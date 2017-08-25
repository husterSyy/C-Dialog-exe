
// PM.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PM.h"
#include "PMDlg.h"
#include"MySingletonClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPMApp

BEGIN_MESSAGE_MAP(CPMApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPMApp ����

CPMApp::CPMApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPMApp ����

CPMApp theApp;


// CPMApp ��ʼ��

BOOL CPMApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
//	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
//	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
//	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();





    AfxEnableControlContainer();


	// ��ģ̬�Ի���
	m_pPMDlg = new CPMDlg();
	ASSERT_VALID(m_pPMDlg);

	m_pMainWnd = m_pPMDlg;
	if (!m_pPMDlg->Create(IDD_PM_DIALOG))
	{
		return FALSE;
	}

	m_pPMDlg->ShowWindow(SW_HIDE);
	m_pPMDlg->UpdateWindow();


//
//	// ���� shell ���������Է��Ի������
//	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;
//
//	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
//
//	// ��׼��ʼ��
//	// ���δʹ����Щ���ܲ�ϣ����С
//	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
//	// ����Ҫ���ض���ʼ������
//	// �������ڴ洢���õ�ע�����
//	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
//	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
//
	CPMDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
//		// TODO:  �ڴ˷��ô����ʱ��
//		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
    {
//		// TODO:  �ڴ˷��ô����ʱ��
//		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
//
//	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

//	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
//	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}





int CPMApp::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���


	if (m_pPMDlg)
	{
		delete m_pPMDlg;
		m_pPMDlg = NULL;
	}
	ASSERT(m_pPMDlg == NULL);


	CMySingletonClass *pMyInstance = CMySingletonClass::GetInstance();

	if (pMyInstance)
	{
		pMyInstance->DeleteInstance();
	}




	return CWinApp::ExitInstance();
}
