; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgLogin
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LampServer.h"
LastPage=0

ClassCount=6
Class1=CLampServerApp
Class2=CLampServerDoc
Class3=CLampServerView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_LAMPSERVER_FORM
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX
Class6=CDlgLogin
Resource4=IDD_DIALOG_LOGIN

[CLS:CLampServerApp]
Type=0
HeaderFile=LampServer.h
ImplementationFile=LampServer.cpp
Filter=N

[CLS:CLampServerDoc]
Type=0
HeaderFile=LampServerDoc.h
ImplementationFile=LampServerDoc.cpp
Filter=N

[CLS:CLampServerView]
Type=0
HeaderFile=LampServerView.h
ImplementationFile=LampServerView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=CLampServerView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=LampServer.cpp
ImplementationFile=LampServer.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_LAMPSERVER_FORM]
Type=1
Class=CLampServerView
ControlCount=5
Control1=IDC_EDIT1,edit,1352730692
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_BUTTON3,button,1342242816

[DLG:IDD_DIALOG_LOGIN]
Type=1
Class=CDlgLogin
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308865
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350631584

[CLS:CDlgLogin]
Type=0
HeaderFile=DlgLogin.h
ImplementationFile=DlgLogin.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgLogin

