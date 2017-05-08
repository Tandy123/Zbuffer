
// TandyZbufferDoc.h : CTandyZbufferDoc 类的接口
//


#pragma once
#include "Mesh.h"

class CTandyZbufferDoc : public CDocument
{
protected: // 仅从序列化创建
	CTandyZbufferDoc();
	DECLARE_DYNCREATE(CTandyZbufferDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CTandyZbufferDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

public:
	//载入模型
	bool LoadMesh(const char * file_path,EngineMain *rmain);
	bool IsMeshValid(){return m_mesh->IsValid();}
	bool Tetrahedron(EngineMain *rmain);
	bool Cone(double r1,double r2, double h,int side,EngineMain *rmain);
	bool Box(EngineMain *rmain);
	bool Attachment(EngineMain *rmain);
public:
	Mesh *m_mesh;
};
