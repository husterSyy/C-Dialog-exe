
// PMDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

//#define WM_SHELLNOTIFY  (WM_USER+1)
#define WM_SHELLNOTIFY  (WM_APP+1)



//#define IDI_ICON1 0
//#define IDI_ICON2 1



// CPMDlg 对话框
class CPMDlg : public CDialogEx
{
// 构造
public:
	

	void OnRemind();
	CPMDlg(CWnd* pParent = NULL);	// 标准构造函数
	
	void toolbar();
	void AddToGrid();
	bool m_uCheckState;
	CMenu m_Menu;
	CListCtrl	m_Grid;
	CImageList m_ImageList;						//图像列表
	CToolBar   m_ToolBar;						//工具栏对象
	CStatusBar m_StatusBar;						//状态栏对象

// 对话框数据
	enum { IDD = IDD_PM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
     WINDOWPLACEMENT m_wndPlaceMent;
private:
	void InitNotifyIconData();
	BOOL CompareDateTime();
	void DoClickEvent();
	void DoDbClickEvent();
	void ShowTipInfo();
// 实现
protected:
	//afx_msg void OnMyOperate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShellNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuSystemQuit();
	afx_msg void OnMenuitemHelpAboutDeveloper();
	afx_msg void OnMenuitemHelpExplain();
	void PopupMenu();
	void OnDestroy();
	void OnCancel();
//	afx_msg void OnTimer(UINT nIDEvent);
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDateClickMonthview(DATE DateClicked);
	afx_msg void OnDateDblClickMonthview(DATE DateDblClicked);



	//afx_msg void OnDate();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDate();
	afx_msg void OnRemindtime();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHelp();
	afx_msg void OnDairy();
	afx_msg void OnNote();
	afx_msg void OnMusic();
	afx_msg void OnStart();
	afx_msg void OnRemindfestival();
	afx_msg void OnMainmenu();
	
	afx_msg void OnExit();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

