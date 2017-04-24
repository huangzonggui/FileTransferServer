
// FileTransferServerDlg.h : header file
//

#pragma once


// CFileTransferServerDlg dialog
class CFileTransferServerDlg : public CDialogEx
{
// Construction
public:
	CFileTransferServerDlg(CWnd* pParent = NULL);	// standard constructor
	~CFileTransferServerDlg();
// Dialog Data
	enum { IDD = IDD_FILETRANSFERSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
//	afx_msg void OnBnClickedOk();
	CString m_strRecv;
	CString m_strFileName;
	int m_ret;
	char m_sendBuf[512],m_recvBuf[512];
	int m_len;
	FILE *fp;
private:
	SOCKET m_sockListen;
	SOCKET m_sockTongXun;
public:
	void StartMessage(void);
	afx_msg void OnBnClickedBtnListen();
	struct sockaddr_in addrServer;
	afx_msg void OnBnClickedBtnSelectfiledir();
	CString m_FileDir;
};
