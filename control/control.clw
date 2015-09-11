; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=addnewcontrol
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "control.h"

ClassCount=13
Class1=CControlApp
Class2=CControlDlg

ResourceCount=15
Resource2=IDD_lightcontrldlg
Resource1=IDR_MAINFRAME
Class3=land
Resource3=IDD_usercontrol
Resource4=IDD_lightdlg
Resource5=IDD_sensordlg
Resource6=IDD_controldlg
Resource7=IDR_MENU1
Resource8=IDD_changepassword
Class4=controlmanage
Class5=errormsgdlg
Class6=lightcontrldlg
Class7=lightdlg
Class8=sensordlg
Class9=usercontrol
Resource9=IDD_changename
Class10=about
Resource10=IDD_ABOUT
Resource11=IDD_CONTROL_DIALOG
Class11=changepassword
Resource12=IDD_addnewcontrol
Class12=changename
Resource13=IDD_LANDED
Resource14=IDD_errormsgdlg
Class13=addnewcontrol
Resource15=IDR_MENU2

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
LastObject=IDC_EDIT1



[DLG:IDD_CONTROL_DIALOG]
Type=1
Class=CControlDlg
ControlCount=13
Control1=IDC_LIST1,SysListView32,1350631433
Control2=IDC_LIST2,SysListView32,1350631437
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_BUTTON3,button,1342242816
Control6=IDC_BUTTON4,button,1342242816
Control7=IDC_BUTTON5,button,1342242816
Control8=IDC_BUTTON6,button,1342242816
Control9=IDC_STATIC,static,1342177294
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_EDIT1,edit,1342244992
Control13=IDC_STATIC,button,1342177287

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
ControlCount=12
Control1=IDC_LIST1,SysListView32,1350631433
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_EDIT2,edit,1350631584
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_COMBO1,combobox,1344339971
Control11=IDC_EDIT4,edit,1342244992
Control12=IDC_STATIC,button,1342177287

[DLG:IDD_controldlg]
Type=1
Class=controlmanage
ControlCount=33
Control1=IDC_COMBO1,combobox,1344339971
Control2=IDC_BUTTON3,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON4,button,1342242816
Control5=IDC_EDIT1,edit,1350633600
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_EDIT4,edit,1350631552
Control8=IDC_COMBO2,combobox,1344339971
Control9=IDC_EDIT5,edit,1350631552
Control10=IDC_EDIT6,edit,1350631552
Control11=IDC_EDIT7,edit,1350631552
Control12=IDC_EDIT8,edit,1350631552
Control13=IDC_EDIT9,edit,1350631552
Control14=IDC_EDIT10,edit,1350631552
Control15=IDC_EDIT11,edit,1350631552
Control16=IDC_EDIT12,edit,1350631552
Control17=IDC_BUTTON2,button,1342242816
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816
Control33=IDC_STATIC,button,1342177287

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
VirtualFilter=dWC

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
LastObject=ID_MENUITEM32778
VirtualFilter=dWC

[DLG:IDD_ABOUT]
Type=1
Class=about
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177294
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:about]
Type=0
HeaderFile=about.h
ImplementationFile=about.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_MENUITEM32771
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
Class=CControlDlg
Command1=ID_MENUITEM32771
Command2=ID_MENUITEM32774
Command3=ID_MENUITEM32773
Command4=ID_MENUITEM32772
CommandCount=4

[DLG:IDD_changepassword]
Type=1
Class=changepassword
ControlCount=9
Control1=IDC_EDIT1,edit,1350631584
Control2=IDC_EDIT2,edit,1350631584
Control3=IDC_EDIT3,edit,1350631584
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342177294

[CLS:changepassword]
Type=0
HeaderFile=changepassword.h
ImplementationFile=changepassword.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[DLG:IDD_changename]
Type=1
Class=changename
ControlCount=5
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342177294
Control5=IDC_STATIC,static,1342308352

[CLS:changename]
Type=0
HeaderFile=changename.h
ImplementationFile=changename.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[MNU:IDR_MENU2]
Type=1
Class=usercontrol
Command1=ID_MENUITEM32778
CommandCount=1

[DLG:IDD_addnewcontrol]
Type=1
Class=addnewcontrol
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT1,edit,1350631552
Control10=IDC_EDIT2,edit,1350631552
Control11=IDC_EDIT3,edit,1350631552
Control12=IDC_EDIT4,edit,1350631552
Control13=IDC_EDIT5,edit,1350631552
Control14=IDC_COMBO1,combobox,1344339971

[CLS:addnewcontrol]
Type=0
HeaderFile=addnewcontrol.h
ImplementationFile=addnewcontrol.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

