#include "stdafx.h"
#include "Obj.h"
#include "Math.h"


//第一遍扫描OBJ文件 统计顶点数目 面数目
bool Obj::ReloadObjFile(const char* file_path, int& vertex_number,int& surface_number) {
	FILE *pFile;

	if(fopen_s(&pFile,file_path,"r"))
		return false;
	vertex_number = surface_number = 0;
	//假设一行最多有65535个字符
	static const int MAXLEN = 65535;
	static char line[MAXLEN];
	//设置标志位 倒数第一位为0,如果被修改,则说明行缓冲不够,出错---
	line[MAXLEN-2] = 0;
	while(fgets(line,MAXLEN,pFile)){
		//如果一行超过65535 则说明出错
		if(line[MAXLEN-2]){
			fclose(pFile);
			return false;
		}
		switch(*line){
		case 'f':	// 面信息
			//一行一个面片---三角形面片也是多边形面片
			surface_number++ ;
			break;
		case 'v':	// 顶点信息 v vt纹理  vn法线
			// 每一行代表一个顶点
			if(*(line+1)==' ')
				++vertex_number;
			break;
		default :
			break;
		}
	}
	fclose(pFile);
	return vertex_number && surface_number;
}


//去掉控制字符,包括空格(0x20
inline const char* ridOfCtrl(const char* s) {
	while (*s && (*s<0x21 || *s>0x7e)) ++s;
	return s;
}


//读取面的一个顶点信息
inline const char* getVerInfo(const char* is, char* os) {
	const char *old=is=ridOfCtrl(is);
	//把非控制符读进来,不包括空格
	while (*is>0x20 && *is<0x7f) 
		*(os++)=*(is++); 
	*os=0;
	return old==is ? 0 : is;
}


//读取出第一个顶点的顶点索引信息
inline unsigned int getVerIndex(const char* s) {
	//去掉可能出现的+号
	if (*(s=ridOfCtrl(s))=='+') 
		++s;
	unsigned int ret=0;
	while (*s>='0' && *s<='9') 
		ret=ret*10+*(s++)-'0';
	return ret;
}


//读多边形面片
bool Obj::ReadPolygonal(const char* file_path, int& vertex_number,int& surface_number) {

	//设置指针
	Triple<double>* vertex_ptr = &m_vertex[0];	 
	ObjFace* surface_ptr = &m_surface[0];	//面片指针

	FILE *pFile;
	if(fopen_s(&pFile,file_path,"r"))
		return false;
	static const int MAXLEN = 65536;
	static char line[MAXLEN];
	vertex_number = surface_number = 0;
	line[MAXLEN-2] = 0;
	while(fgets(line,MAXLEN,pFile)){
		if(line[MAXLEN-2]){
			fclose(pFile);
			return false;
		}
		static char tmp[MAXLEN];
		const char *p;
		switch(*line){
		case 'v':	
			//顶点
			if(*(line+1) == ' '){	
				//读入顶点的坐标
				sscanf_s(line+1,"%lf %lf %lf", &vertex_ptr->x, &vertex_ptr->y, &vertex_ptr->z);
				++vertex_ptr;
				++vertex_number;
			}		
			break;
		case 'f':
			//表面
			p=line+1;
			//把所有顶点索引压入栈
			while(p=getVerInfo(p,tmp)){
				surface_ptr->vertexIndex.push_back(getVerIndex(tmp)-1);
			}
			++surface_ptr;
			++surface_number;
			break;
		default:
			break;
		}
	}
	fclose(pFile);
	return true;
}


//设置模型属性信息
//中心点 模型大小 面的法线信息
void Obj::SetProperties() {
	m_center.x = m_center.y = m_center.z = 0.0 ;
	Triple<double> min_xyz = m_vertex[0],max_xyz=m_vertex[0];
	for(int i=0; i< (int)m_vertex.size(); ++i){
		m_center += m_vertex[i];
		min_xyz.x = min(min_xyz.x,m_vertex[i].x);
		min_xyz.y = min(min_xyz.y,m_vertex[i].y);
		min_xyz.z = min(min_xyz.z,m_vertex[i].z);
		max_xyz.x = max(max_xyz.x,m_vertex[i].x);
		max_xyz.y = max(max_xyz.y,m_vertex[i].y);
		max_xyz.z = max(max_xyz.z,m_vertex[i].z);
	}
	//中心位置
	m_center/=(float)m_vertex.size();
	//法线量
	m_normal.resize(m_surface.size());
	//模型的大小
	m_scale = (max_xyz-min_xyz).VectorLen();

	//求面的法线信息
	for(int i=0;i<(int)m_surface.size();++i){
		m_normal[i] = (m_vertex[m_surface[i].vertexIndex[1]] - m_vertex[m_surface[i].vertexIndex[0]])*
			(m_vertex[m_surface[i].vertexIndex[2]]-m_vertex[m_surface[i].vertexIndex[0]]);
		m_normal[i] /= m_normal[i].VectorLen();//单位化
	}

}

//构造四面体
bool Obj::CreatTetrahedron() {

	m_vertex[0] = Triple<double>( 1.0, 1.0, 1.0);
	m_vertex[1] = Triple<double>(-1.0, 1.0,-1.0);
	m_vertex[2] = Triple<double>(-1.0,-1.0, 1.0);
	m_vertex[3] = Triple<double>( 1.0,-1.0,-1.0);

	int tmp[4][3] = 
	{0,1,2,
	0,2,3,
	0,3,1,
	3,2,1};
	for(int i = 0; i<4; i++)
		for (int j = 0; j < 3; j++)
		{
			m_surface[i].vertexIndex.push_back(tmp[i][j]);
		}
		return true;
}

//构造正方体
bool Obj::CreatBox() {

	m_vertex[0] = Triple<double>(-1.0,-1.0,-1.0);
	m_vertex[1] = Triple<double>( 1.0,-1.0,-1.0);
	m_vertex[2] = Triple<double>(-1.0, 1.0,-1.0);
	m_vertex[3] = Triple<double>( 1.0, 1.0,-1.0);
	m_vertex[4] = Triple<double>(-1.0,-1.0, 1.0);
	m_vertex[5] = Triple<double>( 1.0,-1.0, 1.0);
	m_vertex[6] = Triple<double>(-1.0, 1.0, 1.0);
	m_vertex[7] = Triple<double>( 1.0, 1.0, 1.0);


	int tmp[12][3] = 
	{0,1,2,
	3,2,1,
	0,2,4,
	6,4,2,
	0,4,1,
	5,1,4,
	7,5,6,
	4,6,5,
	7,6,3,
	2,3,6,
	7,3,5,
	1,5,3};
	for(int i = 0; i<12; i++)
		for (int j = 0; j < 3; j++)
		{
			m_surface[i].vertexIndex.push_back(tmp[i][j]);
		}
		return true;
}

//构造圆锥体
bool Obj::CreatCone(double r1,double r2, double h, int SubDiv) {

	m_vertex[0]=Triple<double>( 0,-h/2.0,0 );
	m_vertex[1]=Triple<double>( 0, h/2.0,0 ); 

	int i,b1,b2;
	b1 = b2 = 2;
	int cnt=2;
	if(r1!=0)
	{
		for(i=0;i<SubDiv;++i)
		{
			double a = ToRad(i*360.0/SubDiv);
			m_vertex[cnt]=Triple<double>(r1*cos(a), -h/2.0, r1*sin(a));
			++cnt;
		}
		b2 += SubDiv;
	}

	if(r2!=0)
	{
		for(i=0;i<SubDiv;++i)
		{
			double a = ToRad(i*360.0/SubDiv);
			m_vertex[cnt]=Triple<double>( r2*cos(a), h/2.0, r2*sin(a)); 
			++cnt;
		}
	}

	int n=0;
	if(r1!=0){ 
		for(i=0;i<SubDiv;++i){
			m_surface[n].vertexIndex.push_back(0);
			m_surface[n].vertexIndex.push_back(b1+i);
			m_surface[n].vertexIndex.push_back(b1+(i+1)%SubDiv);
			n++;
		}
	}

	if(r2!=0){
		for(i=0;i<SubDiv;++i) {
			m_surface[n].vertexIndex.push_back(1);
			m_surface[n].vertexIndex.push_back(b2+i);
			m_surface[n].vertexIndex.push_back(b2+(i+1)%SubDiv);
			n++;
		}} 


	if(r1==0) {
		for(i=0;i<SubDiv;++i)
		{
			m_surface[n].vertexIndex.push_back(0);
			m_surface[n].vertexIndex.push_back(b2+i);
			m_surface[n].vertexIndex.push_back(b2+(i+1)%SubDiv);
			n++;
		}
	}

	if(r2==0){
		for(i=0;i<SubDiv;++i){
			m_surface[n].vertexIndex.push_back(1);
			m_surface[n].vertexIndex.push_back(b1+i);
			m_surface[n].vertexIndex.push_back(b1+(i+1)%SubDiv);
			n++;
		}
	}


	if(r1!=0 && r2!=0){
		for(i=0;i<SubDiv;++i)
		{
			m_surface[n].vertexIndex.push_back(b1+i);
			m_surface[n].vertexIndex.push_back(b2+i);
			m_surface[n].vertexIndex.push_back(b2+(i+1)%SubDiv);
			n++;
			m_surface[n].vertexIndex.push_back(b1+i);
			m_surface[n].vertexIndex.push_back(b2+(i+1)%SubDiv);
			m_surface[n].vertexIndex.push_back(b1+(i+1)%SubDiv);
			n++;
		}	
	}

	return true;
}

bool Obj::CreatAttachment(int SubDiv) {
	int i,j,b1,b2;
	double thickness = 0.5;
	double longEdge = 2.0;
	double shortEdge = 1.0;
	double r = 1.0;

	m_vertex[0]=Triple<double>( 0.0, 0.0, r-thickness );
	m_vertex[1]=Triple<double>( 0.0, 0.0, r ); 

	int cnt = 2;
	b1=cnt;
	//bottom
	for(i=0;i<SubDiv;++i)
	{
		double a = ToRad(i*360.0/SubDiv);
		double b = ToRad(45.0);
		m_vertex[cnt]=Triple<double>(shortEdge*cos(a)*cos(b), longEdge*sin(a)*cos(b),r-thickness);
		++cnt;
	}

	b2=cnt;
	//top
	for (i=0;i<SubDiv;++i)
	{
		double a =ToRad(i*45.0/SubDiv+45.0);
		double h = r*sin(a);
		double r2 = r*cos(a);
		for (j=0;j<SubDiv;++j)
		{
			double b = ToRad(j*360.0/SubDiv);
			m_vertex[cnt]=Triple<double>(shortEdge*r2*cos(b),longEdge*r2*sin(b),h);
			++cnt;
		}
	}

	int n=0;
	for(i=0;i<SubDiv;++i)	
	{
		m_surface[n].vertexIndex.push_back(0);
		m_surface[n].vertexIndex.push_back(b1+(i+1)%SubDiv);
		m_surface[n].vertexIndex.push_back(b1+i);
		n++;
	}

	//around
	for (i=0;i<SubDiv;++i)
	{
		m_surface[n].vertexIndex.push_back(b1+i);
		m_surface[n].vertexIndex.push_back(b1+(i+1)%SubDiv);
		m_surface[n].vertexIndex.push_back(b2+(i+1)%SubDiv);
		n++;
		m_surface[n].vertexIndex.push_back(b1+i);
		m_surface[n].vertexIndex.push_back(b2+(i+1)%SubDiv);
		m_surface[n].vertexIndex.push_back(b2+i);
		n++;
	}

	//top
	for (i=0;i<SubDiv;++i)
	{
		int l=b2+SubDiv*SubDiv-SubDiv;
		m_surface[n].vertexIndex.push_back(1);
		m_surface[n].vertexIndex.push_back(l+i);
		m_surface[n].vertexIndex.push_back(l+(i+1)%SubDiv);
		n++;
	}

	for(i=0;i<SubDiv-1;++i)
	{
		for (j=0;j<SubDiv;++j)
		{
			int l =b2+i*SubDiv;
			m_surface[n].vertexIndex.push_back(l+j);
			m_surface[n].vertexIndex.push_back(l+(j+1)%SubDiv);
			m_surface[n].vertexIndex.push_back(l+(j+1)%SubDiv+SubDiv);
			n++;
			m_surface[n].vertexIndex.push_back(l+j);
			m_surface[n].vertexIndex.push_back(l+(j+1)%SubDiv+SubDiv);
			m_surface[n].vertexIndex.push_back(l+j+SubDiv);
			n++;
		}
	}

	return true;
}

