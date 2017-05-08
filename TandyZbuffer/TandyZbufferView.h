
// TandyZbufferView.h : CTandyZbufferView ��Ľӿ�
//

#pragma once
#include "EngineMain.h"
#include "DialogCone.h"

class CTandyZbufferView : public CView
{
protected: // �������л�����
	CTandyZbufferView();
	DECLARE_DYNCREATE(CTandyZbufferView)

// ����
public:
	CTandyZbufferDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CTandyZbufferView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
	//Щö�ٱ���
	enum {renderSoft,renderHardOpenGL,
		rotateManual,rotateManualAuto};
	CClientDC* m_dcptr;//��Ⱦ����
	UINT_PTR m_draw_timer,m_statistic_timer;//ͳ��FPS
	EngineMain *m_viewengine;//�������
	int m_render_mode;	// ��Ⱦ��ʽ(�����Ӳ��)
	int m_rotate_mode;	// ��ת����(�Զ�����Ϊ���Զ�+��Ϊ)
	int m_anti_mode;	// �Ƿ�����
	int m_framecount;	// ֡ͳ�� 
	double m_dx,m_dy;	// ��ת����������	

	afx_msg void OnTimer(UINT_PTR nIDEvent);	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	// �����޸ģ��������˸
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	afx_msg void OnDrawCone();
	afx_msg void OnAppAbout();
	afx_msg void OnBox();
	afx_msg void OnAttachment();
};

#ifndef _DEBUG  // TandyZbufferView.cpp �еĵ��԰汾
inline CTandyZbufferDoc* CTandyZbufferView::GetDocument() const
   { return reinterpret_cast<CTandyZbufferDoc*>(m_pDocument); }
#endif

