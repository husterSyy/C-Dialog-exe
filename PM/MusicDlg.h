#pragma once


// CMusicDlg �Ի���

class CMusicDlg : public CDialog
{
	DECLARE_DYNAMIC(CMusicDlg)

public:
	CMusicDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMusicDlg();

// �Ի�������
	enum { IDD = IDD_MusicDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
