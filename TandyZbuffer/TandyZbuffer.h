
// TandyZbuffer.h : TandyZbuffer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};
// CTandyZbufferApp:
// �йش����ʵ�֣������ TandyZbuffer.cpp
//

class CTandyZbufferApp : public CWinApp
{
public:
	CTandyZbufferApp();


// ��д
public:
	virtual BOOL InitInstance();
	//virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTandyZbufferApp theApp;
