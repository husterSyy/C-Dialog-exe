#pragma once

#import "C:\Program Files\Common Files\System\ado\msado15.dll"no_namespace rename("EOF","adoEOF")

class CADOConn
{
public:
	BOOL ExecuteSQL(_bstr_t bstrSQL);

	CADOConn();
	virtual ~CADOConn();

	//���һ��ָ��Connection�����ָ��
	_ConnectionPtr m_pConnection;
	//���һ��ָ��Recordset�����ָ��
	_RecordsetPtr m_pRecordset;
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	void ExitConnect();
	void OnInitADOConn();
};