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


//��ʹ�����棬����OPENGL
bool EngineMain::InitializeEngine(WinHWND hwd)
{

	//��������
	if(!CreateOpenGLRenderer(&m_engine))
			return false;

	//��ʹ������
	if(!m_engine->Initialize(0,0,hwd,0))
		return false;

	//���ñ�����ɫ
	m_engine->SetClearCol(135.0f/255.0f,206.0f/255.0f,235.0f/255.0f);
	
	return true;
}


//��תģ��
void EngineMain::RotateObject(double x,double y)
{
	m_engine->RotateObject(x,y);
}


//�ر�����
void EngineMain::ShutDownEngine()
{
	if(m_engine)
	{
		m_engine->Shutdown();
		delete m_engine;
		m_engine = NULL;
	}
}


//��Ⱦ
void EngineMain::RenderLoop()
{
	if(!m_engine)
		return ;
	m_engine->StartRender(1,1,1);

	m_engine->EndRendering();
}


//�ر�����
void EngineMain::RenderShutdown()
{
	delete m_engine;
}


//�����ӿ�
void EngineMain::SetViewport(int x,int y,unsigned int w,unsigned int h)
{
	m_engine->SetViewport(x,y,w,h);

}


bool EngineMain::RenderLoopObj(Obj *obj,int render_mode)
{
	m_render_mode = RENDER_OPENGL;

	m_engine->StartRender(1,1,0);	// ������ɫ�������
	m_engine->renderInitial();	// ��Ⱦ��ʹ����
	m_engine->createVertexFace(obj);//��䶥�㡢�桢��������
	m_engine->EndRendering();	// ������Ⱦ
	
	return true;
}


//���������е�ģ����Ϣ
void EngineMain::RegisterObjectInfo(double scale,  Triple<double> &center)
{
	//��䶥�㡢�桢��������
	m_engine->RegisterObjectInfo(scale,center);
}


//��Ҫ�ǰ�ģ�ͷ�����Ļ���м��λ��
void EngineMain::FocusObject()
{
	//��䶥�㡢�桢��������
	m_engine->FocusObject();
}


bool EngineMain::RenderInitialize()
{
	return true;
}


//�Ŵ���Сģ��
void EngineMain::ZoomObject(double z_delta)
{
	m_engine->ZoomObject(z_delta * 0.001);
}
