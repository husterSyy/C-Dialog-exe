// TimeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PM.h"
#include "TimeDlg.h"
#include "afxdialogex.h"
#include"ADOConn.h"
#include"MySingletonClass.h"
#include"MessageDlg.h"
#include"PDairyDlg.h"
#include <mmsystem.h>


#include"iostream"
using namespace std;

// CTimeDlg �Ի���

IMPLEMENT_DYNAMIC(CTimeDlg, CDialog)

CTimeDlg::CTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeDlg::IDD, pParent)
	, m_time(COleDateTime::GetCurrentTime())
	, m_clocktime(COleDateTime::GetCurrentTime())
	, m_title(_T(""))
	, m_content(_T(""))
	
	, m_hour(_T(""))
	, m_minute(_T(""))
	, m_second(_T(""))
{

}

CTimeDlg::~CTimeDlg()
{
	m_content = _T("");
}

void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_Grid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_clocktime);
	DDX_CBString(pDX, IDC_COMBO1, m_title);
	DDX_Text(pDX, IDC_EDIT1, m_content);

	//  DDX_Text(pDX, IDC_EDIT_TIP_CONTENT, m_csTipInfo);
	//	DDX_Control(pDX, IDC_EDIT_TIP_CONTENT, m_content);
	
}


BEGIN_MESSAGE_MAP(CTimeDlg, CDialog)

	//ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BUTTON1, &CTimeDlg::OnBnClickedAdd)
	
	//ON_BN_CLICKED(IDC_BUTTON1, &CTimeDlg::OnBnClickedRemindM)

	ON_BN_CLICKED(IDC_BUTTON3, &CTimeDlg::OnBnClickedChange)

	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CTimeDlg::OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTimeDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_BUTTON5, &CTimeDlg::OnBnClickedCle)
	ON_BN_CLICKED(IDC_BUTTON6, &CTimeDlg::OnBnClickedExit1)

	ON_BN_CLICKED(IDC_BUTTON2, &CTimeDlg::OnBnClickedRemind)
	ON_BN_CLICKED(IDC_BUTTON10, &CTimeDlg::OnBnClickedButton10)
	
END_MESSAGE_MAP()


// CTimeDlg ��Ϣ�������

void CTimeDlg::AddToGrid()
{
	CADOConn conn;       // ADOConn�����
	conn.OnInitADOConn(); //�������ݿ�
	CString dq_sql;
	int dq_ii = 0;
	dq_sql.Format("select * from remindT");                         //���ò�ѯ���
	conn.m_pRecordset = conn.GetRecordSet((_bstr_t)dq_sql); //��ѯ
	while (!conn.m_pRecordset->adoEOF)
	{
		//���б���ͼ�ؼ��в�����IDC_STATIC_ZZH_CONTENTIDC_STATIC_ZZH_TITLE
		m_Grid.InsertItem(dq_ii, "");
		//���б���ͼ�ؼ��в�����
		m_Grid.SetItemText(dq_ii, 0, (char*)(_bstr_t)conn.m_pRecordset->GetCollect("t_time"));
		m_Grid.SetItemText(dq_ii, 1, (char*)(_bstr_t)conn.m_pRecordset->GetCollect("t_title"));
		m_Grid.SetItemText(dq_ii, 2, (char*)(_bstr_t)conn.m_pRecordset->GetCollect("t_content"));
		conn.m_pRecordset->MoveNext(); //����¼��ָ���ƶ�����һ����¼
		dq_ii++;

	}
	conn.ExitConnect(); //�Ͽ����ݿ�����
}



void CTimeDlg::OnBnClickedAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int year = m_time.GetYear();
	int mounth = m_time.GetMonth();
	int day = m_time.GetDay();
	CString yearTime;
	CString mounthTime;
	CString dayTime;
	yearTime.Format("%d", year);
	mounthTime.Format("%d", mounth);
	dayTime.Format("%d", day);
	int hour = m_clocktime.GetHour();
	int minute = m_clocktime.GetMinute();
	int second = m_clocktime.GetSecond();
	CString hourtime;
	CString minutetime;
	CString secondtime;
	hourtime.Format("%d", hour);
	minutetime.Format("%d", minute);
	secondtime.Format("%d", second);
	CString timeFinal;
	timeFinal.Format("%s-%s-%s %s:%s:%s", yearTime, mounthTime, dayTime, hourtime, minutetime, secondtime);
	CADOConn ds;
	if (m_title.IsEmpty() || m_content.IsEmpty())
	{
		MessageBox("���������ݣ�");
		return;
	}
	ds.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from remindT";
	ds.m_pRecordset.CreateInstance(__uuidof(Recordset));
	ds.m_pRecordset->Open(sql, ds.m_pConnection.GetInterfacePtr(), adOpenDynamic,
		adLockOptimistic, adCmdText);
	try
	{
		ds.m_pRecordset->AddNew(); //�������
		ds.m_pRecordset->PutCollect("t_time", (_bstr_t)timeFinal);
		ds.m_pRecordset->PutCollect("t_title", (_bstr_t)m_title);
		ds.m_pRecordset->PutCollect("t_content", (_bstr_t)m_content);
		ds.m_pRecordset->Update();
		ds.ExitConnect();
	}
	catch (...)
	{
		MessageBox("����ʧ��");
		return;
	}
	MessageBox("��ӳɹ�");
	m_Grid.DeleteAllItems();
	AddToGrid();

}



void CTimeDlg::OnBnClickedChange()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	//��ʱ�����ת��
	int year = m_time.GetYear();
	int mounth = m_time.GetMonth();
	int day = m_time.GetDay();
	CString yearTime;
	CString mounthTime;
	CString dayTime;
	yearTime.Format("%d", year);
	mounthTime.Format("%d", mounth);
	dayTime.Format("%d", day);
	int hour = m_clocktime.GetHour();
	int minute = m_clocktime.GetMinute();
	int second = m_clocktime.GetSecond();
	CString hourtime;
	CString minutetime;
	CString secondtime;
	hourtime.Format("%d", hour);
	minutetime.Format("%d", minute);
	secondtime.Format("%d", second);
	CString timeFinal;
	timeFinal.Format("%s-%s-%s %s:%s:%s", yearTime, mounthTime, dayTime, hourtime, minutetime, secondtime);
	if (m_title.IsEmpty() || m_content.IsEmpty())
	{
		MessageBox("������Ϣ����Ϊ�գ�");
		return;
	}
	CADOConn conn;
	conn.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from remindT";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(), adOpenDynamic,
		adLockOptimistic, adCmdText);
	try
	{
		conn.m_pRecordset->Move((long)pos, vtMissing);
		conn.m_pRecordset->PutCollect("t_time", (_bstr_t)timeFinal);
		conn.m_pRecordset->PutCollect("t_title", (_bstr_t)m_title);
		conn.m_pRecordset->PutCollect("t_content", (_bstr_t)m_content);
		conn.m_pRecordset->Update();
		conn.ExitConnect();
	}
	catch (...)
	{
		MessageBox("����ʧ��");
		return;
	}
	MessageBox("�޸ĳɹ�");
	m_Grid.DeleteAllItems();
	AddToGrid();

}




void CTimeDlg::OnBnClickedDel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	pos = m_Grid.GetSelectionMark();
	CADOConn conn;
	conn.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from remindT";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(), adOpenDynamic,
		adLockOptimistic, adCmdText);
	try
	{
		conn.m_pRecordset->Move(pos, vtMissing);
		conn.m_pRecordset->Delete(adAffectCurrent);
		conn.m_pRecordset->Update();
		conn.ExitConnect();
	}
	catch (...)
	{
		MessageBox("����ʧ��");
		return;
	}
	MessageBox("ɾ���ɹ�");

	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT1)->SetWindowText("");
	SetDlgItemText(IDC_STATIC2, "");

	m_Grid.DeleteAllItems();
	AddToGrid();

}



void CTimeDlg::OnBnClickedCle()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT1)->SetWindowText("");

}




void CTimeDlg::OnBnClickedExit1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->OnCancel();
}


void CTimeDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	//�õ���ǰѡ����к�
	int nItem = -1;
	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		nItem = lpNMItemActivate->iItem;
	}
	//���õ�ǰ�кŵ�����
	m_Grid.GetItemText(nItem, 1);
	m_Grid.GetItemText(nItem, 2);
	SetDlgItemText(IDC_STATIC2, "���⣺" + m_Grid.GetItemText(nItem, 1) + "\n" + "���ݣ�" + m_Grid.GetItemText(nItem, 2));
}


BOOL CTimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//OnTimer(1);
	SetTimer(1, 1000, NULL);
	//RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB
		| LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0, "�ճ�ʱ��", LVCFMT_LEFT, 160, 0);
	m_Grid.InsertColumn(1, _T("�ճ̱���"), LVCFMT_LEFT, 180, 1);
	m_Grid.InsertColumn(2, _T("�ճ�����"), LVCFMT_LEFT, 280, 2);
	AddToGrid();//�����ݿ��е����ݲ��뵽�б���ͼ�ؼ���	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//Remind();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CTimeDlg::Remind()
{
	UpdateData(TRUE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int year = m_time.GetYear();
	int mounth = m_time.GetMonth();
	int day = m_time.GetDay();
	CString yearTime;
	CString mounthTime;
	CString dayTime;
	yearTime.Format("%d", year);
	mounthTime.Format("%d", mounth);
	dayTime.Format("%d", day);
	int hour = m_clocktime.GetHour();
	int minute = m_clocktime.GetMinute();
	int second = m_clocktime.GetSecond();
	CString hourtime;
	CString minutetime;
	CString secondtime;
	hourtime.Format("%d", hour);
	minutetime.Format("%d", minute);
	secondtime.Format("%d", second);
	CString timeFinal1;
	timeFinal1.Format("%s-%s-%s %s:%s:%s", yearTime, mounthTime, dayTime, hourtime, minutetime, secondtime);

	CTime time = CTime::GetCurrentTime();//���ϵͳʱ��

	int year2 = time.GetYear();
	int mounth2 = time.GetMonth();
	int day2 = time.GetDay();
	CString yearTime2;
	CString mounthTime2;
	CString dayTime2;
	yearTime2.Format("%d", year2);
	mounthTime2.Format("%d", mounth2);
	dayTime2.Format("%d", day2);
	int hour2 = time.GetHour();
	int minute2 = time.GetMinute();
	int second2 = time.GetSecond();
	CString hourtime2;
	CString minutetime2;
	CString secondtime2;
	hourtime2.Format("%d", hour2);
	minutetime2.Format("%d", minute2);
	secondtime2.Format("%d", second2);
	CString timeFinal2;
	timeFinal2.Format("%s-%s-%s %s:%s:%s", yearTime2, mounthTime2, dayTime2, hourtime2, minutetime2, secondtime2);

	cout << minute << endl;
	if (timeFinal1 == timeFinal2)
		//MessageBox(timeFinal2);
	{
		CMessageDlg dlg;
		dlg.DoModal();
	}
}
void CTimeDlg::OnBnClickedRemind()     //��ȷ��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int year = m_time.GetYear();
	int mounth = m_time.GetMonth();
	int day = m_time.GetDay();
	CString yearTime;
	CString mounthTime;
	CString dayTime;
	yearTime.Format("%d", year);
	mounthTime.Format("%d", mounth);
	dayTime.Format("%d", day);
	int hour = m_clocktime.GetHour();
	int minute = m_clocktime.GetMinute();
	int second = m_clocktime.GetSecond();
	CString hourtime;
	CString minutetime;
	CString secondtime;
	hourtime.Format("%d", hour);
	minutetime.Format("%d", minute);
	secondtime.Format("%d", second);
	CString timeFinal1;
	timeFinal1.Format("%s-%s-%s %s:%s:%s", yearTime, mounthTime, dayTime, hourtime, minutetime, secondtime);

	CTime time = CTime::GetCurrentTime();//���ϵͳʱ��

	int year2 = time.GetYear();
	int mounth2 = time.GetMonth();
	int day2 = time.GetDay();
	CString yearTime2;
	CString mounthTime2;
	CString dayTime2;
	yearTime2.Format("%d", year2);
	mounthTime2.Format("%d", mounth2);
	dayTime2.Format("%d", day2);
	int hour2 = time.GetHour();
	int minute2 = time.GetMinute();
	int second2 = time.GetSecond();
	CString hourtime2;
	CString minutetime2;
	CString secondtime2;
	hourtime2.Format("%d", hour2);
	minutetime2.Format("%d", minute2);
	secondtime2.Format("%d", second2);
	CString timeFinal2;
	timeFinal2.Format("%s-%s-%s %s:%s:%s", yearTime2, mounthTime2, dayTime2, hourtime2, minutetime2, secondtime2);

	cout << minute << endl;
//	if (timeFinal1 == timeFinal2)
		//MessageBox(timeFinal1);
		
	MessageBox(timeFinal2);
}





void CTimeDlg::OnBnClickedButton10()    //���Ѱ�ť
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


	// TODO: Add your control notification handler code here
	// ��ȡ���ں�ʱ��
	//CString csTipDate = _T("");
	CString csTipTime = _T("");
	////
	//GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(csTipDate);
	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowText(csTipTime);

	CMySingletonClass *pMyInstance = CMySingletonClass::GetInstance();
	//pMyInstance->m_csTipDate = csTipDate;
	pMyInstance->m_csTipTime = csTipTime;

	// ��ȡ��������
	UpdateData();
	pMyInstance->m_csTipContent = m_content;

//	MessageBox("ok");
	CDialog::OnOK();
	

}
/*

// ��ʾ��ʾ��Ϣ
void CTimeDlg::ShowTipInfo()
{
	//CMessage dlg;
	//dlg.DoModal();
	MessageBox("hello");
}


// ʱ��ȽϺ���, �ж�ʱ���Ƿ��ѵ�
BOOL CTimeDlg::CompareDateTime()
{
	CTime CurrentTime = CTime::GetCurrentTime(); // ȡ�õ�ǰʱ��
	CString csTime = CurrentTime.Format("%H:%M:%S");
	CString csDate = _T("");
	csDate.Format(_T("%d-%d-%d"),
		CurrentTime.GetYear(),
		CurrentTime.GetMonth(),
		CurrentTime.GetDay());

	CString csTempDate = _T("");
	CString csTempTime = _T("");
	CMySingletonClass *pMyInstance = CMySingletonClass::GetInstance();
	csTempDate = pMyInstance->m_csTipDate;
	if (csTempDate.CompareNoCase(csDate) == 0) // �Ƚ�����
	{
		csTempTime = pMyInstance->m_csTipTime;
		if (csTempTime.CompareNoCase(csTime) == 0) // �Ƚ�ʱ��
		{
			return TRUE;
		}
	}

	return FALSE;
}





void CTimeDlg::OnTimer(UINT nIDEvent)
{


	int hour = m_clocktime.GetHour();
	int minute = m_clocktime.GetMinute();
	int second = m_clocktime.GetSecond();
	CString hourtime;
	CString minutetime;
	CString secondtime;
	hourtime.Format("%d", hour);
	minutetime.Format("%d", minute);
	secondtime.Format("%d", second);
	s = hourtime + "ʱ" + minutetime + "��" + secondtime + "��";
	//��ȡ��ǰϵͳʱ����ʾ����̬�ı���time��
	CTime t = CTime::GetCurrentTime();
	CString str;
	str.Format("%dʱ%d��%d��", t.GetHour(), t.GetMinute(), t.GetSecond());
	//SetDlgItemText(time, str);
	//�жϵ�ǰʱ�����趨ʱ���Ƿ�һ��
	if (s == str)
	{
		ShowTipInfo();
	//	PlaySound("F:\\CloudMusic\\�������.mp3", NULL, SND_FILENAME | SND_ASYNC);
	//	MessageBox(NULL, m_content, MB_OK);
	}

	CDialog::OnTimer(nIDEvent);
}

*/