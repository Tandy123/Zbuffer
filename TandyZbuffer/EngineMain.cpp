#include "stdafx.h"
#include "EngineMain.h"

EngineMain::EngineMain()
{
	m_engine = NULL;
	m_render_mode = RENDER_OPENGL;
}


EngineMain::~EngineMain()
{
	RenderShutdown();
}


//初使化引擎，生成OPENGL
bool EngineMain::InitializeEngine(WinHWND hwd)
{

	//生成引擎
	if(!CreateOpenGLRenderer(&m_engine))
			return false;

	//初使化引擎
	if(!m_engine->Initialize(0,0,hwd,0))
		return false;

	//设置背景颜色
	m_engine->SetClearCol(135.0f/255.0f,206.0f/255.0f,235.0f/255.0f);
	
	return true;
}


//旋转模型
void EngineMain::RotateObject(double x,double y)
{
	m_engine->RotateObject(x,y);
}


//关闭引擎
void EngineMain::ShutDownEngine()
{
	if(m_engine)
	{
		m_engine->Shutdown();
		delete m_engine;
		m_engine = NULL;
	}
}


//渲染
void EngineMain::RenderLoop()
{
	if(!m_engine)
		return ;
	m_engine->StartRender(1,1,1);

	m_engine->EndRendering();
}


//关闭引擎
void EngineMain::RenderShutdown()
{
	delete m_engine;
}


//设置视口
void EngineMain::SetViewport(int x,int y,unsigned int w,unsigned int h)
{
	m_engine->SetViewport(x,y,w,h);

}


bool EngineMain::RenderLoopObj(Obj *obj,int render_mode)
{
	m_render_mode = RENDER_OPENGL;

	m_engine->StartRender(1,1,0);	// 设置颜色、深度量
	m_engine->renderInitial();	// 渲染初使设置
	m_engine->createVertexFace(obj);//填充顶点、面、法线数据
	m_engine->EndRendering();	// 结束渲染
	
	return true;
}


//设置引擎中的模型信息
void EngineMain::RegisterObjectInfo(double scale,  Triple<double> &center)
{
	//填充顶点、面、法线数据
	m_engine->RegisterObjectInfo(scale,center);
}


//主要是把模型放在屏幕的中间的位置
void EngineMain::FocusObject()
{
	//填充顶点、面、法线数据
	m_engine->FocusObject();
}


bool EngineMain::RenderInitialize()
{
	return true;
}


//放大缩小模型
void EngineMain::ZoomObject(double z_delta)
{
	m_engine->ZoomObject(z_delta * 0.001);
}
