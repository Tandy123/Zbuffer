#ifndef MESH_H_
#define MESH_H_


#include "Obj.h"
#include "EngineMain.h"
#include "ScanLineZbuffer.h"


class Mesh {
public:
	//Ӳ�������ģ��
	enum {DRAW_HARDWARE, DRAW_SOFTWARE};

	//���캯��,���ƹ���,��ֵ����
	Mesh() {
		DrawMode(DRAW_HARDWARE);
		m_scanline = new ScanLineZbuffer;
		m_draw_soft = false;
	}
	
	~Mesh();
	
	Mesh& operator=(const Mesh& rhs);

	//����mesh
	bool LoadMesh(const char* file_path);

	//���û��Ʒ�ʽ
	void DrawMode(int mode) {m_draw_mode = mode;}

	//���ػ��Ʒ�ʽ
	int DrawMode() const {return m_draw_mode;}

	//���ƺ���
	void Draw(EngineMain *,int render_mode);

	//�õ�������
	int getVertexNum();

	//�õ�����
	int getFaceNum();

	Triple<double>&  getCenter(){return m_obj.Center();}	//�������������

	double getScale(){return m_obj.Scale();}//ģ�͵ĳߴ�

	bool IsValid(){return m_obj.IsValid();}	//Mesh�Ƿ���Ч

	bool Tetrahedron();//����������

	bool Cone(double r1,double r2,double h,int SubDiv);//����Բ׶��

	bool Box();//��������

	bool Attachment();

private:
	//Ӳ��������ƺ���
	void DrawHardwareImpl(EngineMain *,int render_mode);

	void DrawSoftwareImpl();

	int m_draw_mode;	//���Ʒ�ʽ:Ӳ����
	bool m_draw_soft;	//��������Ƿ�ɹ�
	Obj m_obj;		//OBJģ��
	ScanLineZbuffer *m_scanline;//���ɨ����Zbuffer�㷨��
};

#endif