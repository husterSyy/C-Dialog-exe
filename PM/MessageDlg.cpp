// MessageDlg.cpp : ʵ���ļ�
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


// CMessageDlg ��Ϣ�������



void CMessageDlg::OnBnClickedButton1()        //���ȷ��
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
	
	CString choose = _T("F://CloudMusic//�������.mp3"); //�����ļ���·��   
	hMCI = MCIWndCreate(NULL, NULL, WS_POPUP | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, choose);
	MCIWndPlay(hMCI); //��������

	

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CMessageDlg::OnBnClickedButtonClose()
{
	//MCIWndStop(hMCI);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialog::OnCancel();
	this->OnCancel();
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);// �ص�����
	

	
}

/*
void CMessageDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialog::OnLButtonDown(nFlags, point);
}
*/