// MusicDlg.cpp : ʵ���ļ�
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


// CMusicDlg �Ի���

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


// CMusicDlg ��Ϣ�������


void Load(HWND hWnd, CString strFilepath)
{
	m_hWnd = hWnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0); //�ڼ����ļ�ǰ�������һ�β��ŵ��豸
	mciopenparms.lpstrElementName = strFilepath; //�������ļ�·�������豸
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))
	{
		//��������ʧ��,��������Ϣ������buffer,����ʾ������
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256); //��ȡ�������Ӧ�Ĵ�����Ϣ
		MessageBox(hWnd, buffer, "�����棡", MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP); //����������Ϣ��ʾ�Ի���
	}
	DeviceId = mciopenparms.wDeviceID;
	//���ļ��ɹ��͹����ļ����豸
}

void CMusicDlg::play()
{
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)m_hWnd;
	mciplayparms.dwFrom = 0; //ÿ�β��Ŷ��Ǵ�0��ʼ����
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
	//�����ֹͣ��ťʱ,�����е���Ϣ�������
}



BOOL CMusicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	/*
	HWND hMCI;
	CString choose = _T("F://CloudMusic//1.mp3"); //�����ļ���·��   
	hMCI = MCIWndCreate(NULL, NULL, WS_POPUP | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, choose);
	MCIWndPlay(hMCI); //��������
	
	*/
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}



void CMusicDlg::OnBnClickedPlay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

		play();
		SetDlgItemText(IDC_PAUSE, "��ͣ");
	
}


void CMusicDlg::OnBnClickedfilechoice()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char szFileFilter[] = "mp3�ļ�(*.mp3)|*.mp3|"
		"wma�ļ�(*.wma)|*.wma|"
		"wav�ļ�(*.wav)|*.wav|"
		"�����ļ�(*.*)|*.*|";
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, szFileFilter);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilepath = dlg.GetPathName();
		CString strFilename = dlg.GetFileName();
		SetDlgItemText(IDC_filename, strFilename);
		Load(this->m_hWnd, strFilepath);
	}
	GetDlgItem(IDC_PLAY)->EnableWindow(true); //�ļ���ȡ�ɹ�ʱ���а�ť��ɿ�ѡ
	GetDlgItem(IDC_PAUSE)->EnableWindow(true);
	GetDlgItem(IDC_STOP)->EnableWindow(true);
}


void CMusicDlg::OnBnClickedStop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	stop();
	SetDlgItemText(IDC_PAUSE, "��ͣ");
	//GetDlgItem(IDC_PLAY)->EnableWindow(false); //������stop��ʱ��,���ź���ͣ����ѡ
	//GetDlgItem(IDC_PAUSE)->EnableWindow(false);


}

void CMusicDlg::OnBnClickedPause()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString strTemp;
	GetDlgItemText(IDC_PAUSE, strTemp); //��ȡ��ť��״̬
	if (strTemp.Compare("��ͣ") == 0)
	{
		pause();
		SetDlgItemText(IDC_PAUSE, "�ָ�");
	}

	if (strTemp.Compare("�ָ�") == 0)
	{
		resume();
		SetDlgItemText(IDC_PAUSE, "��ͣ");
	}
}


void CMusicDlg::OnBnClickedConfirm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageBox("�޸ĳɹ�");
}


void CMusicDlg::OnBnClickedExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->OnCancel();
	stop();
}
