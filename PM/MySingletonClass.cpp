

#include "stdafx.h"
#include "PM.h"
#include "MySingletonClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// 初始化实例句柄
CMySingletonClass* CMySingletonClass::m_hSingleInstance = NULL;

// 初始化变量
CMySingletonClass::CMySingletonClass()
{
	m_bIsGuestUser = false;
	m_csTipDate = _T("");
	m_csTipTime = _T("");
	m_csTipContent = _T("");
}

CMySingletonClass::~CMySingletonClass()
{

}

// 取得实例
CMySingletonClass* CMySingletonClass::GetInstance()
{
	if (NULL == m_hSingleInstance)
	{
		m_hSingleInstance = new CMySingletonClass();
	}

	return m_hSingleInstance;
}

// 删除实例
void CMySingletonClass::DeleteInstance()
{
	if (NULL != m_hSingleInstance)
	{
		delete m_hSingleInstance;
		m_hSingleInstance = NULL;
	}

	return;
}