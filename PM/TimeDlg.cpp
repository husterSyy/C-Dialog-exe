// TimeDlg.cpp : 实现文件
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

// CTimeDlg 对话框

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


// CTimeDlg 消息处理程序

void CTimeDlg::AddToGrid()
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



void CTimeDlg::OnBnClickedAdd()
{
	// TODO:  在此添加控件通知处理程序代码
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
		MessageBox("请输入内容！");
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
		ds.m_pRecordset->AddNew(); //添加新行
		ds.m_pRecordset->PutCollect("t_time", (_bstr_t)timeFinal);
		ds.m_pRecordset->PutCollect("t_title", (_bstr_t)m_title);
		ds.m_pRecordset->PutCollect("t_content", (_bstr_t)m_content);
		ds.m_pRecordset->Update();
		ds.ExitConnect();
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



void CTimeDlg::OnBnClickedChange()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//对时间进行转化
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
		MessageBox("基础信息不能为空！");
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
		MessageBox("操作失败");
		return;
	}
	MessageBox("修改成功");
	m_Grid.DeleteAllItems();
	AddToGrid();

}




void CTimeDlg::OnBnClickedDel()
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
	GetDlgItem(IDC_EDIT1)->SetWindowText("");
	SetDlgItemText(IDC_STATIC2, "");

	m_Grid.DeleteAllItems();
	AddToGrid();

}



void CTimeDlg::OnBnClickedCle()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT1)->SetWindowText("");

}




void CTimeDlg::OnBnClickedExit1()
{
	// TODO:  在此添加控件通知处理程序代码
	this->OnCancel();
}


void CTimeDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
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
	SetDlgItemText(IDC_STATIC2, "标题：" + m_Grid.GetItemText(nItem, 1) + "\n" + "内容：" + m_Grid.GetItemText(nItem, 2));
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
	m_Grid.InsertColumn(0, "日程时间", LVCFMT_LEFT, 160, 0);
	m_Grid.InsertColumn(1, _T("日程标题"), LVCFMT_LEFT, 180, 1);
	m_Grid.InsertColumn(2, _T("日程内容"), LVCFMT_LEFT, 280, 2);
	AddToGrid();//将数据库中的数据插入到列表视图控件中	
	// TODO:  在此添加额外的初始化
	//Remind();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CTimeDlg::Remind()
{
	UpdateData(TRUE);
	// TODO:  在此添加控件通知处理程序代码
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

	CTime time = CTime::GetCurrentTime();//获得系统时间

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
void CTimeDlg::OnBnClickedRemind()     //左确定
{
	// TODO:  在此添加控件通知处理程序代码
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

	CTime time = CTime::GetCurrentTime();//获得系统时间

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





void CTimeDlg::OnBnClickedButton10()    //提醒按钮
{
	// TODO:  在此添加控件通知处理程序代码


	// TODO: Add your control notification handler code here
	// 获取日期和时间
	//CString csTipDate = _T("");
	CString csTipTime = _T("");
	////
	//GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(csTipDate);
	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowText(csTipTime);

	CMySingletonClass *pMyInstance = CMySingletonClass::GetInstance();
	//pMyInstance->m_csTipDate = csTipDate;
	pMyInstance->m_csTipTime = csTipTime;

	// 获取提醒内容
	UpdateData();
	pMyInstance->m_csTipContent = m_content;

//	MessageBox("ok");
	CDialog::OnOK();
	

}
/*

// 显示提示信息
void CTimeDlg::ShowTipInfo()
{
	//CMessage dlg;
	//dlg.DoModal();
	MessageBox("hello");
}


// 时间比较函数, 判断时间是否已到
BOOL CTimeDlg::CompareDateTime()
{
	CTime CurrentTime = CTime::GetCurrentTime(); // 取得当前时间
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
	if (csTempDate.CompareNoCase(csDate) == 0) // 比较日期
	{
		csTempTime = pMyInstance->m_csTipTime;
		if (csTempTime.CompareNoCase(csTime) == 0) // 比较时间
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
	s = hourtime + "时" + minutetime + "分" + secondtime + "秒";
	//获取当前系统时间显示到静态文本框time上
	CTime t = CTime::GetCurrentTime();
	CString str;
	str.Format("%d时%d分%d秒", t.GetHour(), t.GetMinute(), t.GetSecond());
	//SetDlgItemText(time, str);
	//判断当前时间与设定时间是否一致
	if (s == str)
	{
		ShowTipInfo();
	//	PlaySound("F:\\CloudMusic\\告白气球.mp3", NULL, SND_FILENAME | SND_ASYNC);
	//	MessageBox(NULL, m_content, MB_OK);
	}

	CDialog::OnTimer(nIDEvent);
}

*/