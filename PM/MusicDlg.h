#pragma once


// CMusicDlg 对话框

class CMusicDlg : public CDialog
{
	DECLARE_DYNAMIC(CMusicDlg)

public:
	CMusicDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMusicDlg();

// 对话框数据
	enum { IDD = IDD_MusicDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void play();
    void stop();
	virtual BOOL OnInitDialog();
	//afx_msg void OnBnClickedTryListen();

	//afx_msg void OnBnClickedChangeMusic();
	afx_msg void OnBnClickedPlay();


	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedfilechoice();
	
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedConfirm();
	afx_msg void OnBnClickedExit();
};
