// MusicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PM.h"
#include "MusicDlg.h"
#include "afxdialogex.h"

/*
#include <Vfw.H>
#pragma comment(lib, "VFW32.lib")
#pragma comment(lib, "WINMM.lib")
*/




//
#include <MMSystem.h>
#include <Digitalv.h>

#pragma comment(lib, "Winmm.lib")


HWND m_hWnd;
DWORD DeviceId;
MCI_OPEN_PARMS mciopenparms;


// CMusicDlg 对话框

IMPLEMENT_DYNAMIC(CMusicDlg, CDialog)

CMusicDlg::CMusicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMusicDlg::IDD, pParent)
{

}

CMusicDlg::~CMusicDlg()
{
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMusicDlg, CDialog)
	//ON_BN_CLICKED(IDC_BUTTON1, &CMusicDlg::OnBnClickedTryListen)
	
	//ON_BN_CLICKED(IDC_BUTTON4, &CMusicDlg::OnBnClickedChangeMusic)
	ON_BN_CLICKED(IDC_PLAY, &CMusicDlg::OnBnClickedPlay)
	

	ON_BN_CLICKED(IDC_STOP, &CMusicDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_filechoice, &CMusicDlg::OnBnClickedfilechoice)
	
	ON_BN_CLICKED(IDC_PAUSE, &CMusicDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_filechoice3, &CMusicDlg::OnBnClickedConfirm)
	ON_BN_CLICKED(IDC_filechoice2, &CMusicDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CMusicDlg 消息处理程序


void Load(HWND hWnd, CString strFilepath)
{
	m_hWnd = hWnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0); //在加载文件前先清空上一次播放的设备
	mciopenparms.lpstrElementName = strFilepath; //将音乐文件路径传给设备
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))
	{
		//如果打开玩家失败,将出错信息储存在buffer,并显示出错警告
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256); //获取错误码对应的错误信息
		MessageBox(hWnd, buffer, "出错警告！", MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP); //弹出错误信息提示对话框
	}
	DeviceId = mciopenparms.wDeviceID;
	//打开文件成功就关联文件到设备
}

void CMusicDlg::play()
{
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)m_hWnd;
	mciplayparms.dwFrom = 0; //每次播放都是从0开始播放
	mciSendCommand(DeviceId, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);
}


void pause()
{
	mciSendCommand(DeviceId, MCI_PAUSE, 0, 0);
}


void resume()
{
	mciSendCommand(DeviceId, MCI_RESUME, 0, 0);
}



void CMusicDlg::stop()
{
	mciSendCommand(DeviceId, MCI_STOP, 0, 0);
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);
	//当点击停止按钮时,将所有的信息都清除掉
}



BOOL CMusicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	/*
	HWND hMCI;
	CString choose = _T("F://CloudMusic//1.mp3"); //音乐文件的路径   
	hMCI = MCIWndCreate(NULL, NULL, WS_POPUP | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, choose);
	MCIWndPlay(hMCI); //播放音乐
	
	*/
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



void CMusicDlg::OnBnClickedPlay()
{
	// TODO:  在此添加控件通知处理程序代码

		play();
		SetDlgItemText(IDC_PAUSE, "暂停");
	
}


void CMusicDlg::OnBnClickedfilechoice()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	char szFileFilter[] = "mp3文件(*.mp3)|*.mp3|"
		"wma文件(*.wma)|*.wma|"
		"wav文件(*.wav)|*.wav|"
		"所有文件(*.*)|*.*|";
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, szFileFilter);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilepath = dlg.GetPathName();
		CString strFilename = dlg.GetFileName();
		SetDlgItemText(IDC_filename, strFilename);
		Load(this->m_hWnd, strFilepath);
	}
	GetDlgItem(IDC_PLAY)->EnableWindow(true); //文件读取成功时所有按钮变成可选
	GetDlgItem(IDC_PAUSE)->EnableWindow(true);
	GetDlgItem(IDC_STOP)->EnableWindow(true);
}


void CMusicDlg::OnBnClickedStop()
{
	// TODO:  在此添加控件通知处理程序代码
	stop();
	SetDlgItemText(IDC_PAUSE, "暂停");
	//GetDlgItem(IDC_PLAY)->EnableWindow(false); //当按下stop的时候,播放和暂停不可选
	//GetDlgItem(IDC_PAUSE)->EnableWindow(false);


}

void CMusicDlg::OnBnClickedPause()
{
	// TODO:  在此添加控件通知处理程序代码

	CString strTemp;
	GetDlgItemText(IDC_PAUSE, strTemp); //获取按钮的状态
	if (strTemp.Compare("暂停") == 0)
	{
		pause();
		SetDlgItemText(IDC_PAUSE, "恢复");
	}

	if (strTemp.Compare("恢复") == 0)
	{
		resume();
		SetDlgItemText(IDC_PAUSE, "暂停");
	}
}


void CMusicDlg::OnBnClickedConfirm()
{
	// TODO:  在此添加控件通知处理程序代码
	MessageBox("修改成功");
}


void CMusicDlg::OnBnClickedExit()
{
	// TODO:  在此添加控件通知处理程序代码
	this->OnCancel();
	stop();
}
