#pragma once
#include "afxdtctl.h"
#include "afxwin.h"
#include "afxcmn.h"


// CRemindByDate 对话框

class CRemindByDate : public CDialog
{
	DECLARE_DYNAMIC(CRemindByDate)

public:

	

	void AddToGrid();
	CRemindByDate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRemindByDate();
	int pos;
// 对话框数据
	enum { IDD = IDD_DateDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

   COleDateTime	m_date;

//	CString m_title;
	CString m_content;
	CString m_Ctitle;

//    CListCtrl m_AllCont;

	/*
	

	CComboBox	m_title;
	CListCtrl	m_dq_Grid;
	COleDateTime	m_dq_time;
	CString	m_dq_content;
	CString	m_dq_title;
	*/
	//CString	m_jr_title;

	afx_msg void OnBnClickedButtonDateadd();
	
	
//	CString m_Title;
//	CString m_TiTle;
	//afx_msg void OnEnChangeEdit3();
//	CString m_Title;
	afx_msg void OnBnClickedDeletebutton();
	afx_msg void OnBnClickedButtonChange();
	//afx_msg void OnEnChangeEdit2();
	

	
	
	CString m_title;
	CComboBox m_Title;
	virtual BOOL OnInitDialog();
	CListCtrl m_Grid;
	afx_msg void OnClickMainlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedClean();
};
