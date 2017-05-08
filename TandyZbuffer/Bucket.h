#ifndef BUCKET_H_
#define BUCKET_H_


#include "Algorithm.h"


//Ͱ��
class Bucket{

public:

	Bucket(){
		m_edge.clear();
		m_polygon.clear();
	}

	~Bucket(){
		for(int i=0;i<(int)m_edge.size();++i){
			for(int j=0;j<(int)(m_edge[i].size());++j)
				m_edge[i].clear();
		}
		for(int i=0;i<(int)m_polygon.size();++i){
			for(int j=0;j<(int)m_polygon[i].size();++j)
				m_polygon[i].clear();
		}
		m_edge.clear();
		m_polygon.clear();
	}

	//��������Ͱ��С��Ҫ�����
	void Reset(int height){
		for(int i=0;i<(int)m_edge.size();++i){
			for(int j=0;j<(int)(m_edge[i].size());++j)
				m_edge[i].clear();
		}
		for(int i=0;i<(int)m_polygon.size();++i){
			for(int j=0;j<(int)m_polygon[i].size();++j)
				m_polygon[i].clear();
		}
		m_edge.clear();
		m_polygon.clear();

		m_polygon.resize(height); 
		m_edge.resize(height);
	}
	
	//�ѱ߼���߱�
	//����˵�x  ����ɨ���ߵ�x�仯��  Y�ı仯��  ��num�������  ��YͰ ���ֵzz
	bool AddEdge(double x,double delta_x,int delta_y,unsigned int num,unsigned int y,double zz);
	
	//�Ѷ���� ��������Ͱ
	// ƽ�����  numɨ���� delta_y������ɨ��������  color��ɫ yͰ
	bool AddPolygon(Triple<double> para, unsigned int num ,int delta_y, Triple<unsigned char> color, unsigned int y);
	
	//���numͰ�ж���εĻ����򷵻�poly��������������������, ���򷵻�-1
	int HaveBucketPoly(int num , std::vector<TandyPolygon> &poly);

	//���ص�num��ɨ�������poly_num������εĽ���,���ر߱�edge , ��������
	//�ڱ�Ͱ��Ѱ������poly_num����εıߣ�������
	int HaveEdge(int num,int poly_num,std::vector<Edge> & edge);

	//�õ�ָ���ı� ��num----num+delta_yr��Χ��Ѱ��
	//num:ɨ����  delta_yr:�仯��Yֵ poly_num:ָ���Ķ���� edge_tmp:���صı�
	bool getProperEdge(int num,int delta_yr,int poly_num,Edge & edge_tmp);

private:
	std::vector<std::vector<TandyPolygon> > m_polygon;	// �����YͲ
	std::vector<std::vector<Edge> >	m_edge;	//��YͲ

};

#endif