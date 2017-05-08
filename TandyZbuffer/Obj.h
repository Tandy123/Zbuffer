#ifndef OBJ_H
#define OBJ_H

#include <iostream>
#include <vector>
#include "Triple.h"


//�������ĸ�ʽ
struct ObjFace{
	std::vector<unsigned int> vertexIndex;
};

class Obj {
public:

	//���캯��
	Obj(){ m_center.x=m_center.y=m_center.z =0.0; m_scale = 1;}

	//�ж�OBJ�Ƿ���Ч     
	bool IsValid() const {return !m_vertex.empty() && !m_surface.empty();}

	//�õ�ģ�͵����ĵ�
    Triple<double>& Center() {return m_center;}

	//�õ�ģ�͵�����ֵ
	double Scale() const {return m_scale;}

	//�õ�ģ�͵Ķ�����
	int VertexNumber() const {return (int)m_vertex.size();}

	//�õ�ģ�͵���
	int SurfaceNumber() const {return (int)m_surface.size();}

	//��ն��㡢�滺������
	void ClearVerSur() {m_vertex.clear();m_surface.clear();m_normal.clear();}

	//�������ö��㡢��ʸ����С
	void ResetVerSur(const int vernum,const int surnum){
		m_vertex.resize(vernum);
		m_surface.resize(surnum);
	}

	//��ģ�ͺ���
	bool ReloadObjFile(const char* file_path, int& vertex_number,int& surface_number);
	bool ReadPolygonal(const char* file_path, int& vertex_number,int& surface_number);

	//����ģ�͵�����ֵ
	void SetProperties();

	//�õ�����
	std::vector<Triple<double> > & getVertex(){return m_vertex;}	

	//�õ�����
	std::vector<Triple<double> > & getNormal(){return m_normal;}

	//�õ���
	std::vector<ObjFace> & getFace(){return m_surface;}

	bool CreatTetrahedron();

	bool CreatBox();

	bool CreatCone(double r1,double r2, double h, int SubDiv);

	bool CreatAttachment(int SubDiv);

private:
	std::vector<Triple<double> > m_vertex;	//����
	std::vector<Triple<double> > m_normal;	//����
	std::vector<ObjFace> m_surface;	//��
	Triple<double> m_center;	//�������������
	double m_scale;		//ģ�͵ĳߴ�
};

#endif
