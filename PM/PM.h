
// PM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include"PMDlg.h"

// CPMApp: 
// �йش����ʵ�֣������ PM.cpp
//

class CPMApp : public CWinApp
{
public:
	CPMApp();

private:
	CPMDlg* m_pPMDlg;

// ��д
public:
//	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

extern CPMApp theApp;