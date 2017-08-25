/*
#pragma once
class CMySingletonClass
{
public:
	CMySingletonClass();
	~CMySingletonClass();
};
*/

// MySingletonClass.h: interface for the CMySingletonClass class.
//
//////////////////////////////////////////////////////////////////////


#pragma once


class CMySingletonClass
{
public:
	CMySingletonClass();
	virtual ~CMySingletonClass();

public:
	static CMySingletonClass* m_hSingleInstance;
	static CMySingletonClass* GetInstance();
	void DeleteInstance();

public:
	bool m_bIsGuestUser;
	CString m_csTipDate;
	CString m_csTipTime;
	CString m_csTipContent;
};

//#endif // !defined(AFX_MYSINGLETONCLASS_H__207E7495_282C_471D_917B_529D2C18AC11__INCLUDED_)

