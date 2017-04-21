
// FileTransferServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileTransferServer.h"
#include "FileTransferServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SERVERIP "127.0.0.1"
#define SERVERPORT 6666


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileTransferServerDlg dialog




CFileTransferServerDlg::CFileTransferServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileTransferServerDlg::IDD, pParent)
	, m_strRecv(_T(""))
	, m_strFileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileTransferServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERMESSAGE, m_strRecv);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
}

BEGIN_MESSAGE_MAP(CFileTransferServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFileTransferServerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileTransferServerDlg message handlers

BOOL CFileTransferServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileTransferServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileTransferServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileTransferServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileTransferServerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int ret;
	char sendBuf[512],recvBuf[512];
	//���windows socket��ʼ����Ϣ
	WSADATA data;
	SOCKET sockListen,sockTongXun;

	//UpdateData(FALSE);//������ؼ���������
	UpdateData(TRUE);//���Դӿؼ�������� 
	//1.create file
	FILE *fp = fopen(m_strFileName,"wb");
	if (fp==NULL){
		MessageBox("creat file %s failed!");
	}
	//2.��ʼ��winsock
	ret=WSAStartup(MAKEWORD(2,2),&data);
	if (SOCKET_ERROR==ret){
		MessageBox("creat file %s failed!");
	}
	//3.�����׽���(�׽�������,��ʽ�׽���,TCPЭ��)
	sockListen=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (SOCKET_ERROR==sockListen){
		MessageBox("socket ����");
	}
	////4.���÷�������ַ
	//struct sockaddr_in addrServer;
	//int len;
	//addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);//"127.0.0.1"
	//addrServer.sin_family=AF_INET;
	//addrServer.sin_port=htons(SERVERPORT);//6666
	//len=sizeof(sockaddr);
	////5.���׽���
	//ret=bind(sockListen,(sockaddr*)&addrServer,len);
	//if (SOCKET_ERROR==ret){
	//	serverMassage->SetWindowText("bind ����\r\n");
	//	//return;
	//}



	////UpdateData(FALSE);
	//


	////6.��ʼ����
	//ret=listen(sockListen,1);
	//if (SOCKET_ERROR==ret){
	//	serverMassage->SetWindowText("listen ����\r\n");
	//	//return;
	//}
	//serverMassage->SetWindowText("�����������ɹ������ڼ���...\r\n\r\n");
	////7.���û��clientҪ���ӣ�server�ڵ���ʱ����������clientҪ���ӣ��ʹ����Ҫ���ӵĶ�����ȡ��Ȼ��accept
	//struct sockaddr_in addrClient;
	//len=sizeof(sockaddr);
	//sockTongXun=accept(sockListen,(sockaddr*)&addrClient,&len);
	//if (INVALID_SOCKET==ret){
	//	serverMassage->SetWindowText("accept ����\r\n");
	//	//return ;
	//}

	//serverMassage->SetWindowText("���յ�һ���ͻ������ӣ����濪ʼͨ��...\r\n\r\n");
	////8.��client������Ϣ
	//memset(sendBuf,0,sizeof(sendBuf));
	//strcpy(sendBuf,"Welcome to tcpServer�����Ѿ����ӵ���TCP��������");
	//ret=send(sockTongXun,sendBuf,sizeof(sendBuf)+1,0);
	//if (SOCKET_ERROR==ret){
	//	serverMassage->SetWindowText("accept ����\r\n");
	//	//return ;
	//}
	////printf("��ͻ��˳ɹ�����������Ϣ:\n%s\n\n",sendBuf);??????
	//serverMassage->SetWindowText("��ͻ��˳ɹ�����������Ϣ:\r\n%s\r\n\r\n");

	//memset(recvBuf,0,sizeof(recvBuf));
	////9.���ܴӿͻ��˷�������Ϣ
	//int num = 0;
	//while (1){
	//	num = recv(sockTongXun, recvBuf, 512, 0);
	//	if (SOCKET_ERROR==num){
	//		printf("recv ����");
	//		//return ;
	//	}
	//	if(num == 0) 
	//		break;
	//	fwrite(recvBuf, 1, num, fp);
	//}
	//serverMassage->SetWindowText("transmission done\r\n");
	////10.�ر��ļ�
	//fclose(fp);

	////12.�ر��׽���
	//closesocket(sockListen);
	//closesocket(sockTongXun);
	////13.ж��winsock
	//WSACleanup();
	//file_name.ReleaseBuffer();

	//CDialogEx::OnOK();
}
