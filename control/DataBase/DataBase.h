// DataBase.h: interface for the CDataBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASE_H__A03BEF79_5955_4E75_84DE_E74D52C36133__INCLUDED_)
#define AFX_DATABASE_H__A03BEF79_5955_4E75_84DE_E74D52C36133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataBase  
{
public:
	CDataBase(CString server=_T(""),CString strSQLTYPE = _T("ACCESS"),CString db=_T(""),CString UserName=_T(""),CString Pwd=_T(""));
	virtual ~CDataBase();

	BOOL OpenConnectionSQL(CString server,CString db,CString UserName,CString Pwd);
	BOOL ADOExecute(_RecordsetPtr &ADOSet, _variant_t &strSQL,BOOL showError);	

	BOOL CloseConnection();
	BOOL           linkOK;	
	HRESULT        hr;
	_RecordsetPtr  m_pADOSet;
	_RecordsetPtr  m_pADOSet1;
	_RecordsetPtr  m_pADOSet2;
	_RecordsetPtr  m_pADOSet3;
	_RecordsetPtr  m_pADOSet4;
	_ConnectionPtr ADOConn;	
};

#endif // !defined(AFX_DATABASE_H__A03BEF79_5955_4E75_84DE_E74D52C36133__INCLUDED_)
