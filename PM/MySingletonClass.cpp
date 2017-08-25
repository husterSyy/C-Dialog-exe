

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
// ��ʼ��ʵ�����
CMySingletonClass* CMySingletonClass::m_hSingleInstance = NULL;

// ��ʼ������
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

// ȡ��ʵ��
CMySingletonClass* CMySingletonClass::GetInstance()
{
	if (NULL == m_hSingleInstance)
	{
		m_hSingleInstance = new CMySingletonClass();
	}

	return m_hSingleInstance;
}

// ɾ��ʵ��
void CMySingletonClass::DeleteInstance()
{
	if (NULL != m_hSingleInstance)
	{
		delete m_hSingleInstance;
		m_hSingleInstance = NULL;
	}

	return;
}