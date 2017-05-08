#include "stdafx.h"
#include "Mesh.h"

Mesh::~Mesh()
{
	m_obj.ClearVerSur();
	delete m_scanline;
	m_scanline = NULL;
}

//����OBJģ�ͺ���
bool Mesh::LoadMesh(const char* file_path) {
	//��ն��㡢�滺������
	m_obj.ClearVerSur();

	int vertexNum,surfaceNum;
	//��һ��ɨ��ͳ��֪��OBJ�ļ��Ķ��㡢������
	if(!m_obj.ReloadObjFile(file_path,vertexNum,surfaceNum)){
		return false;
	}

	//�������ö��㡢���VECTOR��С
	m_obj.ResetVerSur(vertexNum,surfaceNum);
	//����Ƭ
	int vn,sn;
	bool ret=m_obj.ReadPolygonal(file_path,vn,sn);
	if(vn!=vertexNum || sn!=surfaceNum || !ret){
		return false;
	}

	//����OBJģ�͵���Ϣ
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

bool Mesh::Tetrahedron() {
	//��ն��㡢�滺������
	m_obj.ClearVerSur();

	int vertexNum = 4;
	int surfaceNum = 4;

	m_obj.ResetVerSur(vertexNum,surfaceNum);
	
	bool ret=m_obj.CreatTetrahedron();

	//����OBJģ�͵���Ϣ
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

bool Mesh::Cone(double r1,double r2,double h,int SubDiv) {
	//��ն��㡢�滺������
	m_obj.ClearVerSur();

	int vertexNum,surfaceNum;

	if(r1==0 || r2==0) {
        vertexNum=SubDiv+2;
        surfaceNum=SubDiv*2;
	}	else {
        vertexNum=SubDiv*2+2;
        surfaceNum=SubDiv*4;
	}

	m_obj.ResetVerSur(vertexNum,surfaceNum);
	
	bool ret=m_obj.CreatCone(r1,r2,h,SubDiv);

	//����OBJģ�͵���Ϣ
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

bool Mesh::Box() {
		//��ն��㡢�滺������
	m_obj.ClearVerSur();

	int vertexNum = 8;
	int surfaceNum = 12;

	m_obj.ResetVerSur(vertexNum,surfaceNum);
	
	bool ret=m_obj.CreatBox();

	//����OBJģ�͵���Ϣ
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

bool Mesh::Attachment() {
		//��ն��㡢�滺������
	m_obj.ClearVerSur();
	int SubDiv = 36;

	int VN,FN;
	VN = SubDiv*SubDiv+SubDiv+2;
	FN = 2*SubDiv*SubDiv-SubDiv+SubDiv*3;

	int vertexNum = VN;
	int surfaceNum = FN;

	m_obj.ResetVerSur(vertexNum,surfaceNum);
	
	bool ret=m_obj.CreatAttachment(SubDiv);

	//����OBJģ�͵���Ϣ
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

//Ӳ�����ƺ���
void Mesh::DrawHardwareImpl(EngineMain *rMain,int render_mode){

	rMain->RenderLoopObj(&m_obj,render_mode);
}


//���ģ����ƺ���
void Mesh::DrawSoftwareImpl(){
	int vertex_num = m_obj.VertexNumber();
	Triple<double>* vertex = &(m_obj.getVertex())[0];
	int face_num = m_obj.SurfaceNumber();
	ObjFace *surface = &(m_obj.getFace())[0];
	Triple<double> *normal = &(m_obj.getNormal())[0];
	
	if(m_draw_soft == false)
		return;

	m_scanline->InitialZbuffer(vertex_num,vertex,face_num
		,surface,normal);

	//��������㷨
	if(!m_scanline->StartAlgorithm())
		m_draw_soft = false;	// ����ʧ��,ֹͣ����
}


//���ƺ���
void Mesh::Draw(EngineMain *rMain,int render_mode) {
	if(!m_obj.IsValid())
		return;

	switch(render_mode){
		case 0:
			// soft
			m_draw_mode = DRAW_SOFTWARE;
			break;
		case 1:
			// opengl
			m_draw_mode = DRAW_HARDWARE;
			break;
		default:
			break;
	}

	switch (m_draw_mode) {
	case DRAW_HARDWARE: DrawHardwareImpl(rMain,render_mode);
		break;
	case DRAW_SOFTWARE: DrawSoftwareImpl();
		break;
	default:
		break;
	}
}


//�õ��������Ŀ
int Mesh::getVertexNum()
{
	if(m_obj.IsValid())
		return m_obj.VertexNumber();
	return 0;
}


//�õ������Ŀ
int Mesh::getFaceNum()
{
	if(m_obj.IsValid())
		return m_obj.SurfaceNumber();
	return 0;
}