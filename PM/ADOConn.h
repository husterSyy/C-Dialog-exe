#pragma once

#import "C:\Program Files\Common Files\System\ado\msado15.dll"no_namespace rename("EOF","adoEOF")

class CADOConn
{
public:
	BOOL ExecuteSQL(_bstr_t bstrSQL);

	CADOConn();
	virtual ~CADOConn();

	//添加一个指向Connection对象的指针
	_ConnectionPtr m_pConnection;
	//添加一个指向Recordset对象的指针
	_RecordsetPtr m_pRecordset;
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	void ExitConnect();
	void OnInitADOConn();
};