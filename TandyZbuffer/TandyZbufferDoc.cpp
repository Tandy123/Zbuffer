
// TandyZbufferDoc.cpp : CTandyZbufferDoc 类的实现
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


// CTandyZbufferDoc 构造/析构

CTandyZbufferDoc::CTandyZbufferDoc()
{
	// TODO: 在此添加一次性构造代码
	m_mesh = new Mesh;
}

CTandyZbufferDoc::~CTandyZbufferDoc()
{
	delete m_mesh;	// 删除对象,清除内存
	m_mesh = NULL;
}

BOOL CTandyZbufferDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CTandyZbufferDoc 序列化

void CTandyZbufferDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

// CTandyZbufferDoc 诊断

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


// CTandyZbufferDoc 命令
//载入模型
bool CTandyZbufferDoc::LoadMesh(const char * file_path,EngineMain *rmain)
{
	if(!m_mesh->LoadMesh(file_path)){
		return false;
	}
	//rmian为引擎控制，将模型的大小、中心信息记录在引擎里
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//利用引擎把模型放在视口中
	rmain->FocusObject();

	return true;
}

bool CTandyZbufferDoc::Tetrahedron(EngineMain *rmain)
{
	if(!m_mesh->Tetrahedron()){
		return false;
	}
	//rmian为引擎控制，将模型的大小、中心信息记录在引擎里
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//利用引擎把模型放在视口中
	rmain->FocusObject();

	return true;
}
bool CTandyZbufferDoc::Cone(double r1,double r2, double h,int side,EngineMain *rmain)
{
	if(!m_mesh->Cone(r1,r2,h,side)){
		return false;
	}
	//rmian为引擎控制，将模型的大小、中心信息记录在引擎里
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//利用引擎把模型放在视口中
	rmain->FocusObject();

	return true;
}

bool CTandyZbufferDoc::Box(EngineMain *rmain)
{
	if(!m_mesh->Box()){
		return false;
	}
	//rmian为引擎控制，将模型的大小、中心信息记录在引擎里
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//利用引擎把模型放在视口中
	rmain->FocusObject();

	return true;
}

bool CTandyZbufferDoc::Attachment(EngineMain *rmain)
{
	if(!m_mesh->Attachment()){
		return false;
	}
	//rmian为引擎控制，将模型的大小、中心信息记录在引擎里
	rmain->RegisterObjectInfo(m_mesh->getScale(),m_mesh->getCenter());
	//利用引擎把模型放在视口中
	rmain->FocusObject();

	return true;
}