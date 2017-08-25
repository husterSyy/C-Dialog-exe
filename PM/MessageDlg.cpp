// MessageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PM.h"
#include "MessageDlg.h"
#include "afxdialogex.h"
#include"MySingletonClass.h"
#include"MusicDlg.h"



#include <Vfw.H>
#pragma comment(lib, "VFW32.lib")
#pragma comment(lib, "WINMM.lib")

HWND hMCI;



IMPLEMENT_DYNAMIC(CMessageDlg, CDialog)

CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageDlg::IDD, pParent)
{

}

CMessageDlg::~CMessageDlg()
{
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMessageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMessageDlg::OnBnClickedButtonClose)
	//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMessageDlg 消息处理程序



void CMessageDlg::OnBnClickedButton1()        //点击确定
{
	
	//MCIWndStop(hMCI);
	this->OnCancel();
	
	MCIWndStop(hMCI);
	
		
}




BOOL CMessageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CMySingletonClass *pMyInstance = CMySingletonClass::GetInstance();
	CString csTipInfo = pMyInstance->m_csTipContent;
	GetDlgItem(IDC_MessA)->SetWindowText(csTipInfo);
	
	CString choose = _T("F://CloudMusic//告白气球.mp3"); //音乐文件的路径   
	hMCI = MCIWndCreate(NULL, NULL, WS_POPUP | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, choose);
	MCIWndPlay(hMCI); //播放音乐

	

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CMessageDlg::OnBnClickedButtonClose()
{
	//MCIWndStop(hMCI);
	// TODO:  在此添加控件通知处理程序代码
	//CDialog::OnCancel();
	this->OnCancel();
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);// 关掉播放
	

	
}

/*
void CMessageDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialog::OnLButtonDown(nFlags, point);
}
*/