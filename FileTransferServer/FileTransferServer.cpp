
// FileTransferServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FileTransferServer.h"
#include "FileTransferServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileTransferServerApp

BEGIN_MESSAGE_MAP(CFileTransferServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFileTransferServerApp construction

CFileTransferServerApp::CFileTransferServerApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CFileTransferServerApp::~CFileTransferServerApp(){
	//析构函数中卸载winsock
	WSACleanup();
}


// The one and only CFileTransferServerApp object

CFileTransferServerApp theApp;


// CFileTransferServerApp initialization

BOOL CFileTransferServerApp::InitInstance()
{
	//初始化函数里初始化winsock
	//存放windows socket初始化信息
	WSADATA wsaData;
	int ret;
	ret=WSAStartup(MAKEWORD(2,2),&wsaData);
	if (SOCKET_ERROR==ret){
		return FALSE;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 ||//是取得16进制数最低（最右边）那个字节的内容
		HIBYTE( wsaData.wVersion ) != 2 ) {//取得16进制数最高（最左边）那个字节的内容

			WSACleanup( );
			return FALSE; 
	}

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CFileTransferServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump
	return FALSE;
}

