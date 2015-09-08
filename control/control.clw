; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=usercontrol
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "control.h"

ClassCount=9
Class1=CControlApp
Class2=CControlDlg

ResourceCount=9
Resource2=IDD_CONTROL_DIALOG
Resource1=IDR_MAINFRAME
Class3=land
Resource3=IDD_lightdlg
Resource4=IDD_sensordlg
Resource5=IDD_usercontrol
Resource6=IDD_LANDED
Resource7=IDD_lightcontrldlg
Resource8=IDD_controldlg
Class4=controlmanage
Class5=errormsgdlg
Class6=lightcontrldlg
Class7=lightdlg
Class8=sensordlg
Class9=usercontrol
Resource9=IDD_errormsgdlg

[CLS:CControlApp]
Type=0
HeaderFile=control.h
ImplementationFile=control.cpp
Filter=N

[CLS:CControlDlg]
Type=0
HeaderFile=controlDlg.h
ImplementationFile=controlDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CControlDlg



[DLG:IDD_CONTROL_DIALOG]
Type=1
Class=CControlDlg
ControlCount=0

[DLG:IDD_LANDED]
Type=1
Class=land
ControlCount=6
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631584
Control3=IDOK,button,1342242817
Control4=IDC_STATIC,static,1342308364
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342177294

[CLS:land]
Type=0
HeaderFile=land.h
ImplementationFile=land.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_usercontrol]
Type=1
Class=usercontrol
ControlCount=0

[DLG:IDD_controldlg]
Type=1
Class=controlmanage
ControlCount=0

[DLG:IDD_lightdlg]
Type=1
Class=lightdlg
ControlCount=0

[DLG:IDD_sensordlg]
Type=1
Class=sensordlg
ControlCount=0

[DLG:IDD_lightcontrldlg]
Type=1
Class=lightcontrldlg
ControlCount=0

[DLG:IDD_errormsgdlg]
Type=1
Class=errormsgdlg
ControlCount=0

[CLS:controlmanage]
Type=0
HeaderFile=controlmanage.h
ImplementationFile=controlmanage.cpp
BaseClass=CDialog
Filter=D
LastObject=controlmanage

[CLS:errormsgdlg]
Type=0
HeaderFile=errormsgdlg.h
ImplementationFile=errormsgdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=errormsgdlg

[CLS:lightcontrldlg]
Type=0
HeaderFile=lightcontrldlg.h
ImplementationFile=lightcontrldlg.cpp
BaseClass=CDialog
Filter=D
LastObject=lightcontrldlg

[CLS:lightdlg]
Type=0
HeaderFile=lightdlg.h
ImplementationFile=lightdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=lightdlg

[CLS:sensordlg]
Type=0
HeaderFile=sensordlg.h
ImplementationFile=sensordlg.cpp
BaseClass=CDialog
Filter=D
LastObject=sensordlg

[CLS:usercontrol]
Type=0
HeaderFile=usercontrol.h
ImplementationFile=usercontrol.cpp
BaseClass=CDialog
Filter=D
LastObject=usercontrol

