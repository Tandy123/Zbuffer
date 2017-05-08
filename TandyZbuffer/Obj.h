#ifndef OBJ_H
#define OBJ_H

#include <iostream>
#include <vector>
#include "Triple.h"


//多边形面的格式
struct ObjFace{
	std::vector<unsigned int> vertexIndex;
};

class Obj {
public:

	//构造函数
	Obj(){ m_center.x=m_center.y=m_center.z =0.0; m_scale = 1;}

	//判断OBJ是否有效     
	bool IsValid() const {return !m_vertex.empty() && !m_surface.empty();}

	//得到模型的中心点
    Triple<double>& Center() {return m_center;}

	//得到模型的缩放值
	double Scale() const {return m_scale;}

	//得到模型的顶点数
	int VertexNumber() const {return (int)m_vertex.size();}

	//得到模型的面
	int SurfaceNumber() const {return (int)m_surface.size();}

	//清空顶点、面缓存数据
	void ClearVerSur() {m_vertex.clear();m_surface.clear();m_normal.clear();}

	//重新设置顶点、面矢量大小
	void ResetVerSur(const int vernum,const int surnum){
		m_vertex.resize(vernum);
		m_surface.resize(surnum);
	}

	//读模型函数
	bool ReloadObjFile(const char* file_path, int& vertex_number,int& surface_number);
	bool ReadPolygonal(const char* file_path, int& vertex_number,int& surface_number);

	//更新模型的属性值
	void SetProperties();

	//得到顶点
	std::vector<Triple<double> > & getVertex(){return m_vertex;}	

	//得到法线
	std::vector<Triple<double> > & getNormal(){return m_normal;}

	//得到面
	std::vector<ObjFace> & getFace(){return m_surface;}

	bool CreatTetrahedron();

	bool CreatBox();

	bool CreatCone(double r1,double r2, double h, int SubDiv);

	bool CreatAttachment(int SubDiv);

private:
	std::vector<Triple<double> > m_vertex;	//顶点
	std::vector<Triple<double> > m_normal;	//法线
	std::vector<ObjFace> m_surface;	//面
	Triple<double> m_center;	//物体的中心坐标
	double m_scale;		//模型的尺寸
};

#endif
