#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ATLComTime.h"


// CFestvialDlg �Ի���

class CFestvialDlg : public CDialog
{
	DECLARE_DYNAMIC(CFestvialDlg)

public:
	int pos;



	CFestvialDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFestvialDlg();

// �Ի�������
	enum { IDD = IDD_FestivalDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
