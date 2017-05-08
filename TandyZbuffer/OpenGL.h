#ifndef OPENGL_H
#define OPENGL_H

#include <gl/GL.h>
#include <gl/GLU.h>
#include "EngineInterface.h"
#include "Obj.h"

//导入opengl库
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")


class OpenGL : public EngineInterface{
public:

	OpenGL(){}

	~OpenGL();

	//---初使化OPENGL，使之与环境相符---
	bool Initialize(int w,int h, WinHWND mainWin,bool fullScreen);	

	//--关闭引擎
	void Shutdown();

	//--设置背景颜色 
	void SetClearCol(float r, float g, float b);

	//--开始渲染
	void StartRender(bool bColor, bool bDepth, bool bStencil);

	//--结束渲染
	void EndRendering();

	void ClearBuffers(bool bColor, bool bDepth, bool bStencil);
	void CalculateProjMatrix(float fov, float n, float f);
	void CalculateOrthoMatrix(float n, float f);
	int CreateStaticBuffer(VertexType, PrimType,
		int totalVerts, int totalIndices,
		int stride, void **data, unsigned int *indices,
		int *staticId);

	//--旋转
	void RotateObject(double x,double y);

	//--渲染
	int Render(int staticId);

	//--设置视口
	void SetViewport(int x,int y,unsigned int w,unsigned int h);

	//--填充顶点和面信息
	bool createVertexFace(Obj* obj);

	//--绘制初使化
	bool renderInitial();

	//--设置引擎信息
	void RegisterObjectInfo(double scale,  Triple<double> &center);

	//--把模型放在视口中
	void FocusObject();
	void AntiAliasing(bool anti);
	void ZoomObject(double);

private:
	//---设置OPENGL状态--- 
	void OneTimeInit();
	void setStatus();	// 只能内部调用，由Initialize调用过

	HGLRC m_render_contex;	// 绘制上下文
};

//生成opengl引擎 
bool CreateOpenGLRenderer(EngineInterface **pObj);

#endif