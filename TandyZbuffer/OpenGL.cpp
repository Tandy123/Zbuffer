#include "stdafx.h"
#include "OpenGl.h"


//�����������ѡ��OPENGL
bool CreateOpenGLRenderer(EngineInterface **pObj)
{
	if(!*pObj) 
		*pObj = new OpenGL;
	else 
		return false;

	return true;
}


OpenGL::~OpenGL()
{
	Shutdown();
}


//��ʹ����������
bool OpenGL::Initialize(int w,int h,WinHWND hdc,bool fullScreen) {

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		::GetDeviceCaps(hdc, BITSPIXEL),	//�õ�������ɫλ�� Number of adjacent color bits for each pixel
		0,0,0,0,0,0,0,0,
		0,0,0,0,0, 
		32,
		0,0, 
		PFD_MAIN_PLANE, 
		0, 
		0,0,0
	};

	//---match an appropriate pixel format supported by a device context to a given pixel format specification.
	int pixel_format;
	if(!(pixel_format = ChoosePixelFormat(hdc, &pfd))){
		//MessageBox("ChoosePixelFormat failed");
		return false;
	}
	//sets the pixel format of the specified device context to the format specified by the iPixelFormat index.
	SetPixelFormat(hdc, pixel_format, &pfd);
	//creates a new OpenGL rendering context, which is suitable for drawing on the device referenced by hdc. 
	//The rendering context has the same pixel format as the device context.
	m_render_contex = wglCreateContext(hdc);

	//makes a specified OpenGL rendering context the calling thread's current rendering context
	wglMakeCurrent(hdc, m_render_contex);

	setStatus();
	return true;
}


//���ó�ʹ״̬
void OpenGL::setStatus()
{
	glDisable(GL_DEPTH_TEST);	// �ر�ZBUFFER��Ȳ���
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);	// ����˫�����,���� ����
	glClearColor(135/255,206/255,235/255,1.0f);	// ����Ļ��ճɵ���ɫ Ĭ��
	glShadeModel(GL_FLAT);	// ʹ����ɫģʽ��ƽ����ɫ
	glEnable(GL_LIGHTING);	// ��������
	glEnable(GL_LIGHT0);	// �������յ�1
	static const float mat_amb_diff[] = {1.0f, 1.0f, 1.0f, 1.0f };	// ����ɢ���ͻ����ⷴ����ɫ
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
	m_z_delta = 0.0;	// ģ�ͷ���������������
	glDisable(GL_DEPTH_TEST);	// ������Ȳ���
}


//��תģ��
void OpenGL::RotateObject(double x,double y)
{
	double modleview_matrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modleview_matrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//���Ƶ�ԭ��
	glTranslated(0.0,0.0,m_z_delta);
	//��ת
	glRotated(sqrt((double)(x*x+y*y)),y,x,0.0);
	//���ƻ�ԭ��
	glTranslated(0.0,0.0, -m_z_delta);
	glMultMatrixd(modleview_matrix);
}


//�ر�����
void OpenGL::Shutdown()
{
//	t.print("trace in KnightOpenGL::Shutdown\n");

	wglMakeCurrent(NULL, NULL);
	if (m_render_contex != NULL) {
		wglDeleteContext(m_render_contex);
		m_render_contex = NULL;
	}
}


//���������ɫ
void OpenGL::SetClearCol(float r, float g, float b)
{
	glClearColor(r,g,b,1);
	glClear(GL_COLOR_BUFFER_BIT);
}


//��ʼ��Ⱦ�����û���
void OpenGL::StartRender(bool bColor, bool bDepth,
							   bool bStencil)
{
	if(bColor==true)
		glClear(GL_COLOR_BUFFER_BIT);
	if(bDepth==true)
		glClear(GL_DEPTH_BUFFER_BIT);
	if(bStencil)
		glClear(GL_STENCIL_BITS);
}


//������Ⱦ
void OpenGL::EndRendering()
{
	glFinish();
}


//�����ӿ�
void OpenGL::SetViewport(int x,int y,unsigned int w,unsigned int h)
{
	glViewport(x,y,w,h);
}


//���ö��������Ϣ
bool OpenGL::createVertexFace(Obj* obj)
{
	std::vector<Triple<double> > vertex_ptr = obj->getVertex();
	std::vector<Triple<double> > normal_ptr = obj->getNormal();
	std::vector<ObjFace> face_ptr = obj->getFace();
	
	for(int i=0;i<(int)face_ptr.size();++i){
		glBegin(GL_POLYGON);
		glNormal3d(normal_ptr[i].x,normal_ptr[i].y,normal_ptr[i].z);
		for(int j=0;j<(int)face_ptr[i].vertexIndex.size();++j){
			glVertex3d(vertex_ptr[face_ptr[i].vertexIndex[j]].x,
				vertex_ptr[face_ptr[i].vertexIndex[j]].y,
				vertex_ptr[face_ptr[i].vertexIndex[j]].z);
		}
		glEnd();
	}

	return true;
}


//����ǰ��׼��
bool OpenGL::renderInitial()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,viewport[2]/(double)viewport[3],1e-2,1e6);
	//ɢ�����ɫ
	const float color[] = {255.0f/255.0f, 255.0f/255.0f, 0.0f/255.0f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	//Ӳ��������Ȳ���
	glEnable(GL_DEPTH_TEST);
 
	return true;
}


//����ģ������������Ϣ
void OpenGL::RegisterObjectInfo(double scale,  Triple<double> &center)
{
	m_scale = scale;
	m_center = center;
}


//��ģ�ͷ������ӿڿռ���
void OpenGL::FocusObject() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(-m_center.x, -m_center.y,-m_center.z - m_scale * 1.5);
	m_z_delta = -m_scale *1.5;
}


//�Ƿ���������
void OpenGL::AntiAliasing(bool anti){
	if(anti){
		glEnable(GL_POLYGON_SMOOTH);
	}
	else{
		glDisable(GL_POLYGON_SMOOTH);
	}
}


//�Ŵ��Сģ��
void OpenGL::ZoomObject(double z_delta)
{	
	//���ɹ���
	if(m_z_delta+z_delta*m_scale > -m_scale*1)
		return ;
	//���ɹ�С
	if(m_z_delta+z_delta*m_scale < -m_scale * 10)
		return ;
	
	//�õ�ģ���ӵ����
	double modelviewMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX,modelviewMatrix);

	//�޸�ģ���ӵ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//�Ŵ��Сģ��=
	glTranslated(0.0,0.0,z_delta*m_scale);
	//���ֵ�仯
	m_z_delta += z_delta*m_scale;
	//������ǰ��ģ���ӵ����
	glMultMatrixd(modelviewMatrix);
}
void OpenGL::ClearBuffers(bool bColor, bool bDepth,
								bool bStencil)
{

}
void OpenGL::CalculateProjMatrix(float fov, float n, float f)
{

}
void OpenGL::CalculateOrthoMatrix(float n, float f)
{
}
int OpenGL::Render(int staticId)
{
	return 3;
}
int OpenGL::CreateStaticBuffer(VertexType, PrimType, int totalVerts, int totalIndices,
									 int stride, void **data, unsigned int *indices, int *staticId)
{
	return 3;
}
void OpenGL::OneTimeInit()
{
}