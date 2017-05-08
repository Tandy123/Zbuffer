// DialogCone.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TandyZbuffer.h"
#include "DialogCone.h"
#include "afxdialogex.h"


// DialogCone �Ի���

IMPLEMENT_DYNAMIC(DialogCone, CDialogEx)

DialogCone::DialogCone(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogCone::IDD, pParent)
	, radius1(2)
	, radius2(2)
	, height(3)
	, side(36)
{

}

DialogCone::~DialogCone()
{
}

void DialogCone::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, radius1);
	DDX_Text(pDX, IDC_EDIT1, radius1);
	DDX_Text(pDX, IDC_EDIT2, radius2);
	DDX_Text(pDX, IDC_EDIT3, height);
	DDX_Text(pDX, IDC_EDIT4, side);
}


BEGIN_MESSAGE_MAP(DialogCone, CDialogEx)
END_MESSAGE_MAP()


// DialogCone ��Ϣ�������


