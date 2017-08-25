// NoteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PM.h"
#include "NoteDlg.h"
#include "afxdialogex.h"
#include"ADOConn.h"


// CNoteDlg �Ի���

IMPLEMENT_DYNAMIC(CNoteDlg, CDialog)

CNoteDlg::CNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNoteDlg::IDD, pParent)
	//, m_time(COleDateTime::GetCurrentTime())
	, m_content(_T(""))
	//, m_Title(_T(""))
	, m_title(_T(""))
	, m_date(COleDateTime::GetCurrentTime())
{

}

CNoteDlg::~CNoteDlg()
{
}

void CNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time);
	DDX_Text(pDX, IDC_EDIT1, m_content);
	//  DDX_Control(pDX, IDC_COMBO1, m_title);
	//  DDX_CBString(pDX, IDC_COMBO1, m_Title);



	DDX_Control(pDX, IDC_COMBO1, m_Title);
	DDX_CBString(pDX, IDC_COMBO1, m_title);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
}


BEGIN_MESSAGE_MAP(CNoteDlg, CDialog)
	

	ON_BN_CLICKED(IDC_BUTTON1, &CNoteDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON3, &CNoteDlg::OnBnClickedChange)
	ON_BN_CLICKED(IDC_BUTTON4, &CNoteDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_BUTTON5, &CNoteDlg::OnBnClickedClean)
	ON_BN_CLICKED(IDC_BUTTON6, &CNoteDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CNoteDlg ��Ϣ�������




void CNoteDlg::OnBnClickedAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


	UpdateData(TRUE);
	int year = m_date.GetYear();
	int mounth = m_date.GetMonth();
	int day = m_date.GetDay();
	CString yearTime;
	CString mounthTime;
	CString dayTime;
	yearTime.Format("%d", year);
	mounthTime.Format("%d", mounth);
	dayTime.Format("%d", day);
	CString timeFinal;
	timeFinal.Format("%s-%s-%s", yearTime, mounthTime, dayTime);

	CADOConn conn;					//�������ݿ������
	conn.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from dairy";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(),
		adOpenDynamic, adLockOptimistic, adCmdText);
	try
	{
		conn.m_pRecordset->AddNew(); //�������
		conn.m_pRecordset->PutCollect("n_content", (_bstr_t)m_content);
		conn.m_pRecordset->PutCollect("n_title", (_bstr_t)m_title);
		conn.m_pRecordset->PutCollect("n_time", (_bstr_t)(timeFinal));
		conn.m_pRecordset->Update(); //�������ݱ�
		conn.ExitConnect();
	}
	catch (...)
	{
		MessageBox("����ʧ��");
		return;
	}
	MessageBox("��ӳɹ�");

}



void CNoteDlg::OnBnClickedChange()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNoteDlg::OnBnClickedDel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}




void CNoteDlg::OnBnClickedClean()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT1)->SetWindowText("");


}




void CNoteDlg::OnBnClickedExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->OnCancel();
}


