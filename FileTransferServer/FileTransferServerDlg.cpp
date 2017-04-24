
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
// 	UpdateData(TRUE);//���Դӿؼ�������� 
// 	//1.create file
// 	while (m_strFileName==""){
// 		MessageBox("�ļ�������Ϊ��!");
// 		return FALSE;
// 	}
// 	fp = fopen(m_strFileName,"wb");
// 	if (fp==NULL){
// 		MessageBox("creat file %s failed!");
// 		return FALSE;
// 	}	
// 	m_strRecv+="�������ļ�"+m_strFileName+"\r\n";
// 	UpdateData(FALSE);
// 	MessageBox("�������ļ�"+m_strFileName);
// 
// 	//3.�����׽���(�׽�������,��ʽ�׽���,TCPЭ��)
// 	m_sockListen=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
// 	if (SOCKET_ERROR==m_sockListen){
// 		MessageBox("socket ����");
// 		return FALSE;
// 	}
// 	//4.���÷�������ַ
// 	struct sockaddr_in addrServer;
// 	addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);//"127.0.0.1"
// 	addrServer.sin_family=AF_INET;
// 	addrServer.sin_port=htons(SERVERPORT);//6666
// 	m_len=sizeof(sockaddr);
// 	//5.���׽���
// 	m_ret=bind(m_sockListen,(sockaddr*)&addrServer,m_len);
// 	if (SOCKET_ERROR==m_ret){
// 		MessageBox("bind ����!");
// 		return FALSE;
// 	}
// 	//6.��ʼ����
// 	m_ret=listen(m_sockListen,1);
// 	if (SOCKET_ERROR==m_ret){
// 		MessageBox("listen ����");
// 		return FALSE;
// 	}
// 	m_strRecv+="�����������ɹ���\r\n\r\n";
// 	UpdateData(FALSE);//��ؼ���������
// 
// 	//7.���û��clientҪ���ӣ�server�ڵ���ʱ����������clientҪ���ӣ��ʹ����Ҫ���ӵĶ�����ȡ��Ȼ��accept
// 	//����֪����clientҪ����
// 	struct sockaddr_in addrClient;
// 	m_len=sizeof(sockaddr);
// 	m_sockTongXun=accept(m_sockListen,(sockaddr*)&addrClient,&m_len);
// 	if (INVALID_SOCKET==m_ret){
// 		MessageBox("accept ����!");
// 		return FALSE;
// 	}
// 	m_strRecv+="���յ�һ���ͻ������ӣ����濪ʼ�����ļ�...\r\n";
// 	UpdateData(FALSE);
// 	MessageBox("���յ�һ���ͻ������ӣ����濪ʼ�����ļ�...");
// 	//8.��client������Ϣ
// 	memset(m_sendBuf,0,sizeof(m_sendBuf));
// 	strcpy(m_sendBuf,"Welcome to tcpServer�����Ѿ����ӵ���TCP��������");
// 	m_ret=send(m_sockTongXun,m_sendBuf,sizeof(m_sendBuf)+1,0);
// 	if (SOCKET_ERROR==m_ret){
// 		MessageBox("send ����!");
// 		return FALSE;
// 	}
// 	CString str_sendBuf;
// 	str_sendBuf.Format("%s",m_sendBuf);
// 	m_strRecv+="\r\n��ͻ��˳ɹ�����������Ϣ:\r\n"+str_sendBuf+"\r\n";
// 	UpdateData(FALSE);
// 	MessageBox("��ͻ��˳ɹ�����������Ϣ:"+str_sendBuf);
// 
// 	memset(m_recvBuf,0,sizeof(m_recvBuf));
// 
// 	//9.���ܴӿͻ��˷�������Ϣ
// 	int num = 0;
// 	while (1){
// 		num = recv(m_sockTongXun, m_recvBuf, 512, 0);
// 		if (SOCKET_ERROR==num){
// 			MessageBox("recv ����!");
// 			return FALSE;
// 		}
// 		if(num == 0) 
// 			break;
// 		fwrite(m_recvBuf, 1, num, fp);
// 	}
// 	//10.�ر��ļ�
// 	fclose(fp);
// 	m_strRecv+="transmission done:\r\n";
// 	UpdateData(FALSE);//��ؼ���������
// 
// 	return TRUE;
//}

void CFileTransferServerDlg::StartMessage(void)
{
	UpdateData(TRUE);
	m_strRecv+="���ڼ���...\r\n";
	UpdateData(FALSE);
	MessageBox("�����Ѿ�������");
}


void CFileTransferServerDlg::OnBnClickedBtnListen()
{
	//3.�����׽���(�׽�������,��ʽ�׽���,TCPЭ��)
	m_sockListen=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (SOCKET_ERROR==m_sockListen){
		MessageBox("socket ����");
		return ;
	}
	//4.���÷�������ַ
	addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);//"127.0.0.1"
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(SERVERPORT);//6666
	m_len=sizeof(sockaddr);
	//5.���׽���(�󶨱�������IP�Ͷ˿ں�)
	m_ret=bind(m_sockListen,(sockaddr*)&addrServer,m_len);
	if (SOCKET_ERROR==m_ret){
		MessageBox("bind ����!");
		return ;
	}
	//6.��ʼ����
	m_ret=listen(m_sockListen,1);
	if (SOCKET_ERROR==m_ret){
		MessageBox("listen ����");
		return ;
	}
	m_strRecv+="�����������ɹ���\r\n\r\n";
	UpdateData(FALSE);//��ؼ���������
	StartMessage();
	//7.���û��clientҪ���ӣ�server�ڵ���ʱ����������clientҪ���ӣ��ʹ����Ҫ���ӵĶ�����ȡ��Ȼ��accept
	//����֪����clientҪ����
	struct sockaddr_in addrClient;
	m_len=sizeof(sockaddr);
	m_sockTongXun=accept(m_sockListen,(sockaddr*)&addrClient,&m_len);
	if (INVALID_SOCKET==m_ret){
		MessageBox("accept ����!");
		return ;
	}
	m_strRecv+="���յ�һ���ͻ������ӣ����濪ʼ�����ļ�...\r\n";
	UpdateData(FALSE);
	MessageBox("���յ�һ���ͻ������ӣ����濪ʼ�����ļ�...");
	//8.��client������Ϣ
	memset(m_sendBuf,0,sizeof(m_sendBuf));
	strcpy(m_sendBuf,"Welcome to tcpServer�����Ѿ����ӵ���TCP��������");
	m_ret=send(m_sockTongXun,m_sendBuf,sizeof(m_sendBuf)+1,0);
	if (SOCKET_ERROR==m_ret){
		MessageBox("send ����!");
		return ;
	}
	CString str_sendBuf;
	str_sendBuf.Format("%s",m_sendBuf);
	m_strRecv+="\r\n��ͻ��˳ɹ�����������Ϣ:\r\n"+str_sendBuf+"\r\n";
	UpdateData(FALSE);
	MessageBox("��ͻ��˳ɹ�����������Ϣ:"+str_sendBuf);

	memset(m_recvBuf,0,sizeof(m_recvBuf));

	//�����ļ���
	int fileNameNum = recv(m_sockTongXun,m_recvBuf,512,0);
	if (SOCKET_ERROR==fileNameNum){
		MessageBox("recv �ļ��� ����!");
		return ;
	}
	//MessageBox()
	CString str = m_recvBuf;
	//ReverseFind:��һ���ϴ���ַ����д�ĩ�˿�ʼ����ĳ���ַ�
	m_strFileName=str.Mid(str.ReverseFind('\\')+1);
	m_strFileName=m_FileDir+m_strFileName;
	fp = fopen(m_strFileName,"wb");
	if (fp==NULL){
		MessageBox("creat file %s failed!");
		return ;
	}	
	//m_strRecv+="�������ļ�:\r\n"+m_strFileName+"\r\n\r\n";

	memset(m_recvBuf,0,sizeof(m_recvBuf));
	//9.���ܴӿͻ��˷�������Ϣ
	int num = 0;
	while (1){
		num = recv(m_sockTongXun, m_recvBuf, 512, 0);
		if (SOCKET_ERROR==num){
			MessageBox("recv ����!");
			return ;
		}
		if(num == 0) 
			break;
		fwrite(m_recvBuf, 1, num, fp);
	}
	//10.�ر��ļ�
	fclose(fp);
	m_strRecv+="���յ����ļ�:\r\n"+m_strFileName+"\r\n\r\n";
	m_strRecv+="\r\n�ļ��������:\r\n";
	UpdateData(FALSE);//��ؼ���������
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
			MessageBox("��ȡĿ¼ʧ��");
		} 
			//bRet = TRUE;    
// 		IMalloc *pMalloc = NULL;    
// 		if (SUCCEEDED(SHGetMalloc(&pMalloc)) && pMalloc)    
// 		{     
// 			pMalloc->Free(pidl);     
// 			pMalloc->Release();    
// 		}    
	}    
	m_FileDir = szFolder;//ѡ����ļ���·��
	m_FileDir=m_FileDir+"\\";
	//m_FileDir = "C:\\Users\\hzg\\Desktop\\";
	UpdateData(FALSE);
// 	TRACE("/n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&/n");    
// 	TRACE(m_FileDir);    
// 	TRACE("/n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&/n");    
	MessageBox(m_FileDir);
	//OnPaint(); 
}
