#pragma once
#include "afxwin.h"


// DialogCone 对话框

class DialogCone : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCone)

public:
	DialogCone(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogCone();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double radius1;
	double radius2;
	double height;
	int side;
};
