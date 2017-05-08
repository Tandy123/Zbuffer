#include "stdafx.h"
#include "Bucket.h"


//�ѱ߼������߱�
//����˵�x  ����ɨ���ߵ�x�仯��  Y�ı仯��  ��num�������  ��YͰ ���ֵzz
bool Bucket::AddEdge(double x,double delta_x,int delta_y,unsigned int num,unsigned int y,double zz)
{
	Edge edge;
	edge.delta_x = delta_x;
	edge.delta_y = delta_y;
	edge.num = num;
	edge.x = x;
	edge.z = zz;
	m_edge[y].push_back(edge);
	
	return true;
}


//�Ѷ���� ���� �����Ͱ
// ƽ�����  numɨ���� delta_y������ɨ��������  color��ɫ yͰ
bool Bucket::AddPolygon(Triple<double> para, unsigned int num , int delta_y, 
							  Triple<unsigned char> color, unsigned int y)
{
	TandyPolygon polygon;
	polygon.a = para.x;
	polygon.b = para.y;
	polygon.c = para.z;
	polygon.delta_y = delta_y;
	polygon.num = num;
	m_polygon[y].push_back(polygon);

	return true;
}


//���numͰ�ж���εĻ����򷵻�poly��������������������, ���򷵻�-1
int Bucket::HaveBucketPoly(int num , std::vector<TandyPolygon> &poly)
{
	if(m_polygon[num].size()==0){
		return -1;
	}
	else{
		poly = m_polygon[num];
		return (int)m_polygon[num].size();
	}

}

//���ص�num��ɨ�������poly_num������εĽ���,���ر߱�edge , ��������
int Bucket::HaveEdge(int num,int poly_num,std::vector<Edge> & edge)
{
	int countt=0;
	if(m_edge[num].size()==0){
		return -1;
	}
	else{
		for(int i=0;i<(int)m_edge[num].size();++i){
			if(m_edge[num][i].num == poly_num){
				edge.push_back(m_edge[num][i]);
				++countt;
			}	
		}
		return countt;
	}
}


//�õ�ָ���ı� ��num----num+delta_yr��Χ��Ѱ��
//num:ɨ����  delta_yr:�仯��Yֵ poly_num:ָ���Ķ���� edge_tmp:���صı�
bool Bucket::getProperEdge(int num,int delta_yr,int poly_num,Edge & edge_tmp)
{
	for(int i=num;i<=(int)(num+delta_yr);++i){
		for(int j=0;j<(int)m_edge[i].size();++j){
			if(m_edge[i][j].num == poly_num){
				edge_tmp = m_edge[i][j];
				return true;
			}
		}
	}
	return false;
}