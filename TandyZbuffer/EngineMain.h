#ifndef _ENGINE_MAIN_H_
#define _ENGINE_MAIN_H_

#include "EngineInterface.h"
#include "OpenGL.h"
#include "Math.h"

class EngineMain {
public:
	enum {RENDER_OPENGL};

	EngineMain();
	~EngineMain();
	bool InitializeEngine(WinHWND hwd);	// ��ʹ������
	void ShutDownEngine();	// �ر�����
	bool RenderInitialize();	// ��ʹ������
	void RenderLoop();		// ��Ⱦ
	bool RenderLoopObj(Obj *obj,int render_mode);	//����Ӳ����ȾOBJ
	void RenderShutdown();	// ��������

	//��ת
	void RotateObject(double x,double y);
	//�����ӿ�λ��
	void SetViewport(int x,int y,unsigned int w,unsigned int h);
	//���������е�ģ����Ϣ
	void RegisterObjectInfo(double scale, Triple<double>& center);
	//��ģ�ͷ����ӿڵ���
	void FocusObject();
	void setColor(float r,float g,float b){m_engine->SetClearCol( r, g, b);}

	void ZoomObject(double z_delta);

private:
	EngineInterface *m_engine;	// ����
	int m_render_mode;	// ��Ⱦ��ʽ 
};

#endif