#include "stdafx.h"
#include "ActiveList.h"

ActiveList::~ActiveList(){
	m_edgeActive.clear(); 
	m_polygonActive.clear();
}


ActiveList::ActiveList(){
	m_edgeActive.clear(); 
	m_polygonActive.clear();
}


//把多边形插入活化多边表中
void ActiveList::AddActivePoly(TandyPolygon &poly)
{	
	m_polygonActive.insert(m_polygonActive.end(),poly);
}


//把边插入活化边表中
void ActiveList::AddActiveEdge(int poly_num,EdgeActive &edge_active)
{	
	m_edgeActive.insert(m_edgeActive.end(),edge_active);
}


//得到活化边表
std::list<EdgeActive> * ActiveList::getEdgeActive(){
	return &m_edgeActive;
}


//删除掉活化边
void ActiveList::eraseEdgeActive(std::list<EdgeActive>::iterator it)
{
	m_edgeActive.erase(it);
}


//得到指定活化多边形的delta_y
int ActiveList::getPolyDeltaY(int num){
	IteratorPoly it;
	for(it=m_polygonActive.begin();it!=m_polygonActive.end();++it){
		if((*it).num==num){
			return (*it).delta_y;
		}
	}
	return 0;
}


//删除掉指定活化多边形
void ActiveList::erasePolyActive(int num)
{	
	IteratorPoly it;
	for(it=m_polygonActive.begin();it!=m_polygonActive.end();++it){
		if((*it).num==num){
			m_polygonActive.erase((it));
			return ;
		}
	}
}


//对活化多边形 的每个delta_y减一
void ActiveList::PolySubDeltaY()
{
	IteratorPoly it;
	for(it=m_polygonActive.begin();it!=m_polygonActive.end();++it)
		--(*it).delta_y;
}


//把Y变化量小于1的每个多边形删掉
void ActiveList::PolyUpdate(){
	IteratorPoly it;
	for(it=m_polygonActive.begin();it!=m_polygonActive.end();){
		if((*it).delta_y<0){
			m_polygonActive.erase(it++);	// 删除该多边形,注意写法-
		}
		else{
			++it;
		}
	}
}