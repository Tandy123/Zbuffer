#ifndef ENGINEINTERFACE_H_
#define ENGINEINTERFACE_H_


#include "Define.h"
#include "Triple.h"
#include "Obj.h"


class EngineInterface
{
public:

	EngineInterface() : m_screenWidth(0),
		m_screenHeight(0), m_near(0), m_far(0) { }
	virtual ~EngineInterface() {}	

	//---��ʹ��---
	virtual bool Initialize(int w, int h,WinHWND mainWin, bool fullScreen) = 0;	

	//---��ʱ����---
	virtual void OneTimeInit() = 0;

	//---�����Ⱦϵͳ--- 
	virtual void Shutdown() = 0;

	//---����̨������ɫ����Ϊָ����ɫ---
	virtual void SetClearCol(float r, float g, float b) = 0;

	//---�����³���---
	virtual void StartRender(bool bColor, bool bDepth,bool bStencil) = 0;
	
	virtual void ClearBuffers(bool bColor, bool bDepth,
		bool bStencil) = 0;

	//---�����³���---
	virtual void EndRendering() = 0;

	//---����ͶӰ---
	virtual void CalculateProjMatrix(float fov, float n, float f) = 0;

	//---����ͶӰ---
	virtual void CalculateOrthoMatrix(float n, float f) = 0;

	//---������̬���㻺��---
	virtual int CreateStaticBuffer(VertexType, PrimType,
		int totalVerts, int totalIndices,
		int stride, void **data, unsigned int *indices,
		int *staticId) = 0;

	//---������������ʾ����Ļ��
	virtual int Render(int staticId) = 0;

	//---��ת
	virtual void RotateObject(double x,double y)=0;

	//---�ӿ�λ�� 
	virtual void SetViewport(int x,int y,unsigned int w,unsigned int h)=0;

	virtual bool createVertexFace(Obj* obj)=0;
	virtual bool renderInitial()=0;
	virtual void RegisterObjectInfo(double scale,  Triple<double> &center) = 0;
	virtual void FocusObject() =0;
	virtual void AntiAliasing(bool anti) = 0;
	virtual void ZoomObject(double)=0;


protected:	// ������������������ĳ�Ա����
	int m_screenWidth;	// ��Ļ���
	int m_screenHeight;	// ��Ļ�߶�
	bool m_fullscreen;	// �Ƿ�ȫ��

	WinHWND m_mainHandle;//���ھ��

	float m_near;	// ͶӰ����Ľ�����ֵ
	float m_far;	// Զ����ֵ

	double m_z_delta;	// z����
	Triple<double> m_center;	//����λ�� 
	double m_scale;	//��С
};

#endif
