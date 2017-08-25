// PDairyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PM.h"
#include "PDairyDlg.h"
#include "afxdialogex.h"
#include"ADOConn.h"

// CPDairyDlg 对话框

IMPLEMENT_DYNAMIC(CPDairyDlg, CDialog)

CPDairyDlg::CPDairyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPDairyDlg::IDD, pParent)
	, m_title(_T(""))
	//, m_time(COleDateTime::GetCurrentTime())
	, m_date(COleDateTime::GetCurrentTime())
	, m_content(_T(""))
{

}

CPDairyDlg::~CPDairyDlg()
{
}

void CPDairyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Title);
	DDX_CBString(pDX, IDC_COMBO1, m_title);
	//  DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Text(pDX, IDC_EDIT1, m_content);
}


BEGIN_MESSAGE_MAP(CPDairyDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPDairyDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON3, &CPDairyDlg::OnBnClickedChange)
	ON_BN_CLICKED(IDC_BUTTON4, &CPDairyDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_BUTTON5, &CPDairyDlg::OnBnClickedClean)
	ON_BN_CLICKED(IDC_BUTTON6, &CPDairyDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CPDairyDlg 消息处理程序


void CPDairyDlg::OnBnClickedAdd()
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

	CADOConn conn;					//声明数据库类对象
	conn.OnInitADOConn();
	_bstr_t sql;
	sql = "select * from dairy";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(),
		adOpenDynamic, adLockOptimistic, adCmdText);
	try
	{
		conn.m_pRecordset->AddNew(); //添加新行
		conn.m_pRecordset->PutCollect("d_content", (_bstr_t)m_content);
		conn.m_pRecordset->PutCollect("d_title", (_bstr_t)m_title);
		conn.m_pRecordset->PutCollect("d_time", (_bstr_t)(timeFinal));
		conn.m_pRecordset->Update(); //更新数据表
		conn.ExitConnect();
	}
	catch (...)
	{
		MessageBox("操作失败");
		return;
	}
	MessageBox("添加成功");
}




void CPDairyDlg::OnBnClickedChange()
{
	// TODO:  在此添加控件通知处理程序代码

}






void CPDairyDlg::OnBnClickedDel()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//对时间进行转化
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
	CString strTemp1;
	//int iPos=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();//得到当期选中的索引号
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(strTemp1);//得到当前选中的内容
	CADOConn conn;
	conn.OnInitADOConn();
	CString sql_update;
	_bstr_t sql;
	sql = "select * from dairy";
	conn.m_pRecordset.CreateInstance(__uuidof(Recordset));
	conn.m_pRecordset->Open(sql, conn.m_pConnection.GetInterfacePtr(), adOpenDynamic,
		adLockOptimistic, adCmdText);
	CString sql_del;
	sql_del.Format("delete * from dairy where d_time = '%s' and d_title = '%s'", timeFinal, strTemp1);
	conn.ExecuteSQL((_bstr_t)sql_del);
	MessageBox("删除成功");


}




void CPDairyDlg::OnBnClickedClean()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT1)->SetWindowText("");

}


void CPDairyDlg::OnBnClickedExit()
{
	// TODO:  在此添加控件通知处理程序代码
	this->OnCancel();
}


