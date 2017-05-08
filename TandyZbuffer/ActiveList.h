#ifndef  ACTIVE_LIST_H_
#define  ACTIVE_LIST_H_


#include "Algorithm.h"
#include <list>


typedef std::list<TandyPolygon>::iterator IteratorPoly;

class ActiveList{
public:
	~ActiveList();
	ActiveList();
	
	//活化边表、活化多边形表 清空
	void Reset(){
		m_edgeActive.clear();
		m_polygonActive.clear();
	}
	
	//把多边形插入活化多边表中
	void AddActivePoly(TandyPolygon &poly);
	
	//把边插入活化边表中
	void AddActiveEdge(int poly_num,EdgeActive &edge_active);

	//得到活化边表
	std::list<EdgeActive>  *getEdgeActive();

	//删除掉活化边
	void eraseEdgeActive(std::list<EdgeActive>::iterator it);

	//得到指定活化多边形的delta_y
	int getPolyDeltaY(int num);

	//删除掉指定活化多边形
	void erasePolyActive(int num);

	//对活化多边形的每个delta_y减一
	void PolySubDeltaY();

	//把Y变化量小于1的每个多边形删掉
	void PolyUpdate();

private:
	std::list<EdgeActive> m_edgeActive;		// 活化边表
	std::list<TandyPolygon> m_polygonActive;	// 活化多边形表
};

#endif