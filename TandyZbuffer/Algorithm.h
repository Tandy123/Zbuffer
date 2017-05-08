#ifndef ALGORITHM_H_
#define ALGORITHM_H_


#include "Math.h"		
#include "Obj.h"
#include "Triple.h"	
#include <list>


//����α������α�
struct TandyPolygon{
	double a,b,c;	// ����η���
	int delta_y;	// ������ɨ������
	unsigned int num;	// ����α��
};

//����߱�
struct Edge{
	double delta_x;	// x�仯��
	int delta_y;	// y�仯��
	unsigned int num;	//����α��
	double x;	// �ߵ��϶˵�X�����ֵ
	double z;	// ��߶�������ֵ
};

//��߱�
struct EdgeActive{
	double xl,delta_xl;
	double xr,delta_xr;
	double zl,delta_zx,delta_zy;
	unsigned int num;
	int delta_yl,delta_yr;
};

typedef std::list<EdgeActive>::iterator Iterator;

#endif