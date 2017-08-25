// FestvialDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PM.h"
#include "FestvialDlg.h"
#include "afxdialogex.h"
#include"ADOConn.h"


// CFestvialDlg 对话框

IMPLEMENT_DYNAMIC(CFestvialDlg, CDialog)

CFestvialDlg::CFestvialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFestvialDlg::IDD, pParent)
	, m_title(_T(""))
	, m_content(_T(""))
	, m_date(COleDateTime::GetCurrentTime())
{

}

CFestvialDlg::~CFestvialDlg()
{
}

void CFestvialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Control(pDX, IDC_COMBO1, m_Title);
	DDX_CBString(pDX, IDC_COMBO1, m_title);
	DDX_Text(pDX, IDC_EDIT4, m_content);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
}


BEGIN_MESSAGE_MAP(CFestvialDlg, CDialog)
	
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CFestvialDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CFestvialDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON3, &CFestvialDlg::OnBnClickedChange)
	ON_BN_CLICKED(IDC_BUTTON4, &CFestvialDlg::OnBnClickedDelet)
	ON_BN_CLICKED(IDC_BUTTON5, &CFestvialDlg::OnBnClickedClean)
	ON_BN_CLICKED(IDC_BUTTON7, &CFestvialDlg::OnBnClickedExit)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CFestvialDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CFestvialDlg 消息处理程序



void CFestvialDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	//得到当前选择的行号
	int nItem = -1;
	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		nItem = lpNMItemActivate->iItem;
	}
	//设置当前行号的内容
	m_Grid.GetItemText(nItem, 1);
	m_Grid.GetItemText(nItem, 2);
	SetDlgItemText(IDC_STATIC3, "标题：" + m_Grid.GetItemText(nItem, 1) + "\n" + "内容：" + m_Grid.GetItemText(nItem, 2));


}

void CFestvialDlg::AddToGrid()
{
	CADOConn dq_m_ADOConn;       // ADOConn类对象
	dq_m_ADOConn.OnInitADOConn(); //连接数据库
	CString dq_sql;
	int dq_ii = 0;
	dq_sql.Format("select * from festival");                         //设置查询语句
	dq_m_ADOConn.m_pRecordset = dq_m_ADOConn.GetRecordSet((_bstr_t)dq_sql); //查询
	while (!dq_m_ADOConn.m_pRecordset->adoEOF)
	{
		//向列表视图控件中插入行IDC_STATIC_ZZH_CONTENTIDC_STATIC_ZZH_TITLE
		m_Grid.InsertItem(dq_ii, "");
		//向列表视图控件中插入列
		m_Grid.SetItemText(dq_ii, 0, (char*)(_bstr_t)dq_m_ADOConn.m_pRecordset->GetCollect("time"));
		m_Grid.SetItemText(dq_ii, 1, (char*)(_bstr_t)dq_m_ADOConn.m_pRecordset->GetCollect("name"));
		m_Grid.SetItemText(dq_ii, 2, (char*)(_bstr_t)dq_m_ADOConn.m_pRecordset->GetCollect("content"));
		dq_m_ADOConn.m_pRecordset->MoveNext(); //将记录集指针移动到下一条记录
		dq_ii++;

	}
	dq_m_ADOConn.ExitConnect(); //断开数据库连接
}
BOOL CFestvialDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB
		| LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0, "日程时间", LVCFMT_LEFT, 160, 0);
	m_Grid.InsertColumn(1, _T("日程标题"), LVCFMT_LEFT, 180, 1);
	m_Grid.InsertColumn(2, _T("日程内容"), LVCFMT_LEFT, 280, 2);
	AddToGrid();//将数据库中的数据插入到列表视图控件中	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CFestvialDlg::OnBnClickedAdd()
{
	// TODO:  在此添加控件通知处理程序代码

	/*

	UpdateData(TRUE);
	CADOConn conn;
	if (m_title.IsEmpty() || m_content.IsEmpty())
	{
		MessageBox("请输入内容！");
		return;
	}
	conn.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from festival";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(), adOpenDynamic,
		adLockOptimistic, adCmdText);
	try
	{
		conn.m_pRecordset->AddNew(); //添加新行
		conn.m_pRecordset->PutCollect("time", (_variant_t)m_date);
		conn.m_pRecordset->PutCollect("name", (_bstr_t)m_title);
		conn.m_pRecordset->PutCollect("content", (_bstr_t)m_content);
		conn.m_pRecordset->Update();
		conn.ExitConnect();
	}
	catch (...)
	{
		MessageBox("操作失败");
		return;
	}
	MessageBox("添加成功");
	m_Grid.DeleteAllItems();
	AddToGrid();
	*/

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
		MessageBox("请输入内容！");
		return;
	}
	conn.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from festival";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(), adOpenDynamic,
		adLockOptimistic, adCmdText);
	try
	{
		conn.m_pRecordset->AddNew(); //添加新行
		conn.m_pRecordset->PutCollect("time", (_bstr_t)timeFinal);
		conn.m_pRecordset->PutCollect("name", (_bstr_t)m_title);
		conn.m_pRecordset->PutCollect("content", (_bstr_t)m_content);
		conn.m_pRecordset->Update();
		conn.ExitConnect();
	}
	catch (...)
	{
		MessageBox("操作失败");
		return;
	}
	MessageBox("添加成功");

	m_Grid.DeleteAllItems();
	AddToGrid();







}




void CFestvialDlg::OnBnClickedChange()
{
	// TODO:  在此添加控件通知处理程序代码

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
		MessageBox("基础信息不能为空！");
		return;
	}

	conn.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from festival";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(), adOpenDynamic,
		adLockOptimistic, adCmdText);
	try
	{
		conn.m_pRecordset->Move((long)pos, vtMissing);
		conn.m_pRecordset->PutCollect("time", (_bstr_t)timeFinal);
		conn.m_pRecordset->PutCollect("name", (_bstr_t)m_title);
		conn.m_pRecordset->PutCollect("content", (_bstr_t)m_content);
		conn.m_pRecordset->Update();
		conn.ExitConnect();
	}
	catch (...)
	{
		MessageBox("操作失败");
		return;
	}
	MessageBox("修改成功");

	m_Grid.DeleteAllItems();
	AddToGrid();
}



void CFestvialDlg::OnBnClickedDelet()
{
	// TODO:  在此添加控件通知处理程序代码
	pos = m_Grid.GetSelectionMark();
	CADOConn conn;
	conn.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from festival";
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
		MessageBox("操作失败");
		return;
	}
	MessageBox("删除成功");

	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT4)->SetWindowText("");
	SetDlgItemText(IDC_STATIC3, "");

	m_Grid.DeleteAllItems();
	AddToGrid();


}





void CFestvialDlg::OnBnClickedClean()
{
	// TODO:  在此添加控件通知处理程序代码

	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT4)->SetWindowText("");
}


void CFestvialDlg::OnBnClickedExit()
{
	// TODO:  在此添加控件通知处理程序代码
	this->OnCancel();

}




void CFestvialDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;


	//得到当前选择的行号
	int nItem = -1;
	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		nItem = lpNMItemActivate->iItem;
	}
	//设置当前行号的内容
	m_Grid.GetItemText(nItem, 1);
	m_Grid.GetItemText(nItem, 2);
	SetDlgItemText(IDC_STATIC3, "标题：" + m_Grid.GetItemText(nItem, 1) + "\n" + "内容：" + m_Grid.GetItemText(nItem, 2));
}
