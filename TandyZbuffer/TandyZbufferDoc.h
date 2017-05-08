
// TandyZbufferDoc.h : CTandyZbufferDoc ��Ľӿ�
//


#pragma once
#include "Mesh.h"

class CTandyZbufferDoc : public CDocument
{
protected: // �������л�����
	CTandyZbufferDoc();
	DECLARE_DYNCREATE(CTandyZbufferDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CTandyZbufferDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
	//����ģ��
	bool LoadMesh(const char * file_path,EngineMain *rmain);
	bool IsMeshValid(){return m_mesh->IsValid();}
	bool Tetrahedron(EngineMain *rmain);
	bool Cone(double r1,double r2, double h,int side,EngineMain *rmain);
	bool Box(EngineMain *rmain);
	bool Attachment(EngineMain *rmain);
public:
	Mesh *m_mesh;
};
