/**************************************
 *FILE    :brightness.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :4/22/2015
 *TEXT    :DataStructure for Street light control system
 *EMAIL   :gtsoft_wk@foxmail.com
***************************************/

#include "stdafx.h"
#include "baidumap.h"
#include "brightness.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// brightness dialog


brightness::brightness(CWnd* pParent /*=NULL*/)
	: CDialog(brightness::IDD, pParent)
{
	//{{AFX_DATA_INIT(brightness)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void brightness::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(brightness)
	DDX_Control(pDX, IDC_SLIDER2, m_slider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(brightness, CDialog)
	//{{AFX_MSG_MAP(brightness)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// brightness message handlers

BOOL brightness::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_slider.SetRange(0,255);//设置滑动范围
	m_slider.SetTicFreq(10);//每10个单位画一刻度

	CString str;
	str="0";
	GetDlgItem(IDC_EDIT1)->SetWindowText(str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void brightness::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//if (nSBCode == SB_THUMBTRACK)	
    {
		CString str;
		int index=m_slider.GetPos();
		str.Format("%d",index);
		GetDlgItem(IDC_EDIT1)->SetWindowText(str);
    }
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
