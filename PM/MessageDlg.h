#pragma once


// CMessageDlg �Ի���

class CMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CMessageDlg)

public:
	CMessageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMessageDlg();

// �Ի�������
	enum { IDD = IDD_MessageDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
