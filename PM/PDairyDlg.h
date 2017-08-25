#pragma once
#include "afxwin.h"
#include "ATLComTime.h"


// CPDairyDlg 对话框

class CPDairyDlg : public CDialog
{
	DECLARE_DYNAMIC(CPDairyDlg)

public:
	CPDairyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPDairyDlg();

// 对话框数据
	enum { IDD = IDD_DairyDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedChange();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedClean();
	afx_msg void OnBnClickedExit();
	CComboBox m_Title;
	CString m_title;
//	COleDateTime m_time;
	COleDateTime m_date;
	CString m_content;
};
