#ifndef  ACTIVE_LIST_H_
#define  ACTIVE_LIST_H_


#include "Algorithm.h"
#include <list>


typedef std::list<TandyPolygon>::iterator IteratorPoly;

class ActiveList{
public:
	~ActiveList();
	ActiveList();
	
	//��߱������α� ���
	void Reset(){
		m_edgeActive.clear();
		m_polygonActive.clear();
	}
	
	//�Ѷ���β�����߱���
	void AddActivePoly(TandyPolygon &poly);
	
	//�ѱ߲����߱���
	void AddActiveEdge(int poly_num,EdgeActive &edge_active);

	//�õ���߱�
	std::list<EdgeActive>  *getEdgeActive();

	//ɾ�������
	void eraseEdgeActive(std::list<EdgeActive>::iterator it);

	//�õ�ָ�������ε�delta_y
	int getPolyDeltaY(int num);

	//ɾ����ָ��������
	void erasePolyActive(int num);

	//�Ի����ε�ÿ��delta_y��һ
	void PolySubDeltaY();

	//��Y�仯��С��1��ÿ�������ɾ��
	void PolyUpdate();

private:
	std::list<EdgeActive> m_edgeActive;		// ��߱�
	std::list<TandyPolygon> m_polygonActive;	// �����α�
};

#endif