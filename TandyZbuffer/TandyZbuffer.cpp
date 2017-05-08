
// TandyZbuffer.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "TandyZbuffer.h"
#include "MainFrm.h"

#include "TandyZbufferDoc.h"
#include "TandyZbufferView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTandyZbufferApp

BEGIN_MESSAGE_MAP(CTandyZbufferApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTandyZbufferApp::OnAppAbout)
	// 基于文件的标准文档命令
	//ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CTandyZbufferApp 构造

CTandyZbufferApp::CTandyZbufferApp()
{
}

// 唯一的一个 CTandyZbufferApp 对象

CTandyZbufferApp theApp;


// CTandyZbufferApp 初始化

BOOL CTandyZbufferApp::InitInstance()
{
	CWinApp::InitInstance();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTandyZbufferDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CTandyZbufferView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//设置程序标题
	m_pMainWnd->SetWindowText(_T("ScanLineZbufferV1.0"));

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

//int CTandyZbufferApp::ExitInstance()
//{
//	//TODO: 处理可能已添加的附加资源
//	AfxOleTerm(FALSE);
//
//	return CWinApp::ExitInstance();
//}

// CTandyZbufferApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框



CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CTandyZbufferApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}