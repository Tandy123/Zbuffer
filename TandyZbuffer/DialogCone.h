#pragma once
#include "afxwin.h"


// DialogCone �Ի���

class DialogCone : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCone)

public:
	DialogCone(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogCone();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double radius1;
	double radius2;
	double height;
	int side;
};
