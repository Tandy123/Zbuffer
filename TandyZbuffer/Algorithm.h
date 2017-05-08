#ifndef ALGORITHM_H_
#define ALGORITHM_H_


#include "Math.h"		
#include "Obj.h"
#include "Triple.h"	
#include <list>


//多边形表、活化多边形表
struct TandyPolygon{
	double a,b,c;	// 多边形方程
	int delta_y;	// 穿过的扫描线数
	unsigned int num;	// 多边形编号
};

//分类边表
struct Edge{
	double delta_x;	// x变化量
	int delta_y;	// y变化量
	unsigned int num;	//多边形编号
	double x;	// 边的上端点X坐标的值
	double z;	// 最高顶点的深度值
};

//活化边表
struct EdgeActive{
	double xl,delta_xl;
	double xr,delta_xr;
	double zl,delta_zx,delta_zy;
	unsigned int num;
	int delta_yl,delta_yr;
};

typedef std::list<EdgeActive>::iterator Iterator;

#endif