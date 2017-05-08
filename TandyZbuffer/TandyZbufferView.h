
// TandyZbufferView.h : CTandyZbufferView 类的接口
//

#pragma once
#include "EngineMain.h"
#include "DialogCone.h"

class CTandyZbufferView : public CView
{
protected: // 仅从序列化创建
	CTandyZbufferView();
	DECLARE_DYNCREATE(CTandyZbufferView)

// 特性
public:
	CTandyZbufferDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CTandyZbufferView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void onRenderSoft();
	afx_msg void OnRenderHardOpenGL();
	afx_msg void OnRotateAutomatic();
	afx_msg void OnRotateManual();
	afx_msg void OnAutoManual();
	afx_msg void OnDrawTetrahedron();
	afx_msg void OnUpdateRenderSoft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenderHardOpenGL(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRotateManual(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAutoManual(CCmdUI *pCmdUI);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
	//些枚举变量
	enum {renderSoft,renderHardOpenGL,
		rotateManual,rotateManualAuto};
	CClientDC* m_dcptr;//渲染区域
	UINT_PTR m_draw_timer,m_statistic_timer;//统计FPS
	EngineMain *m_viewengine;//引擎控制
	int m_render_mode;	// 渲染方式(软件或硬件)
	int m_rotate_mode;	// 旋转控制(自动或人为或自动+人为)
	int m_anti_mode;	// 是否反走样
	int m_framecount;	// 帧统计 
	double m_dx,m_dy;	// 旋转的中心坐标	

	afx_msg void OnTimer(UINT_PTR nIDEvent);	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	// 必须修改，否则会闪烁
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	afx_msg void OnDrawCone();
	afx_msg void OnAppAbout();
	afx_msg void OnBox();
	afx_msg void OnAttachment();
};

#ifndef _DEBUG  // TandyZbufferView.cpp 中的调试版本
inline CTandyZbufferDoc* CTandyZbufferView::GetDocument() const
   { return reinterpret_cast<CTandyZbufferDoc*>(m_pDocument); }
#endif

