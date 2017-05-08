#ifndef  SCANLINEZBUFFER_H_
#define  SCANLINEZBUFFER_H_


#include "Algorithm.h"
#include "ActiveList.h"
#include "Bucket.h"
#include "Buffer.h"
#include <gl/GL.h>
#include <gl/GLU.h>


class ScanLineZbuffer{

public:

	//��ʹ��,���� ���(������/��߶�)Ͱ(�����Ͱ/��Ͱ)֡����
	ScanLineZbuffer();

	//��ĳ�ʹ��
	//��������������ָ������������ָ�뷨������ָ��
	void InitialZbuffer(int vetex_num,Triple<double> *vertex,
		int face_num, ObjFace *surface , Triple<double> *normal);

	//��������
	~ScanLineZbuffer();
	
	//ɨ����Zbuffer�㷨
	bool StartAlgorithm();
	
	//��ʹ����Ͱ �����Ͱ
	//�Ѷ������ݶ������� ������д��Ͱ����
	//YͰֵһ��ͳһȡ��
	void setBucket();
	
	//��ʹ��֡���� Zbuffer����
	void InitialBuffers();
	
	//ɨ�������㷨���
	bool MainAlgorithm();

	//������ε�YͰ��������µĶ�����漰��ɨ���ߣ�������������λ����
	//����������֮�� ҲҪ�Ѹö�����뵱ǰɨ�����ཻ�ı߶� ���뵽��߶Ա�
	void CheckPolygonBucket_PutItToActive(int num,int &err_code);

	//����ÿһ��ɨɨ����
	//numΪɨ���� error_codeΪ�������
	void DealWithActiveEdge(int num,int &err_code);

	//�Ѹö������ɨ���ߵĽ���߶Է���߻����
	//numΪɨ����  poly_numΪ����α��  paraΪ���� a b c
	//func Ϊ0 ��ʾ�ǵ������µĶ����ʱ ������
	//func Ϊ1 ��ʾ�ǵ�����ʧʱ�¼����˱߶Ե����Σ�������Ҫ��delta_ylr����һ
	//err_code Ϊ���صĴ������
	bool PutEdgeToAcitive(int num,int poly_num,Triple<double> &para,int func,int &err_code);

	//ͼ�λ��ƺ���
	void DrawLine();


private:
	
	void SetScene();

	//����ͶӰ����
	void ProjectScene();

	int m_viewport[4];		// �ӿھ���
	double m_modelview[16];	// ģ�ͱ任����
	double m_projection[16];	// ͶӰ����
	std::vector<Triple<double> > m_projectionVertex;	// ͶӰ����
	int m_vertex_num,m_surface_num;	// ������������
	Triple<double> *m_vertex;	// ����
	Triple<double> *m_normal_x;	// ����
	std::vector<Triple<double> > m_normal;
	ObjFace *m_surface;	// ��
	ActiveList *m_activeList;	// �����α� ��߱�
	Bucket *m_bucket;	// �����Ͱ �� ��Ͱ
	ZBuffer m_zBuffer;	// zbuffer
	FrameBuffer<Triple<unsigned char> > *m_frameBuffer;	// ֡����
	
	//�����ɫ����ֵ,֮���Բ��洢�ڶ����YͰ�е�ԭ�����Ϊ�˿��ٲ��ҵ������ɫ��Ϣ
	std::vector<Triple<unsigned char> > m_color;	//�����ɫ
};

#endif