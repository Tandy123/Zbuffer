
// TandyZbufferView.cpp : CTandyZbufferView 类的实现
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

// CTandyZbufferView 构造/析构

CTandyZbufferView::CTandyZbufferView()
{
	// TODO: 在此处添加构造代码
	m_viewengine = new EngineMain;	// 生成引擎
	m_render_mode = renderSoft;		// 软件绘制
	m_rotate_mode = rotateManualAuto;	// 自动+人工
	m_framecount = -1;		// 帧计数
	m_dcptr = NULL;	

}

CTandyZbufferView::~CTandyZbufferView()
{
	if(m_viewengine){
		delete m_viewengine;	// 删除引擎
		m_viewengine = NULL;
	}
	if(m_dcptr){
		delete m_dcptr;
		m_dcptr = NULL;
	}
}

BOOL CTandyZbufferView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
}

// CTandyZbufferView 绘制

void CTandyZbufferView::OnDraw(CDC* /*pDC*/)
{
	CTandyZbufferDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	m_viewengine->setColor(135.0f/255.0f,206.0f/255.0f,235.0f/255.0f);	// 设置背景颜色 
	pDoc->m_mesh->Draw(m_viewengine,m_render_mode);	// 开始绘制
	SwapBuffers(wglGetCurrentDC());	// 交换缓存

	if(m_rotate_mode==rotateManual){	// 手动也要显示出状态栏
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


// CTandyZbufferView 诊断

#ifdef _DEBUG
void CTandyZbufferView::AssertValid() const
{
	CView::AssertValid();
}

void CTandyZbufferView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTandyZbufferDoc* CTandyZbufferView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTandyZbufferDoc)));
	return (CTandyZbufferDoc*)m_pDocument;
}
#endif //_DEBUG


// CTandyZbufferView 消息处理程序

void CTandyZbufferView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	static const char kFileTypes[] = "OBJ files (*.obj)|*.obj|All Files (*.*)|*.*||";
	//打开文件类型
	static CFileDialog FOpenDlg(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST|OFN_ENABLESIZING, (LPCTSTR) kFileTypes);
	if (FOpenDlg.DoModal() == IDOK) {
		if (GetDocument()->LoadMesh((FOpenDlg.GetPathName()),m_viewengine)) {
		}
		else{
			MessageBox(_T("Failed to load .obj file!"), _T("Error"));
		}
	}

	//重新绘制画出
	RedrawWindow();
}
void CTandyZbufferView::OnDrawTetrahedron()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->Tetrahedron(m_viewengine);
}

//采用软件绘制
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
	OnRotateAutomatic();	// 自动
	m_rotate_mode = rotateManualAuto;	// 设置模式
	RedrawWindow();
}


void CTandyZbufferView::OnRotateAutomatic()
{
	//10毫秒绘制一次
	m_draw_timer = SetTimer(1,10,NULL);	
	//1000毫秒(1秒)计算FPS并更新状态栏
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
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_render_mode==renderSoft);
}


void CTandyZbufferView::OnUpdateRenderHardOpenGL(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_render_mode==renderHardOpenGL);
}


void CTandyZbufferView::OnUpdateRotateManual(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_rotate_mode==rotateManual);
}


void CTandyZbufferView::OnUpdateAutoManual(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_rotate_mode==rotateManualAuto);
}


int CTandyZbufferView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//显示位置
	m_dcptr = new CClientDC(this);
	//初使化引擎
	m_viewengine->InitializeEngine(*m_dcptr);
	//默认是自动旋转+人工
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
			//重新绘制
			RedrawWindow();
			break;
		case 2:	{//更新状态栏
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
	//设置视口位置
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CTandyZbufferView::OnBox()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->Box(m_viewengine);
}


void CTandyZbufferView::OnAttachment()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->Attachment(m_viewengine);
}