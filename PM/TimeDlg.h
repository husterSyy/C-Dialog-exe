#pragma once
#include "afxcmn.h"
#include "ATLComTime.h"
#include "afxwin.h"


// CTimeDlg 对话框

class CTimeDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimeDlg)

public:
	void AddToGrid();
	int pos;
	CTimeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTimeDlg();

// 对话框数据
	enum { IDD = IDD_TimeDIALOG };
//	CString m_csTipInfo;
private:
	void Remind();
	void ShowTipInfo();
	BOOL CompareDateTime();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedAdd();

	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnBnClickedChange();

	CListCtrl m_Grid;
	COleDateTime m_time;
	COleDateTime m_clocktime;
	CString m_title;

//	CString m_content;
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedCle();
	afx_msg void OnBnClickedExit1();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedRemind();

	//afx_msg void OnBnClickedRemindM();


	afx_msg void OnBnClickedButton10();

	CString m_content;
	CString m_hour;
	CString m_minute;
	CString m_second;
	CEdit m_hour1;
	CEdit m_minute1;
	CEdit m_second1;
	CString s;
};
