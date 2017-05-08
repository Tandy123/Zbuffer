
// TandyZbuffer.h : TandyZbuffer 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

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
// CTandyZbufferApp:
// 有关此类的实现，请参阅 TandyZbuffer.cpp
//

class CTandyZbufferApp : public CWinApp
{
public:
	CTandyZbufferApp();


// 重写
public:
	virtual BOOL InitInstance();
	//virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTandyZbufferApp theApp;
