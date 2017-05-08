
// TandyZbufferView.cpp : CTandyZbufferView ���ʵ��
//

#include "stdafx.h"
#include "TandyZbuffer.h"

#include "TandyZbufferDoc.h"
#include "TandyZbufferView.h"

#include "DialogCone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTandyZbufferView

IMPLEMENT_DYNCREATE(CTandyZbufferView, CView)

BEGIN_MESSAGE_MAP(CTandyZbufferView, CView)
	ON_COMMAND(ID_32776, &CTandyZbufferView::OnDrawTetrahedron)
	ON_COMMAND(ID_FILE_OPEN, &CTandyZbufferView::OnFileOpen)
	ON_COMMAND(ID_32780, &CTandyZbufferView::onRenderSoft)
	ON_COMMAND(ID_32781, &CTandyZbufferView::OnRenderHardOpenGL)
	ON_COMMAND(ID_32788, &CTandyZbufferView::OnRotateAutomatic)
	ON_COMMAND(ID_32787, &CTandyZbufferView::OnRotateManual)
	ON_COMMAND(ID_32789, &CTandyZbufferView::OnAutoManual)
	ON_UPDATE_COMMAND_UI(ID_32780, &CTandyZbufferView::OnUpdateRenderSoft)
	ON_UPDATE_COMMAND_UI(ID_32781, &CTandyZbufferView::OnUpdateRenderHardOpenGL)
	ON_UPDATE_COMMAND_UI(ID_32787, &CTandyZbufferView::OnUpdateRotateManual)
	ON_UPDATE_COMMAND_UI(ID_32789, &CTandyZbufferView::OnUpdateAutoManual)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_32777, &CTandyZbufferView::OnDrawCone)
	ON_COMMAND(ID_APP_ABOUT, &CTandyZbufferView::OnAppAbout)
	ON_COMMAND(ID_32790, &CTandyZbufferView::OnBox)
	ON_COMMAND(ID_32791, &CTandyZbufferView::OnAttachment)
END_MESSAGE_MAP()

// CTandyZbufferView ����/����

CTandyZbufferView::CTandyZbufferView()
{
	// TODO: �ڴ˴���ӹ������
	m_viewengine = new EngineMain;	// ��������
	m_render_mode = renderSoft;		// �������
	m_rotate_mode = rotateManualAuto;	// �Զ�+�˹�
	m_framecount = -1;		// ֡����
	m_dcptr = NULL;	

}

CTandyZbufferView::~CTandyZbufferView()
{
	if(m_viewengine){
		delete m_viewengine;	// ɾ������
		m_viewengine = NULL;
	}
	if(m_dcptr){
		delete m_dcptr;
		m_dcptr = NULL;
	}
}

BOOL CTandyZbufferView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
}

// CTandyZbufferView ����

void CTandyZbufferView::OnDraw(CDC* /*pDC*/)
{
	CTandyZbufferDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	m_viewengine->setColor(135.0f/255.0f,206.0f/255.0f,235.0f/255.0f);	// ���ñ�����ɫ 
	pDoc->m_mesh->Draw(m_viewengine,m_render_mode);	// ��ʼ����
	SwapBuffers(wglGetCurrentDC());	// ��������

	if(m_rotate_mode==rotateManual){	// �ֶ�ҲҪ��ʾ��״̬��
		char info[256];
		sprintf_s(info,"vertexes: %d , faces: %d .",
			GetDocument()->m_mesh->getVertexNum(),
			GetDocument()->m_mesh->getFaceNum());
		CStatusBar* barPtr =
			(CStatusBar*)(AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR));
		if(barPtr)
			barPtr->SetPaneText(0,info);
	}
}


// CTandyZbufferView ���

#ifdef _DEBUG
void CTandyZbufferView::AssertValid() const
{
	CView::AssertValid();
}

void CTandyZbufferView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTandyZbufferDoc* CTandyZbufferView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTandyZbufferDoc)));
	return (CTandyZbufferDoc*)m_pDocument;
}
#endif //_DEBUG


// CTandyZbufferView ��Ϣ�������

void CTandyZbufferView::OnFileOpen()
{
	// TODO: �ڴ���������������
	static const char kFileTypes[] = "OBJ files (*.obj)|*.obj|All Files (*.*)|*.*||";
	//���ļ�����
	static CFileDialog FOpenDlg(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST|OFN_ENABLESIZING, (LPCTSTR) kFileTypes);
	if (FOpenDlg.DoModal() == IDOK) {
		if (GetDocument()->LoadMesh((FOpenDlg.GetPathName()),m_viewengine)) {
		}
		else{
			MessageBox(_T("Failed to load .obj file!"), _T("Error"));
		}
	}

	//���»��ƻ���
	RedrawWindow();
}
void CTandyZbufferView::OnDrawTetrahedron()
{
	// TODO: �ڴ���������������
	GetDocument()->Tetrahedron(m_viewengine);
}

//�����������
void CTandyZbufferView::onRenderSoft()
{
	m_render_mode = renderSoft;
	RedrawWindow();
}


void CTandyZbufferView::OnRenderHardOpenGL()
{
	m_render_mode = renderHardOpenGL;
	RedrawWindow();
}


void CTandyZbufferView::OnAutoManual()
{
	OnRotateAutomatic();	// �Զ�
	m_rotate_mode = rotateManualAuto;	// ����ģʽ
	RedrawWindow();
}


void CTandyZbufferView::OnRotateAutomatic()
{
	//10�������һ��
	m_draw_timer = SetTimer(1,10,NULL);	
	//1000����(1��)����FPS������״̬��
	m_statistic_timer= SetTimer(2,1000,NULL);
	//m_rotate_mode=rotateAutomatic;

	m_dx = (rand()-rand())*1e-5;
	m_dy = (rand()-rand())*1e-5;
	
	m_framecount = -1;
	RedrawWindow();
}


void CTandyZbufferView::OnRotateManual()
{
	KillTimer(m_draw_timer);
	KillTimer(m_statistic_timer);
	m_rotate_mode = rotateManual;
	RedrawWindow();
}


void CTandyZbufferView::OnUpdateRenderSoft(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_render_mode==renderSoft);
}


void CTandyZbufferView::OnUpdateRenderHardOpenGL(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_render_mode==renderHardOpenGL);
}


void CTandyZbufferView::OnUpdateRotateManual(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_rotate_mode==rotateManual);
}


void CTandyZbufferView::OnUpdateAutoManual(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_rotate_mode==rotateManualAuto);
}


int CTandyZbufferView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//��ʾλ��
	m_dcptr = new CClientDC(this);
	//��ʹ������
	m_viewengine->InitializeEngine(*m_dcptr);
	//Ĭ�����Զ���ת+�˹�
	OnAutoManual();

	return 0;
}


void CTandyZbufferView::OnTimer(UINT_PTR nIDEvent)
{
	if(!GetDocument()->IsMeshValid())
		return ;
	switch(nIDEvent){
		case 1:	
			if(m_framecount==-1)
				m_framecount =0;
			++m_framecount;
			m_viewengine->RotateObject(m_dx,m_dy);
			//���»���
			RedrawWindow();
			break;
		case 2:	{//����״̬��
			static char info[256];
			if(m_framecount>=100){
				m_framecount = 100;
			}
			sprintf_s(info,"vertexes: %d , faces: %d , FPS: %d",
				GetDocument()->m_mesh->getVertexNum(),
				GetDocument()->m_mesh->getFaceNum(),
				m_framecount);
			m_framecount = -1;
			CStatusBar* barPtr =
				(CStatusBar*)(AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR));
			if(barPtr)
				barPtr->SetPaneText(0,info);
			break;
		}
		default:
			break;
	}
}


void CTandyZbufferView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	//�����ӿ�λ��
	m_viewengine->SetViewport(0,0,cx,cy);
	RedrawWindow();
	// TODO: Add your message handler code here
}


void CTandyZbufferView::OnDestroy()
{
	delete m_dcptr;
	m_dcptr = NULL;
	delete m_viewengine;
	m_viewengine = NULL;

	CView::OnDestroy();
}


void CTandyZbufferView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!GetDocument()->IsMeshValid())
		return ;
	if(!(m_rotate_mode==rotateManualAuto || m_rotate_mode==rotateManual))
		return;
	static CPoint last(-1, -1);
	if (nFlags & MK_LBUTTON) {
		if (last.x < 0 || last.y < 0) last = point;
		m_viewengine->RotateObject(point.x - last.x, point.y - last.y);
		last = point;
		RedrawWindow();
	} else {
		last.x = last.y = -1;
	}
}


BOOL CTandyZbufferView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;
}


BOOL CTandyZbufferView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(!GetDocument()->IsMeshValid())
		return false;
	m_viewengine->ZoomObject(zDelta);
	RedrawWindow();
	return true;
}

void CTandyZbufferView::OnDrawCone()
{
	// TODO: �ڴ���������������
	DialogCone DlgCone;
	if(DlgCone.DoModal()== IDOK)
	{
		double r1 = DlgCone.radius1;
		double r2 = DlgCone.radius2;
		double h = DlgCone.height;
		int side = DlgCone.side;
		GetDocument()->Cone(r1,r2,h,side,m_viewengine);
	}
}


void CTandyZbufferView::OnAppAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CTandyZbufferView::OnBox()
{
	// TODO: �ڴ���������������
	GetDocument()->Box(m_viewengine);
}


void CTandyZbufferView::OnAttachment()
{
	// TODO: �ڴ���������������
	GetDocument()->Attachment(m_viewengine);
}