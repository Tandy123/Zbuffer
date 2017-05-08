#ifndef OPENGL_H
#define OPENGL_H

#include <gl/GL.h>
#include <gl/GLU.h>
#include "EngineInterface.h"
#include "Obj.h"

//����opengl��
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")


class OpenGL : public EngineInterface{
public:

	OpenGL(){}

	~OpenGL();

	//---��ʹ��OPENGL��ʹ֮�뻷�����---
	bool Initialize(int w,int h, WinHWND mainWin,bool fullScreen);	

	//--�ر�����
	void Shutdown();

	//--���ñ�����ɫ 
	void SetClearCol(float r, float g, float b);

	//--��ʼ��Ⱦ
	void StartRender(bool bColor, bool bDepth, bool bStencil);

	//--������Ⱦ
	void EndRendering();

	void ClearBuffers(bool bColor, bool bDepth, bool bStencil);
	void CalculateProjMatrix(float fov, float n, float f);
	void CalculateOrthoMatrix(float n, float f);
	int CreateStaticBuffer(VertexType, PrimType,
		int totalVerts, int totalIndices,
		int stride, void **data, unsigned int *indices,
		int *staticId);

	//--��ת
	void RotateObject(double x,double y);

	//--��Ⱦ
	int Render(int staticId);

	//--�����ӿ�
	void SetViewport(int x,int y,unsigned int w,unsigned int h);

	//--��䶥�������Ϣ
	bool createVertexFace(Obj* obj);

	//--���Ƴ�ʹ��
	bool renderInitial();

	//--����������Ϣ
	void RegisterObjectInfo(double scale,  Triple<double> &center);

	//--��ģ�ͷ����ӿ���
	void FocusObject();
	void AntiAliasing(bool anti);
	void ZoomObject(double);

private:
	//---����OPENGL״̬--- 
	void OneTimeInit();
	void setStatus();	// ֻ���ڲ����ã���Initialize���ù�

	HGLRC m_render_contex;	// ����������
};

//����opengl���� 
bool CreateOpenGLRenderer(EngineInterface **pObj);

#endif