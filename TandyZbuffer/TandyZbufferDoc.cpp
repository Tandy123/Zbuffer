
// TandyZbufferDoc.cpp : CTandyZbufferDoc ���ʵ��
//

#include "stdafx.h"
#include "TandyZbuffer.h"

#include "TandyZbufferDoc.h"
#include "OpenGL.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTandyZbufferDoc

IMPLEMENT_DYNCREATE(CTandyZbufferDoc, CDocument)

BEGIN_MESSAGE_MAP(CTandyZbufferDoc, CDocument)
END_MESSAGE_MAP()


// CTandyZbufferDoc ����/����

CTandyZbufferDoc::CTandyZbufferDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_mesh = new Mesh;
}

CTandyZbufferDoc::~CTandyZbufferDoc()
{
	delete m_mesh;	// ɾ������,����ڴ�
	m_mesh = NULL;
}

BOOL CTandyZbufferDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTandyZbufferDoc ���л�

void CTandyZbufferDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

// CTandyZbufferDoc ���

#ifdef _DEBUG
void CTandyZbufferDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTandyZbufferDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTandyZbufferDoc ����
//����ģ��
bool CTandyZbufferDoc::LoadMesh(const char * file_path,EngineMain *rmain)
{
	if(!m_mesh->LoadMesh(file_path)){
		return false;
	}
	//rmianΪ������ƣ���ģ�͵Ĵ�С��������Ϣ��¼��������
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//���������ģ�ͷ����ӿ���
	rmain->FocusObject();

	return true;
}

bool CTandyZbufferDoc::Tetrahedron(EngineMain *rmain)
{
	if(!m_mesh->Tetrahedron()){
		return false;
	}
	//rmianΪ������ƣ���ģ�͵Ĵ�С��������Ϣ��¼��������
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//���������ģ�ͷ����ӿ���
	rmain->FocusObject();

	return true;
}
bool CTandyZbufferDoc::Cone(double r1,double r2, double h,int side,EngineMain *rmain)
{
	if(!m_mesh->Cone(r1,r2,h,side)){
		return false;
	}
	//rmianΪ������ƣ���ģ�͵Ĵ�С��������Ϣ��¼��������
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//���������ģ�ͷ����ӿ���
	rmain->FocusObject();

	return true;
}

bool CTandyZbufferDoc::Box(EngineMain *rmain)
{
	if(!m_mesh->Box()){
		return false;
	}
	//rmianΪ������ƣ���ģ�͵Ĵ�С��������Ϣ��¼��������
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//���������ģ�ͷ����ӿ���
	rmain->FocusObject();

	return true;
}

bool CTandyZbufferDoc::Attachment(EngineMain *rmain)
{
	if(!m_mesh->Attachment()){
		return false;
	}
	//rmianΪ������ƣ���ģ�͵Ĵ�С��������Ϣ��¼��������
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//���������ģ�ͷ����ӿ���
	rmain->FocusObject();

	return true;
}