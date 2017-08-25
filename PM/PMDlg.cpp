
// PMDlg.cpp : 实现文件




#include "stdafx.h"
#include "PM.h"
#include "PMDlg.h"
#include "afxdialogex.h"
#include"ADOConn.h"
#include"RemindByDate.h"
#include"MusicDlg.h"
#include"FestvialDlg.h"
#include"NoteDlg.h"
#include"PDairyDlg.h"
#include"TimeDlg.h"
#include"MessageDlg.h"
#include"MySingletonClass.h"


#include <Vfw.H>
#pragma comment(lib, "VFW32.lib")
#pragma comment(lib, "WINMM.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPMDlg 对话框



CPMDlg::CPMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CPMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_Grid);
}

BEGIN_MESSAGE_MAP(CPMDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_RemindDate, &CPMDlg::OnDate)

	ON_MESSAGE(WM_SHELLNOTIFY, OnShellNotify)
	ON_WM_SIZE()

	ON_COMMAND(ID_RemindTime, &CPMDlg::OnRemindtime)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPMDlg::OnNMClickList1)
	ON_COMMAND(ID_HELP, &CPMDlg::OnHelp)
	ON_COMMAND(ID_Dairy, &CPMDlg::OnDairy)
	ON_COMMAND(ID_Note, &CPMDlg::OnNote)
	ON_COMMAND(ID_Music, &CPMDlg::OnMusic)
	ON_COMMAND(ID_Start, &CPMDlg::OnStart)
	ON_COMMAND(ID_RemindFestival, &CPMDlg::OnRemindfestival)
	ON_COMMAND(ID_MainMenu, &CPMDlg::OnMainmenu)

	//ON_WM_TIMER()

	ON_COMMAND(ID_Exit, &CPMDlg::OnExit)
	
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPMDlg 消息处理程序

BOOL CPMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(3, 1000, NULL);

	InitNotifyIconData();
	CenterWindow();
	//窗口总处于最上面
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	GetWindowPlacement(&m_wndPlaceMent);
	
	// Add "About..." menu item to system menu.


	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_Menu.LoadMenu(IDR_MENU1);  //  菜单
	SetMenu(&m_Menu);

	toolbar();      //小图标

	UINT array[3];					//声明数组
	for (int i = 0; i < 3; i++)
	{
		array[i] = 1010 + i;		//维数组元素赋值
	}
	m_StatusBar.Create(this);		//创建状态栏窗口
	m_StatusBar.SetIndicators(array, sizeof(array) / sizeof(UINT));//添加面板
	CRect rect;//声明区域对象
	GetClientRect(rect);//获得主窗体客户区域
	//CDC* pDC=NULL;
	//pDC->FillSolidRect(rect, RGB(128, 128, 0));    //设置窗口的背景

	for (int n = 0; n < 3; n++)//循环设置面板
	{
		m_StatusBar.SetPaneInfo(n, array[n], 0, rect.Width() / 3);//设置面板高度
	}
	CTime time = CTime::GetCurrentTime();//获得系统时间
	//设置面板文本
	m_StatusBar.SetPaneText(0, _T("系统时间：") + time.Format("%Y-%m-%d "));
	//显示工具栏窗口
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	SetTimer(1, 300, NULL);// 设置定时器

	

	//======================================================================
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB
		| LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0, "日程时间", LVCFMT_LEFT, 160, 0);
	m_Grid.InsertColumn(1, _T("日程标题"), LVCFMT_LEFT, 180, 1);
	m_Grid.InsertColumn(2, _T("日程内容"), LVCFMT_LEFT, 280, 2);
	AddToGrid();//将数据库中的数据插入到列表视图控件中	

  //  OnRemind();

	/*
	HWND hMCI;
	CString choose = _T("F://CloudMusic//告白气球.mp3"); //音乐文件的路径   
	hMCI = MCIWndCreate(NULL, NULL, WS_POPUP | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, choose);
	MCIWndPlay(hMCI); //播放音乐
	*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPMDlg::OnPaint()
{
   //设置背景颜色
	/*
	CRect   rect;
	CPaintDC   dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(128, 128, 0));   //设置为绿色背景
	*/

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPMDlg::OnQueryDragIcon()
{
	//return static_cast<HCURSOR>(m_hIcon);

	return (HCURSOR)m_hIcon;
}

void CPMDlg::toolbar()
{
	
	m_ImageList.Create(32, 32, ILC_COLOR24 | ILC_MASK, 1, 1);	//创建图像列表
	//向图像列表中添加图标
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON8));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON9));

	m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);//创建工具栏
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);	//关联图像列表
	m_ToolBar.SetButtons(NULL, 9);					//共9个按钮
	//设置每个工具栏按钮的ID值和显示文字
	m_ToolBar.SetButtonInfo(0, ID_MainMenu, TBSTYLE_BUTTON, 0);
	m_ToolBar.SetButtonText(0, "主界面");
	m_ToolBar.SetButtonInfo(1, ID_RemindTime, TBSTYLE_BUTTON, 1);
	m_ToolBar.SetButtonText(1, _T("定时提醒"));
	m_ToolBar.SetButtonInfo(2, ID_RemindDate, TBSTYLE_BUTTON, 2);
	m_ToolBar.SetButtonText(2, _T("定期提醒"));
	m_ToolBar.SetButtonInfo(3, ID_RemindFestival, TBSTYLE_BUTTON, 3);
	m_ToolBar.SetButtonText(3, "固定节日提醒");
	m_ToolBar.SetButtonInfo(4, ID_Music, TBSTYLE_BUTTON, 4);
	m_ToolBar.SetButtonText(4, "音乐设定");
	m_ToolBar.SetButtonInfo(5, ID_Dairy, TBSTYLE_BUTTON, 5);
	m_ToolBar.SetButtonText(5, "个人日记");
	m_ToolBar.SetButtonInfo(6, ID_Note, TBSTYLE_BUTTON, 6);
	m_ToolBar.SetButtonText(6, "备忘录");
	m_ToolBar.SetButtonInfo(7, ID_HELP, TBSTYLE_BUTTON, 7);
	m_ToolBar.SetButtonText(7, "帮助");
	m_ToolBar.SetButtonInfo(8, ID_Exit, TBSTYLE_BUTTON, 8);
	m_ToolBar.SetButtonText(8, "退出");


	m_ToolBar.SetSizes(CSize(70, 60), CSize(32, 32));//设置按钮大小
}





void CPMDlg::OnDate()
{
	// TODO:  在此添加命令处理程序代码

	CRemindByDate dlg;
	dlg.DoModal();

}

void CPMDlg::AddToGrid(){
	CADOConn m_ADOConn;       // ADOConn类对象
	m_ADOConn.OnInitADOConn(); //连接数据库
	CString sql;
	int i = 0;
	sql.Format("select * from remindT");                         //设置查询语句
	m_ADOConn.m_pRecordset = m_ADOConn.GetRecordSet((_bstr_t)sql); //查询
	while (!m_ADOConn.m_pRecordset->adoEOF)
	{
		//向列表视图控件中插入行IDC_STATIC_ZZH_CONTENTIDC_STATIC_ZZH_TITLE
		m_Grid.InsertItem(i, "  ");
		//向列表视图控件中插入列
		m_Grid.SetItemText(i, 0, (CString)m_ADOConn.m_pRecordset->GetCollect("t_time"));
		m_Grid.SetItemText(i, 1, (char*)(_bstr_t)m_ADOConn.m_pRecordset->GetCollect("t_title"));
		m_Grid.SetItemText(i, 2, (char*)(_bstr_t)m_ADOConn.m_pRecordset->GetCollect("t_content"));
		m_ADOConn.m_pRecordset->MoveNext(); //将记录集指针移动到下一条记录
		i++;
	}
	m_ADOConn.ExitConnect(); //断开数据库连接
}

void CPMDlg::OnRemindtime()
{
	// TODO:  在此添加命令处理程序代码

	CTimeDlg dlg;
	dlg.DoModal();

}


void CPMDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	//得到当前选择的行号
	int nItem = -1;
	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		nItem = lpNMItemActivate->iItem;
	}
	//设置当前行号的内容
	m_Grid.GetItemText(nItem, 1);
	m_Grid.GetItemText(nItem, 2);
	SetDlgItemText(IDC_STATIC, "标题：" + m_Grid.GetItemText(nItem, 1) + "\n" + "内容：" + m_Grid.GetItemText(nItem, 2));

}


void CPMDlg::OnHelp()
{
	// TODO:  在此添加命令处理程序代码
	CAboutDlg about;
	about.DoModal();


}


void CPMDlg::OnDairy()
{
	// TODO:  在此添加命令处理程序代码
	CPDairyDlg dlg;
	dlg.DoModal();

}


void CPMDlg::OnNote()
{
	// TODO:  在此添加命令处理程序代码
	CNoteDlg dlg;
	dlg.DoModal();
}


void CPMDlg::OnMusic()
{
	// TODO:  在此添加命令处理程序代码
	CMusicDlg dlg;
	dlg.DoModal();
}


void CPMDlg::OnStart()
{
	// TODO:  在此添加命令处理程序代码
	m_uCheckState = !m_uCheckState;//BOOL类型的成员变量  

	HKEY hKey;

	//找到系统的启动项     
	CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

	if (m_uCheckState)
	{
		//打开启动项Key     
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet == ERROR_SUCCESS)
		{
			TCHAR pFileName[MAX_PATH] = { 0 };

			//得到程序自身的全路径     
			DWORD dwRet = GetModuleFileName(NULL, pFileName, MAX_PATH);
			TRACE(pFileName);

			//添加一个子Key,并设置值 // 下面"Demo"是应用程序名字（不需要加后缀.exe）    
			lRet = RegSetValueEx(hKey, _T("Demo"), 0, REG_SZ, (LPBYTE)pFileName, (lstrlen(pFileName) + 1)*sizeof(TCHAR));

			//关闭注册表     
			RegCloseKey(hKey);
			if (lRet != ERROR_SUCCESS)
			{
				MessageBox(_T("系统参数错误,设置自启动失败!"), _T("提示"));
			}
			else
			{
				MessageBox(_T("开机启动设置成功！"), _T("提示"));
			}
		}
		else
		{
			MessageBox(_T("系统参数错误,设置自启动失败!"), _T("提示"));
		}
	}
	else
	{
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet == ERROR_SUCCESS)
		{
			RegDeleteValue(hKey, _T("Demo"));
			//关闭注册表     
			RegCloseKey(hKey);

			MessageBox(_T("关闭开机启动成功！"), _T("提示"));
		}
	}

	
}


void CPMDlg::OnRemindfestival()
{
	// TODO:  在此添加命令处理程序代码
	CFestvialDlg dlg;
	dlg.DoModal();

}


void CPMDlg::OnMainmenu()
{
	// TODO:  在此添加命令处理程序代码
	CPMDlg dlg;
	dlg.DoModal();

}




void CPMDlg::OnExit()
{
	// TODO:  在此添加命令处理程序代码
	this->OnCancel();
}


// 初始化托盘图标
void CPMDlg::InitNotifyIconData()
{
	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	nid.uCallbackMessage = WM_SHELLNOTIFY;

	lstrcpy(nid.szTip, _T("个人日程管理")); // 鼠标移到图标上面时的提示信息

	Shell_NotifyIcon(NIM_ADD, &nid); // 在任务栏右下角添加图标
}

// 弹出式菜单中的退出
void CPMDlg::OnCancel()
{
	DestroyWindow();
}

// 清除托盘图标
void CPMDlg::OnDestroy()
{
	CDialog::OnDestroy();

	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;

	Shell_NotifyIcon(NIM_DELETE, &nid);  // 删除图标
}

// 在图标上按下鼠标左键，显示/隐藏窗口
// 在图标上按下鼠标右键，显示弹出式菜单
LRESULT CPMDlg::OnShellNotify(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_LBUTTONDOWN)
	{
		if (IsWindowVisible())
		{
			ShowWindow(SW_HIDE);  // 隐藏窗口
		}
		else
		{
			SetWindowPlacement(&m_wndPlaceMent);  // 显示窗口
		}
	}

	if (lParam == WM_RBUTTONDOWN)
	{
		PopupMenu();  // 弹出式菜单
	}
	return TRUE;
}

// 弹出式菜单
void CPMDlg::PopupMenu()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menuPopup;

	menuPopup.CreatePopupMenu();  // 创建弹出式菜单
	menuPopup.AppendMenu(MF_STRING, ID_MENUITEM_SHOW, _T("显示"));
	menuPopup.AppendMenu(MF_SEPARATOR);
	menuPopup.AppendMenu(MF_STRING, ID_MENUITEM_EXIT, _T("退出"));

	int nCmd = (int)menuPopup.TrackPopupMenu(\
		TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD, \
		point.x, point.y, \
		AfxGetMainWnd());

	switch (nCmd)
	{
	case ID_MENUITEM_EXIT:  // 退出菜单
		PostMessage(WM_CLOSE);
		break;

	case ID_MENUITEM_SHOW:  // 显示菜单
		SetWindowPlacement(&m_wndPlaceMent);
		break;

	default:
		break;
	}
}


// 隐藏窗口到图标上
void CPMDlg::OnSize(UINT nType, int cx, int cy)
{

	if (nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE);  // 隐藏窗口
	}
}

// 显示提示信息
void CPMDlg::ShowTipInfo()
{
	CMessageDlg dlg;
	dlg.DoModal();
}

// 时间比较函数, 判断时间是否已到
BOOL CPMDlg::CompareDateTime()
{
	CTime CurrentTime = CTime::GetCurrentTime(); // 取得当前时间
	CString csTime = CurrentTime.Format("%H:%M:%S");
	//CString csDate = _T("");
	//csDate.Format(_T("%d-%d-%d"),
		//CurrentTime.GetYear(),
	//	CurrentTime.GetMonth(),
	//	CurrentTime.GetDay());

	//CString csTempDate = _T("");
	CString csTempTime = _T("");
	CMySingletonClass *pMyInstance = CMySingletonClass::GetInstance();
	//csTempDate = pMyInstance->m_csTipDate;
	//if (csTempDate.CompareNoCase(csDate) == 0) // 比较日期
	//{
		csTempTime = pMyInstance->m_csTipTime;
		if (csTempTime.CompareNoCase(csTime) == 0) // 比较时间
		{
			return TRUE;
		}
	//}

	return FALSE;
}



void CPMDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	try
	{
		BOOL bIsJustDateTime = CompareDateTime();
		switch (nIDEvent)
		{
		case 1:
		
			break;

		case 2:
	             
			break;

		case 3:
			if (bIsJustDateTime)
			{
				KillTimer(3);
				ShowTipInfo(); // 显示提示信息
			}
			break;

		default:
			break;
		}
	}
	catch (...)
	{
		KillTimer(nIDEvent);
	}

	CDialog::OnTimer(nIDEvent);

	//CDialogEx::OnTimer(nIDEvent);
}
