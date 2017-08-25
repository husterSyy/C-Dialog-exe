// NoteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PM.h"
#include "NoteDlg.h"
#include "afxdialogex.h"
#include"ADOConn.h"


// CNoteDlg 对话框

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


// CNoteDlg 消息处理程序




void CNoteDlg::OnBnClickedAdd()
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
		conn.m_pRecordset->PutCollect("n_content", (_bstr_t)m_content);
		conn.m_pRecordset->PutCollect("n_title", (_bstr_t)m_title);
		conn.m_pRecordset->PutCollect("n_time", (_bstr_t)(timeFinal));
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



void CNoteDlg::OnBnClickedChange()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CNoteDlg::OnBnClickedDel()
{
	// TODO:  在此添加控件通知处理程序代码
}




void CNoteDlg::OnBnClickedClean()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_COMBO1)->SetWindowText("");
	GetDlgItem(IDC_EDIT1)->SetWindowText("");


}




void CNoteDlg::OnBnClickedExit()
{
	// TODO:  在此添加控件通知处理程序代码
	this->OnCancel();
}


