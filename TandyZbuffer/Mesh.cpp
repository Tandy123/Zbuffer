#include "stdafx.h"
#include "Mesh.h"

Mesh::~Mesh()
{
	m_obj.ClearVerSur();
	delete m_scanline;
	m_scanline = NULL;
}

//导入OBJ模型函数
bool Mesh::LoadMesh(const char* file_path) {
	//清空顶点、面缓存数据
	m_obj.ClearVerSur();

	int vertexNum,surfaceNum;
	//第一遍扫描统计知道OBJ文件的顶点、面数量
	if(!m_obj.ReloadObjFile(file_path,vertexNum,surfaceNum)){
		return false;
	}

	//重新设置顶点、面的VECTOR大小
	m_obj.ResetVerSur(vertexNum,surfaceNum);
	//读面片
	int vn,sn;
	bool ret=m_obj.ReadPolygonal(file_path,vn,sn);
	if(vn!=vertexNum || sn!=surfaceNum || !ret){
		return false;
	}

	//设置OBJ模型的信息
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

bool Mesh::Tetrahedron() {
	//清空顶点、面缓存数据
	m_obj.ClearVerSur();

	int vertexNum = 4;
	int surfaceNum = 4;

	m_obj.ResetVerSur(vertexNum,surfaceNum);
	
	bool ret=m_obj.CreatTetrahedron();

	//设置OBJ模型的信息
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

bool Mesh::Cone(double r1,double r2,double h,int SubDiv) {
	//清空顶点、面缓存数据
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

	//设置OBJ模型的信息
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

bool Mesh::Box() {
		//清空顶点、面缓存数据
	m_obj.ClearVerSur();

	int vertexNum = 8;
	int surfaceNum = 12;

	m_obj.ResetVerSur(vertexNum,surfaceNum);
	
	bool ret=m_obj.CreatBox();

	//设置OBJ模型的信息
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

bool Mesh::Attachment() {
		//清空顶点、面缓存数据
	m_obj.ClearVerSur();
	int SubDiv = 36;

	int VN,FN;
	VN = SubDiv*SubDiv+SubDiv+2;
	FN = 2*SubDiv*SubDiv-SubDiv+SubDiv*3;

	int vertexNum = VN;
	int surfaceNum = FN;

	m_obj.ResetVerSur(vertexNum,surfaceNum);
	
	bool ret=m_obj.CreatAttachment(SubDiv);

	//设置OBJ模型的信息
	m_obj.SetProperties();

	m_draw_soft = true;

	return true;
}

//硬件绘制函数
void Mesh::DrawHardwareImpl(EngineMain *rMain,int render_mode){

	rMain->RenderLoopObj(&m_obj,render_mode);
}


//软件模拟绘制函数
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

	//软件绘制算法
	if(!m_scanline->StartAlgorithm())
		m_draw_soft = false;	// 绘制失败,停止绘制
}


//绘制函数
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


//得到顶点的数目
int Mesh::getVertexNum()
{
	if(m_obj.IsValid())
		return m_obj.VertexNumber();
	return 0;
}


//得到面的数目
int Mesh::getFaceNum()
{
	if(m_obj.IsValid())
		return m_obj.SurfaceNumber();
	return 0;
}