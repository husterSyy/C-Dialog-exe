#pragma once
#include "ATLComTime.h"
#include "afxwin.h"


// CNoteDlg �Ի���

class CNoteDlg : public CDialog
{
	DECLARE_DYNAMIC(CNoteDlg)

public:
	CNoteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNoteDlg();

// �Ի�������
	enum { IDD = IDD_NoteDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
//	COleDateTime m_time;
	CString m_content;
//	CComboBox m_title;
//	CString m_Title;
	
	
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedChange();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedClean();
	afx_msg void OnBnClickedExit();
	CComboBox m_Title;
	CString m_title;
	COleDateTime m_date;
};
