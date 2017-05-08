#include "stdafx.h"
#include "Bucket.h"


//把边加入分类边表
//最左端点x  相邻扫描线的x变化量  Y的变化量  第num个多边形  第Y桶 深度值zz
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


//把多边形 加入 多边形桶
// 平面参数  num扫描线 delta_y穿过的扫描线数量  color颜色 y桶
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


//如果num桶有多边形的话，则返回poly多边形链表，并返回其个数, 否则返回-1
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

//返回第num条扫描线与第poly_num个多边形的交点,返回边表edge , 及其数量
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


//得到指定的边 在num----num+delta_yr范围中寻找
//num:扫描线  delta_yr:变化的Y值 poly_num:指定的多边形 edge_tmp:返回的边
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