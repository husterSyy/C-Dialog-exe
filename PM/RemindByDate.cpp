// RemindByDate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PM.h"
#include "RemindByDate.h"
#include "afxdialogex.h"
#include"ADOConn.h"
#include"PMDlg.h"

// CRemindByDate �Ի���

IMPLEMENT_DYNAMIC(CRemindByDate, CDialog)

CRemindByDate::CRemindByDate(CWnd* pParent /*=NULL*/)
	: CDialog(CRemindByDate::IDD, pParent)
	//, m_title(_T(""))


	
//	, m_title(_T(""))

, m_title(_T(""))
{

	m_content = _T("");
	//m_Ctitle = _T("");
	m_date = COleDateTime::GetCurrentTime();

}

CRemindByDate::~CRemindByDate()
{
}

void CRemindByDate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Text(pDX, IDC_EDIT2, m_content);

	//  DDX_Control(pDX, IDC_MainLIST, m_AllCont);


	DDX_CBString(pDX, IDC_COMBO1, m_title);
	//DDX_Control(pDX, IDC_COMBO1, m_Title);
	DDX_Control(pDX, IDC_MainLIST, m_Grid);
}


BEGIN_MESSAGE_MAP(CRemindByDate, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DATEADD, &CRemindByDate::OnBnClickedButtonDateadd)
	
	ON_BN_CLICKED(IDC_DeleteBUTTON, &CRemindByDate::OnBnClickedDeletebutton)
	ON_BN_CLICKED(IDC_BUTTON2, &CRemindByDate::OnBnClickedButtonChange)

	ON_NOTIFY(NM_CLICK, IDC_MainLIST, &CRemindByDate::OnClickMainlist)
	ON_BN_CLICKED(IDC_DeleteBUTTON3, &CRemindByDate::OnBnClickedExit)
	ON_BN_CLICKED(IDC_DeleteBUTTON2, &CRemindByDate::OnBnClickedClean)
END_MESSAGE_MAP()


// CRemindByDate ��Ϣ�������


void CRemindByDate::OnBnClickedButtonDateadd()
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
	CADOConn conn;
//	if (m_content.IsEmpty())
	if (m_title.IsEmpty() || m_content.IsEmpty())
	{
		MessageBox("���������ݣ�");
		return;
	}
	conn.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from remindT";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(), adOpenDynamic,
		adLockOptimistic, adCmdText);
	try
	{
		conn.m_pRecordset->AddNew(); //�������
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
	MessageBox("��ӳɹ�");

	m_Grid.DeleteAllItems();
	AddToGrid();

}



void CRemindByDate::OnBnClickedDeletebutton()
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
	GetDlgItem(IDC_EDIT2)->SetWindowText("");
	
	SetDlgItemText(IDC_STATIC1,"");
	m_Grid.DeleteAllItems();
	AddToGrid();
	


	


}
void CRemindByDate::AddToGrid()
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




void CRemindByDate::OnBnClickedButtonChange()    //�޸�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CADOConn conn;
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
	if (m_content.IsEmpty())
		//if (m_title.IsEmpty() || m_content.IsEmpty())
	{
		MessageBox("������Ϣ����Ϊ�գ�");
		return;
	}

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





BOOL CRemindByDate::OnInitDialog()
{
	CDialog::OnInitDialog();


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//======================================================================
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB
		| LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0, "�ճ�ʱ��", LVCFMT_LEFT, 160, 0);
	m_Grid.InsertColumn(1, _T("�ճ̱���"), LVCFMT_LEFT, 180, 1);
	m_Grid.InsertColumn(2, _T("�ճ�����"), LVCFMT_LEFT, 280, 2);
	AddToGrid();//�����ݿ��е����ݲ��뵽�б���ͼ�ؼ���	



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}




void CRemindByDate::OnClickMainlist(NMHDR *pNMHDR, LRESULT *pResult)        //�����ʾ����ϸ����
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
	SetDlgItemText(IDC_STATIC1, "���⣺" + m_Grid.GetItemText(nItem, 1) + "\n" + "���ݣ�" + m_Grid.GetItemText(nItem, 2));
}


void CRemindByDate::OnBnClickedExit()       //�˳�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->OnCancel();
}



void CRemindByDate::OnBnClickedClean()     //���
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT2)->SetWindowText("");

}
