#ifndef MESH_H_
#define MESH_H_


#include "Obj.h"
#include "EngineMain.h"
#include "ScanLineZbuffer.h"


class Mesh {
public:
	//硬件或软件模拟
	enum {DRAW_HARDWARE, DRAW_SOFTWARE};

	//构造函数,复制构造,赋值操作
	Mesh() {
		DrawMode(DRAW_HARDWARE);
		m_scanline = new ScanLineZbuffer;
		m_draw_soft = false;
	}
	
	~Mesh();
	
	Mesh& operator=(const Mesh& rhs);

	//导入mesh
	bool LoadMesh(const char* file_path);

	//设置绘制方式
	void DrawMode(int mode) {m_draw_mode = mode;}

	//返回绘制方式
	int DrawMode() const {return m_draw_mode;}

	//绘制函数
	void Draw(EngineMain *,int render_mode);

	//得到顶点数
	int getVertexNum();

	//得到面数
	int getFaceNum();

	Triple<double>&  getCenter(){return m_obj.Center();}	//物体的中心坐标

	double getScale(){return m_obj.Scale();}//模型的尺寸

	bool IsValid(){return m_obj.IsValid();}	//Mesh是否有效

	bool Tetrahedron();//绘制四面体

	bool Cone(double r1,double r2,double h,int SubDiv);//绘制圆锥体

	bool Box();//绘正方体

	bool Attachment();

private:
	//硬件软件绘制函数
	void DrawHardwareImpl(EngineMain *,int render_mode);

	void DrawSoftwareImpl();

	int m_draw_mode;	//绘制方式:硬或软
	bool m_draw_soft;	//软件绘制是否成功
	Obj m_obj;		//OBJ模型
	ScanLineZbuffer *m_scanline;//软件扫描线Zbuffer算法类
};

#endif