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


//�Ѷ���β�����߱���
void ActiveList::AddActivePoly(TandyPolygon &poly)
{	
	m_polygonActive.insert(m_polygonActive.end(),poly);
}


//�ѱ߲����߱���
void ActiveList::AddActiveEdge(int poly_num,EdgeActive &edge_active)
{	
	m_edgeActive.insert(m_edgeActive.end(),edge_active);
}


//�õ���߱�
std::list<EdgeActive> * ActiveList::getEdgeActive(){
	return &m_edgeActive;
}


//ɾ�������
void ActiveList::eraseEdgeActive(std::list<EdgeActive>::iterator it)
{
	m_edgeActive.erase(it);
}


//�õ�ָ�������ε�delta_y
int ActiveList::getPolyDeltaY(int num){
	IteratorPoly it;
	for(it=m_polygonActive.begin();it!=m_polygonActive.end();++it){
		if((*it).num==num){
			return (*it).delta_y;
		}
	}
	return 0;
}


//ɾ����ָ��������
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


//�Ի����� ��ÿ��delta_y��һ
void ActiveList::PolySubDeltaY()
{
	IteratorPoly it;
	for(it=m_polygonActive.begin();it!=m_polygonActive.end();++it)
		--(*it).delta_y;
}


//��Y�仯��С��1��ÿ�������ɾ��
void ActiveList::PolyUpdate(){
	IteratorPoly it;
	for(it=m_polygonActive.begin();it!=m_polygonActive.end();){
		if((*it).delta_y<0){
			m_polygonActive.erase(it++);	// ɾ���ö����,ע��д��-
		}
		else{
			++it;
		}
	}
}