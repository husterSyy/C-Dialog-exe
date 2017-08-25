// RemindByDate.cpp : 实现文件
//

#include "stdafx.h"
#include "PM.h"
#include "RemindByDate.h"
#include "afxdialogex.h"
#include"ADOConn.h"
#include"PMDlg.h"

// CRemindByDate 对话框

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


// CRemindByDate 消息处理程序


void CRemindByDate::OnBnClickedButtonDateadd()
{
	// TODO:  在此添加控件通知处理程序代码

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
	sql = "select * from remindT";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(), adOpenDynamic,
		adLockOptimistic, adCmdText);
	try
	{
		conn.m_pRecordset->AddNew(); //添加新行
		conn.m_pRecordset->PutCollect("t_time", (_bstr_t)timeFinal);
		conn.m_pRecordset->PutCollect("t_title", (_bstr_t)m_title);
		conn.m_pRecordset->PutCollect("t_content", (_bstr_t)m_content);
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



void CRemindByDate::OnBnClickedDeletebutton()
{
	// TODO:  在此添加控件通知处理程序代码
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
		MessageBox("操作失败");
		return;
	}
	MessageBox("删除成功");

	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT2)->SetWindowText("");
	
	SetDlgItemText(IDC_STATIC1,"");
	m_Grid.DeleteAllItems();
	AddToGrid();
	


	


}
void CRemindByDate::AddToGrid()
{
	CADOConn conn;       // ADOConn类对象
	conn.OnInitADOConn(); //连接数据库
	CString dq_sql;
	int dq_ii = 0;
	dq_sql.Format("select * from remindT");                         //设置查询语句
	conn.m_pRecordset = conn.GetRecordSet((_bstr_t)dq_sql); //查询
	while (!conn.m_pRecordset->adoEOF)
	{
		//向列表视图控件中插入行IDC_STATIC_ZZH_CONTENTIDC_STATIC_ZZH_TITLE
		m_Grid.InsertItem(dq_ii, "");
		//向列表视图控件中插入列
		m_Grid.SetItemText(dq_ii, 0, (char*)(_bstr_t)conn.m_pRecordset->GetCollect("t_time"));
		m_Grid.SetItemText(dq_ii, 1, (char*)(_bstr_t)conn.m_pRecordset->GetCollect("t_title"));
		m_Grid.SetItemText(dq_ii, 2, (char*)(_bstr_t)conn.m_pRecordset->GetCollect("t_content"));
		conn.m_pRecordset->MoveNext(); //将记录集指针移动到下一条记录
		dq_ii++;

	}
	conn.ExitConnect(); //断开数据库连接
}




void CRemindByDate::OnBnClickedButtonChange()    //修改
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
		MessageBox("操作失败");
		return;
	}
	MessageBox("修改成功");

	m_Grid.DeleteAllItems();
	AddToGrid();


}





BOOL CRemindByDate::OnInitDialog()
{
	CDialog::OnInitDialog();


	// TODO:  在此添加额外的初始化

	//======================================================================
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




void CRemindByDate::OnClickMainlist(NMHDR *pNMHDR, LRESULT *pResult)        //点击显示在详细内容
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
	SetDlgItemText(IDC_STATIC1, "标题：" + m_Grid.GetItemText(nItem, 1) + "\n" + "内容：" + m_Grid.GetItemText(nItem, 2));
}


void CRemindByDate::OnBnClickedExit()       //退出
{
	// TODO:  在此添加控件通知处理程序代码
	this->OnCancel();
}



void CRemindByDate::OnBnClickedClean()     //清空
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT2)->SetWindowText("");

}
