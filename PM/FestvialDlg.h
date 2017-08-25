#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ATLComTime.h"


// CFestvialDlg 对话框

class CFestvialDlg : public CDialog
{
	DECLARE_DYNAMIC(CFestvialDlg)

public:
	int pos;



	CFestvialDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFestvialDlg();

// 对话框数据
	enum { IDD = IDD_FestivalDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void AddToGrid();
	CListCtrl m_Grid;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedChange();
	afx_msg void OnBnClickedDelet();
	afx_msg void OnBnClickedClean();
	afx_msg void OnBnClickedExit();
	
	CComboBox m_Title;
	CString m_title;
	CString m_content;
	COleDateTime m_date;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
