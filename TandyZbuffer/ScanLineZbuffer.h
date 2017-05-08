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

	//初使化,构造 活化表(活化多边形/活化边对)桶(多边形桶/边桶)帧缓存
	ScanLineZbuffer();

	//类的初使化
	//顶点数顶点数据指针面数面数据指针法线数据指针
	void InitialZbuffer(int vetex_num,Triple<double> *vertex,
		int face_num, ObjFace *surface , Triple<double> *normal);

	//析构函数
	~ScanLineZbuffer();
	
	//扫描线Zbuffer算法
	bool StartAlgorithm();
	
	//初使化边桶 多边形桶
	//把顶点数据读进来后 把数据写进桶里面
	//Y桶值一律统一取整
	void setBucket();
	
	//初使化帧缓存 Zbuffer缓冲
	void InitialBuffers();
	
	//扫描线主算法框架
	bool MainAlgorithm();

	//检查多边形的Y桶，如果有新的多边形涉及该扫描线，则把它放入多边形活化表中
	//当加入多边形之后 也要把该多边形与当前扫描线相交的边对 加入到活化边对表
	void CheckPolygonBucket_PutItToActive(int num,int &err_code);

	//处理每一条扫扫描线
	//num为扫描线 error_code为错误代码
	void DealWithActiveEdge(int num,int &err_code);

	//把该多边形与扫描线的交点边对放入边活化表中
	//num为扫描线  poly_num为多边形编号  para为参数 a b c
	//func 为0 表示是当遇到新的多边形时 的情形
	//func 为1 表示是当边消失时新加入了边对的情形，该情形要把delta_ylr都减一
	//err_code 为返回的错误代码
	bool PutEdgeToAcitive(int num,int poly_num,Triple<double> &para,int func,int &err_code);

	//图形绘制函数
	void DrawLine();


private:
	
	void SetScene();

	//生成投影坐标
	void ProjectScene();

	int m_viewport[4];		// 视口矩阵
	double m_modelview[16];	// 模型变换矩阵
	double m_projection[16];	// 投影矩阵
	std::vector<Triple<double> > m_projectionVertex;	// 投影坐标
	int m_vertex_num,m_surface_num;	// 顶点数、面数
	Triple<double> *m_vertex;	// 顶点
	Triple<double> *m_normal_x;	// 法线
	std::vector<Triple<double> > m_normal;
	ObjFace *m_surface;	// 面
	ActiveList *m_activeList;	// 活化多边形表 活化边表
	Bucket *m_bucket;	// 多边形桶 和 边桶
	ZBuffer m_zBuffer;	// zbuffer
	FrameBuffer<Triple<unsigned char> > *m_frameBuffer;	// 帧缓存
	
	//面的颜色光亮值,之所以不存储在多边形Y桶中的原因就是为了快速查找到面的颜色信息
	std::vector<Triple<unsigned char> > m_color;	//面的颜色
};

#endif