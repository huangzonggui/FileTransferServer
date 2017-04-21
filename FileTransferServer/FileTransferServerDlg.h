
// FileTransferServerDlg.h : header file
//

#pragma once


// CFileTransferServerDlg dialog
class CFileTransferServerDlg : public CDialogEx
{
// Construction
public:
	CFileTransferServerDlg(CWnd* pParent = NULL);	// standard constructor

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
	afx_msg void OnBnClickedOk();
	CString m_strRecv;
	CString m_strFileName;
private:
	SOCKET m_socket;
};
