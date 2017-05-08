
// TandyZbuffer.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	//ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CTandyZbufferApp ����

CTandyZbufferApp::CTandyZbufferApp()
{
}

// Ψһ��һ�� CTandyZbufferApp ����

CTandyZbufferApp theApp;


// CTandyZbufferApp ��ʼ��

BOOL CTandyZbufferApp::InitInstance()
{
	CWinApp::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTandyZbufferDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CTandyZbufferView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//���ó������
	m_pMainWnd->SetWindowText(_T("ScanLineZbufferV1.0"));

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

//int CTandyZbufferApp::ExitInstance()
//{
//	//TODO: �����������ӵĸ�����Դ
//	AfxOleTerm(FALSE);
//
//	return CWinApp::ExitInstance();
//}

// CTandyZbufferApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���



CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CTandyZbufferApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}