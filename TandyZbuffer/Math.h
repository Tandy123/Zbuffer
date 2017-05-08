#ifndef MATH_H_
#define MATH_H_

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//平方函数
template <typename T>
inline T square(const T& x) {return x*x;}

//求最大最小函数
template<typename T>
inline T callWithMax(const T&a ,const T& b)
{
	return (a>b ? a : b);
}
template<typename T>
inline T callWithMin(const T&a ,const T& b)
{
	return (a<b ? a : b);
}

inline int Round(const double &x){
	return (int)(x+0.5);
}

template<typename T>
bool min_max(T a[],int n,T b[])
{
	T max,min;
	bool even=false;

	if(n/2==0)
		even=true;

	if(even==false){
		min = max = a[0];	
		int mid = (n-1)/2;
		for(int i=1;i<mid+1;i++){	
			if(max<callWithMax(a[i],a[n-i]))
				max = callWithMax(a[i],a[n-i]);
			if(min>callWithMin(a[i],a[n-i]))
				min = callWithMin(a[i],a[n-i]);
		}
	}
	else{
		if(a[0]<=a[1]){
			min = a[0];
			max = a[1];
		}
		else{
			min = a[1];
			max = a[0];
		}
		int mid = (n-2)/2;
		for(int i=2;i<2+mid;i++){
			if(max<callWithMax(a[i],a[n-i-1]))
				max = callWithMax(a[i],a[n-i-1]);
			if(min>callWithMin(a[i],a[n-i-1]))
				min = callWithMin(a[i],a[n-i-1]);
		}
	}		
	b[0] = max;	
	b[1] = min;

	return true;
}

inline double  ToRad(const double &a){return M_PI*a/180.0;}

#endif