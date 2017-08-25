/*
#include "stdafx.h"
#include "ADOConn.h"


CADOConn::CADOConn()
{
}


CADOConn::~CADOConn()
{
}
*/

// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PM.h"
#include "ADOConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CADOConn::CADOConn()
{

}

CADOConn::~CADOConn()
{

}
void CADOConn::OnInitADOConn()
{
	//初始化OLE/COM库环境
	::CoInitialize(NULL);
	try
	{
		//创建connection对象
		m_pConnection.CreateInstance("ADODB.Connection");
		//设置连接字符串


		//_bstr_t strConnect = "uid=;pwd=;DRIVER={Microsoft Access Driver (*.mdb)};\
							 			DBQ=schedule.mdb;Data Source=E:\\DataKU_s\\schedule.mdb;";
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\DataKU_s\\PM.mdb;", "", "", -1);   //打开连接

		//UID,PWD根据实际情况来设置
		//m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	//捕捉异常
	catch (_com_error e)
	{
		//显示错误信息
		AfxMessageBox(e.Description());
	}
}

void CADOConn::ExitConnect()
{
	//关闭记录集和连接
	if (m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	//释放环境
	::CoUninitialize();

}

_RecordsetPtr& CADOConn::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if (m_pConnection == NULL)
			OnInitADOConn();
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordset;
}

BOOL CADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	try
	{
		//是否已连接数据库
		if (m_pConnection == NULL)
			OnInitADOConn();
		m_pConnection->Execute(bstrSQL, NULL, adCmdText);
		return true;
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());							//显示错误信息
		return false;
	}
}

