// DataBase.cpp: implementation of the CDataBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDataBase::CDataBase(CString server,CString strSQLTYPE,CString db,CString UserName,CString Pwd)
{
	linkOK = FALSE;
	linkOK = OpenConnectionSQL( server , db , UserName , Pwd );

}

CDataBase::~CDataBase()
{
	//AoutLock lock( &crEvent );
	if (linkOK)
	{
		if ( m_pADOSet->State == adStateOpen)	
		{
			m_pADOSet->Close();
		}
		m_pADOSet.Release();
		if ( m_pADOSet1->State == adStateOpen)	
		{
			m_pADOSet1->Close();
		}
		m_pADOSet1.Release();
		if ( m_pADOSet2->State == adStateOpen)	
		{
			m_pADOSet2->Close();
		}
		m_pADOSet2.Release();
		if ( m_pADOSet3->State == adStateOpen)	
		{
			m_pADOSet3->Close();
		}
		m_pADOSet3.Release();
		if ( m_pADOSet4->State == adStateOpen)	
		{
			m_pADOSet4->Close();
		}
		m_pADOSet4.Release();
		if(ADOConn->State)
			ADOConn->Close(); 
		ADOConn.Release();
		
		linkOK = FALSE;
		::CoUninitialize();
	}
}

BOOL CDataBase::CloseConnection()
{
	if (linkOK)
	{
		if ( m_pADOSet->State == adStateOpen)	
		{
			m_pADOSet->Close();
		}
		m_pADOSet->Release();
		if ( m_pADOSet1->State == adStateOpen)	
		{
			m_pADOSet1->Close();
		}
		m_pADOSet1->Release();
		if ( m_pADOSet2->State == adStateOpen)	
		{
			m_pADOSet2->Close();
		}
		m_pADOSet2->Release();
		if ( m_pADOSet3->State == adStateOpen)	
		{
			m_pADOSet3->Close();
		}
		m_pADOSet3->Release();
		if ( m_pADOSet4->State == adStateOpen)	
		{
			m_pADOSet4->Close();
		}
		m_pADOSet4->Release();
		if(ADOConn->State)
			ADOConn->Close(); 
		ADOConn.Release();
		
		linkOK = FALSE;
	}
	
	::CoUninitialize();
	return !linkOK;
}


BOOL CDataBase::OpenConnectionSQL(CString server,CString db,CString UserName,CString Pwd)
{
	CString strCn; 
	strCn.Empty(); 
	strCn.Format(_T("driver={MySQL ODBC 3.51 Driver};Server=%s;DATABASE=%s;USER=%s;PASSWORD=%s;OPTION=3"),
		server , db , UserName , Pwd );
	_variant_t bcnstr  = _variant_t(strCn); 
	_variant_t bunstr  = _variant_t(UserName); 
	_variant_t bpwdstr = _variant_t(Pwd);
	if( FAILED(::CoInitialize(NULL)) ) 
	{
		AfxMessageBox(_T("ADO Init failed"));
		return FALSE;
	}
	try
	{
		
		//ADOConn.CreateInstance(__uuidof(Connection));
		
		ADOConn.CreateInstance("ADODB.Connection");
		ADOConn->ConnectionTimeout=5;
		//ADOConn->Open( _bstr_t(bcnstr) , _bstr_t(bunstr) , 
		//	_bstr_t(bpwdstr) , adConnectUnspecified );
		ADOConn->Open(_bstr_t(bcnstr),_bstr_t(bunstr),_bstr_t(bpwdstr),adModeUnknown);

		linkOK = TRUE;
	}
	catch(_com_error &e)
	{
		CString err;
		err.Format(_T("%s"), (TCHAR*)(e.Description()) );
		linkOK = FALSE;
		AfxMessageBox(err);	
		return FALSE;
	}
	catch(...)
	{
		AfxMessageBox(_T("Unknown Error..."));
	}
	m_pADOSet.CreateInstance(__uuidof(Recordset));
	m_pADOSet1.CreateInstance(__uuidof(Recordset));
	m_pADOSet2.CreateInstance(__uuidof(Recordset));
	m_pADOSet3.CreateInstance(__uuidof(Recordset));
	m_pADOSet4.CreateInstance(__uuidof(Recordset));
	_CommandPtr cmmd;
	hr = cmmd.CreateInstance(__uuidof(Command));	
	if(FAILED(hr))
	{   
		AfxMessageBox(_T("创建_CommandPtr对象失败"));   
		return FALSE;
	}	
    return TRUE;
}


BOOL CDataBase::ADOExecute(_RecordsetPtr &ADOSet, _variant_t &strSQL,BOOL showError)
{	
	if (!linkOK)
	{
		//DEBUG_INFO1(_T("%s"),_T("!linkOK"));
		return FALSE;
	}
	try
	{
		Sleep(10);
		//AfxMessageBox((TCHAR*)((_bstr_t)strSQL));
		if ( ADOSet->State == adStateOpen)	ADOSet->Close();
		ADOSet = NULL;
		ADOSet.CreateInstance(__uuidof(Recordset));
		//ADOConn->BeginTrans();
		ADOSet->Open(strSQL, ADOConn.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdUnknown);
		//ADOConn->CommitTrans();
		return true;
	}
	catch(_com_error &e)//
	{ 
//		DEBUG_INFO1(_T("%s"),strSQL);
		/*ADOConn->RollbackTrans();
 		if (showError)
 		{
 			CString err;
			err.Format(_T("ADO Error: %s"),(TCHAR*)e.Description());
 			AfxMessageBox(err);
 		}*/
		//OpenConnection();
		return false;
	}
}
