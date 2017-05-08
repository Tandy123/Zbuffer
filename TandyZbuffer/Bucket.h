#ifndef BUCKET_H_
#define BUCKET_H_


#include "Algorithm.h"


//桶类
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

	//重新设置桶大小，要先清空
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
	
	//把边加入边表
	//最左端点x  相邻扫描线的x变化量  Y的变化量  第num个多边形  第Y桶 深度值zz
	bool AddEdge(double x,double delta_x,int delta_y,unsigned int num,unsigned int y,double zz);
	
	//把多边形 加入多边形桶
	// 平面参数  num扫描线 delta_y穿过的扫描线数量  color颜色 y桶
	bool AddPolygon(Triple<double> para, unsigned int num ,int delta_y, Triple<unsigned char> color, unsigned int y);
	
	//如果num桶有多边形的话，则返回poly多边形链表，并返回其个数, 否则返回-1
	int HaveBucketPoly(int num , std::vector<TandyPolygon> &poly);

	//返回第num条扫描线与第poly_num个多边形的交点,返回边表edge , 及其数量
	//在边桶中寻找属于poly_num多边形的边，并返回
	int HaveEdge(int num,int poly_num,std::vector<Edge> & edge);

	//得到指定的边 在num----num+delta_yr范围中寻找
	//num:扫描线  delta_yr:变化的Y值 poly_num:指定的多边形 edge_tmp:返回的边
	bool getProperEdge(int num,int delta_yr,int poly_num,Edge & edge_tmp);

private:
	std::vector<std::vector<TandyPolygon> > m_polygon;	// 多边形Y筒
	std::vector<std::vector<Edge> >	m_edge;	//边Y筒

};

#endif