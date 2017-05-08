#ifndef BUFFER_H_
#define BUFFER_H_

#include <vector>


//֡������
template <typename T>
class FrameBuffer{
public:

	FrameBuffer():m_width(0),m_height(0){}

	//���¸߶ȺͿ�ȣ��������������С
	void ResizeBuffer(int width,int height){
		if(m_width!=width || m_height!=height){
			m_width = width;
			m_height = height;
			m_effectWidth = (m_width * sizeof(T)+3)/4*4;	// ��Ч�Ŀ��
			m_buffer.clear();
			m_buffer.resize(m_effectWidth * m_height);	// ֡�����С
		}
	}

	//��ʹ��֡����
	void Memset(int valueR,int valueG,int valueB){
		for(int i = 0; i<m_buffer.size()/3; i++)
		{
			m_buffer[i*3] = valueR;
			m_buffer[i*3+1] = valueG;
			m_buffer[i*3+2] = valueB;
		}
	}

	//����Ҫд���֡����λ��
	T* Pixel(int row,int col){
		if(row>=0 && row<m_height && col>=0 && col < m_width)
			return ((T*)(&m_buffer[0]+m_effectWidth*row))+col;
		else{		
			return &m_dummy;	// ����δ֪����
		}
	}
private:
	std::vector<char> m_buffer;	// ֡����
	T m_dummy;	// tmp
	int m_width,m_height;	// ���/�߶�
	int m_effectWidth;	// ��Ч�Ŀ��
	FrameBuffer(const FrameBuffer&);	// ����
	FrameBuffer& operator=(const FrameBuffer &);	// ����
};


//Zbuffer����
class ZBuffer{
public:

	ZBuffer(){}

	//---дZbuffer
	double& operator[](int index){
		if((index >=0) &&  (index < (int)m_Zbuffer.size()))
			return m_Zbuffer[index];
		else
			return m_dummy;
	}

	//�������ô�С
	void ResizeBuffer(int n){
		m_Zbuffer.clear();
		m_Zbuffer.resize(n);
	}

private:
	std::vector<double> m_Zbuffer;
	double m_dummy;
	// �������º���
	ZBuffer(const ZBuffer&);
	ZBuffer& operator=(const ZBuffer&);
};

#endif