#ifndef TRIPLE_H_
#define TRIPLE_H_

#include "Math.h"

//三点坐标运算
template <typename T>  
struct Triple {
	T x, y, z;

	Triple() {}
	Triple(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
	
	//矢量加法
	Triple<T>& operator+=(const Triple<T>& rhs) {	
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	//矢量减法
	Triple<T> operator-(const Triple<T>& rhs) {
		return Triple<T>(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	
	//坐标外积公式
	Triple<T> operator*(const Triple<T>& rhs) {
		return Triple<T>(y * rhs.z - z * rhs.y,
						 z * rhs.x - x * rhs.z,
                         x * rhs.y - y * rhs.x);
	}

	//矢量除以指定常数
	Triple<T>& operator/=(const T& rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	//矢量的长度
	T VectorLen() const {return sqrt(square(x) + square(y) + square(z));}
};

#endif  