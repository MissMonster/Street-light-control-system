; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBaidumapDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "baidumap.h"

ClassCount=3
Class1=CBaidumapApp
Class2=CBaidumapDlg

ResourceCount=6
Resource2=IDD_BAIDUMAP_DIALOG
Resource3=IDR_MENU2
Resource4=IDD_DIALOG1
Resource1=IDR_MAINFRAME
Class3=login
Resource5=IDR_MENU1
Resource6=IDR_MENU3

[CLS:CBaidumapApp]
Type=0
HeaderFile=baidumap.h
ImplementationFile=baidumap.cpp
Filter=N
LastObject=CBaidumapApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CBaidumapDlg]
Type=0
HeaderFile=baidumapDlg.h
ImplementationFile=baidumapDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CBaidumapDlg



[DLG:IDD_BAIDUMAP_DIALOG]
Type=1
Class=CBaidumapDlg
ControlCount=10
Control1=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_LIST1,SysListView32,1350631433
Control7=IDC_LIST2,SysListView32,1350631433
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287

[MNU:IDR_MENU1]
Type=1
Class=CBaidumapApp
Command1=ID_MENUITEM32777
Command2=ID_MENUITEM32773
Command3=ID_MENUITEM32774
CommandCount=3

[MNU:IDR_MENU2]
Type=1
Class=CBaidumapApp
Command1=ID_MENUITEM32775
Command2=ID_MENUITEM32776
CommandCount=2

[DLG:IDD_DIALOG1]
Type=1
Class=login
ControlCount=7
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631584
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342177294
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:login]
Type=0
HeaderFile=login.h
ImplementationFile=login.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[MNU:IDR_MENU3]
Type=1
Class=?
Command1=ID_MENUITEM32781
Command2=ID_MENUITEM32780
Command3=ID_MENUITEM32782
Command4=ID_MENUITEM32783
Command5=ID_MENUITEM32779
CommandCount=5

