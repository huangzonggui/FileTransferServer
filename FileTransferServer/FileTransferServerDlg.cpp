
// FileTransferServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileTransferServer.h"
#include "FileTransferServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



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
	, m_FileDir(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ret=0;
	m_len=0;
	m_sockListen=0;
	m_sockTongXun=0;
	m_strFileName = _T("");
}

CFileTransferServerDlg::~CFileTransferServerDlg(){
	if (m_sockListen)
		closesocket(m_sockListen);
	if (m_sockTongXun)
		closesocket(m_sockTongXun);

};

void CFileTransferServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERMESSAGE, m_strRecv);
	DDX_Text(pDX, IDC_EDIT_FILEDIR, m_FileDir);
}

BEGIN_MESSAGE_MAP(CFileTransferServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_LISTEN, &CFileTransferServerDlg::OnBnClickedBtnListen)
	ON_BN_CLICKED(IDC_BTN_SELECTFILEDIR, &CFileTransferServerDlg::OnBnClickedBtnSelectfiledir)
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

//bool CFileTransferServerDlg::ListenSocket(void)
//{
// 	UpdateData(TRUE);//可以从控件获得数据 
// 	//1.create file
// 	while (m_strFileName==""){
// 		MessageBox("文件名不能为空!");
// 		return FALSE;
// 	}
// 	fp = fopen(m_strFileName,"wb");
// 	if (fp==NULL){
// 		MessageBox("creat file %s failed!");
// 		return FALSE;
// 	}	
// 	m_strRecv+="生成了文件"+m_strFileName+"\r\n";
// 	UpdateData(FALSE);
// 	MessageBox("生成了文件"+m_strFileName);
// 
// 	//3.创建套接字(套接字类型,流式套接字,TCP协议)
// 	m_sockListen=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
// 	if (SOCKET_ERROR==m_sockListen){
// 		MessageBox("socket 错误");
// 		return FALSE;
// 	}
// 	//4.设置服务器地址
// 	struct sockaddr_in addrServer;
// 	addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);//"127.0.0.1"
// 	addrServer.sin_family=AF_INET;
// 	addrServer.sin_port=htons(SERVERPORT);//6666
// 	m_len=sizeof(sockaddr);
// 	//5.绑定套接字
// 	m_ret=bind(m_sockListen,(sockaddr*)&addrServer,m_len);
// 	if (SOCKET_ERROR==m_ret){
// 		MessageBox("bind 错误!");
// 		return FALSE;
// 	}
// 	//6.开始监听
// 	m_ret=listen(m_sockListen,1);
// 	if (SOCKET_ERROR==m_ret){
// 		MessageBox("listen 错误");
// 		return FALSE;
// 	}
// 	m_strRecv+="服务器启动成功。\r\n\r\n";
// 	UpdateData(FALSE);//向控件传递数据
// 
// 	//7.如果没有client要连接，server在调用时就阻塞，有client要连接，就从这个要连接的队列里取出然后accept
// 	//监听知道有client要连接
// 	struct sockaddr_in addrClient;
// 	m_len=sizeof(sockaddr);
// 	m_sockTongXun=accept(m_sockListen,(sockaddr*)&addrClient,&m_len);
// 	if (INVALID_SOCKET==m_ret){
// 		MessageBox("accept 错误!");
// 		return FALSE;
// 	}
// 	m_strRecv+="接收到一个客户端连接，下面开始传输文件...\r\n";
// 	UpdateData(FALSE);
// 	MessageBox("接收到一个客户端连接，下面开始传输文件...");
// 	//8.向client发送消息
// 	memset(m_sendBuf,0,sizeof(m_sendBuf));
// 	strcpy(m_sendBuf,"Welcome to tcpServer，你已经连接到了TCP服务器！");
// 	m_ret=send(m_sockTongXun,m_sendBuf,sizeof(m_sendBuf)+1,0);
// 	if (SOCKET_ERROR==m_ret){
// 		MessageBox("send 错误!");
// 		return FALSE;
// 	}
// 	CString str_sendBuf;
// 	str_sendBuf.Format("%s",m_sendBuf);
// 	m_strRecv+="\r\n向客户端成功发送以下信息:\r\n"+str_sendBuf+"\r\n";
// 	UpdateData(FALSE);
// 	MessageBox("向客户端成功发送以下信息:"+str_sendBuf);
// 
// 	memset(m_recvBuf,0,sizeof(m_recvBuf));
// 
// 	//9.接受从客户端发来的消息
// 	int num = 0;
// 	while (1){
// 		num = recv(m_sockTongXun, m_recvBuf, 512, 0);
// 		if (SOCKET_ERROR==num){
// 			MessageBox("recv 错误!");
// 			return FALSE;
// 		}
// 		if(num == 0) 
// 			break;
// 		fwrite(m_recvBuf, 1, num, fp);
// 	}
// 	//10.关闭文件
// 	fclose(fp);
// 	m_strRecv+="transmission done:\r\n";
// 	UpdateData(FALSE);//向控件传递数据
// 
// 	return TRUE;
//}

void CFileTransferServerDlg::StartMessage(void)
{
	UpdateData(TRUE);
	m_strRecv+="正在监听...\r\n";
	UpdateData(FALSE);
	MessageBox("监听已经启动！");
}


void CFileTransferServerDlg::OnBnClickedBtnListen()
{
	//3.创建套接字(套接字类型,流式套接字,TCP协议)
	m_sockListen=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (SOCKET_ERROR==m_sockListen){
		MessageBox("socket 错误");
		return ;
	}
	//4.设置服务器地址
	addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);//"127.0.0.1"
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(SERVERPORT);//6666
	m_len=sizeof(sockaddr);
	//5.绑定套接字(绑定本地主机IP和端口号)
	m_ret=bind(m_sockListen,(sockaddr*)&addrServer,m_len);
	if (SOCKET_ERROR==m_ret){
		MessageBox("bind 错误!");
		return ;
	}
	//6.开始监听
	m_ret=listen(m_sockListen,1);
	if (SOCKET_ERROR==m_ret){
		MessageBox("listen 错误");
		return ;
	}
	m_strRecv+="服务器启动成功。\r\n\r\n";
	UpdateData(FALSE);//向控件传递数据
	StartMessage();
	//7.如果没有client要连接，server在调用时就阻塞，有client要连接，就从这个要连接的队列里取出然后accept
	//监听知道有client要连接
	struct sockaddr_in addrClient;
	m_len=sizeof(sockaddr);
	m_sockTongXun=accept(m_sockListen,(sockaddr*)&addrClient,&m_len);
	if (INVALID_SOCKET==m_ret){
		MessageBox("accept 错误!");
		return ;
	}
	m_strRecv+="接收到一个客户端连接，下面开始传输文件...\r\n";
	UpdateData(FALSE);
	MessageBox("接收到一个客户端连接，下面开始传输文件...");
	//8.向client发送消息
	memset(m_sendBuf,0,sizeof(m_sendBuf));
	strcpy(m_sendBuf,"Welcome to tcpServer，你已经连接到了TCP服务器！");
	m_ret=send(m_sockTongXun,m_sendBuf,sizeof(m_sendBuf)+1,0);
	if (SOCKET_ERROR==m_ret){
		MessageBox("send 错误!");
		return ;
	}
	CString str_sendBuf;
	str_sendBuf.Format("%s",m_sendBuf);
	m_strRecv+="\r\n向客户端成功发送以下信息:\r\n"+str_sendBuf+"\r\n";
	UpdateData(FALSE);
	MessageBox("向客户端成功发送以下信息:"+str_sendBuf);

	memset(m_recvBuf,0,sizeof(m_recvBuf));

	//接收文件名
	int fileNameNum = recv(m_sockTongXun,m_recvBuf,512,0);
	if (SOCKET_ERROR==fileNameNum){
		MessageBox("recv 文件名 错误!");
		return ;
	}
	//MessageBox()
	CString str = m_recvBuf;
	//ReverseFind:在一个较大的字符串中从末端开始查找某个字符
	m_strFileName=str.Mid(str.ReverseFind('\\')+1);
	m_strFileName=m_FileDir+m_strFileName;
	fp = fopen(m_strFileName,"wb");
	if (fp==NULL){
		MessageBox("creat file %s failed!");
		return ;
	}	
	//m_strRecv+="生成了文件:\r\n"+m_strFileName+"\r\n\r\n";

	memset(m_recvBuf,0,sizeof(m_recvBuf));
	//9.接受从客户端发来的消息
	int num = 0;
	while (1){
		num = recv(m_sockTongXun, m_recvBuf, 512, 0);
		if (SOCKET_ERROR==num){
			MessageBox("recv 错误!");
			return ;
		}
		if(num == 0) 
			break;
		fwrite(m_recvBuf, 1, num, fp);
	}
	//10.关闭文件
	fclose(fp);
	m_strRecv+="接收到了文件:\r\n"+m_strFileName+"\r\n\r\n";
	m_strRecv+="\r\n文件传输完成:\r\n";
	UpdateData(FALSE);//向控件传递数据
}


void CFileTransferServerDlg::OnBnClickedBtnSelectfiledir()
{
	// TODO: Add your control notification handler code here
	m_FileDir;    
	BROWSEINFO bi;    
	ZeroMemory(&bi, sizeof(BROWSEINFO));    
	bi.hwndOwner = m_hWnd;    
	bi.ulFlags   = BIF_RETURNONLYFSDIRS;    
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);     
	TCHAR szFolder[MAX_PATH*2];    
	szFolder[0] = _T('/0');    
	if (pidl)    
	{   
		if (SHGetPathFromIDList(pidl, szFolder)==FALSE){
			MessageBox("获取目录失败");
		} 
			//bRet = TRUE;    
// 		IMalloc *pMalloc = NULL;    
// 		if (SUCCEEDED(SHGetMalloc(&pMalloc)) && pMalloc)    
// 		{     
// 			pMalloc->Free(pidl);     
// 			pMalloc->Release();    
// 		}    
	}    
	m_FileDir = szFolder;//选择的文件夹路径
	m_FileDir=m_FileDir+"\\";
	//m_FileDir = "C:\\Users\\hzg\\Desktop\\";
	UpdateData(FALSE);
// 	TRACE("/n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&/n");    
// 	TRACE(m_FileDir);    
// 	TRACE("/n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&/n");    
	MessageBox(m_FileDir);
	//OnPaint(); 
}
