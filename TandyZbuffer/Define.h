#ifndef EFINE_H_
#define DEFINE_H_

#include <windows.h>

// Boolean values.
#define UGP_INVALID -1
#define UGP_OK       1
#define UGP_FAIL     0

// Window handle (need new way if porting to Mac and OpenGL).
#define WinHWND HDC

// Typedefs and enumerations.
typedef long VertexType;

enum PrimType
{
	NULL_TYPE,
	POINT_LIST,
	TRIANGLE_LIST,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
	LINE_LIST,
	LINE_STRIP
};

// Color defines.
#define UGPCOLOR_ARGB(a,r,g,b) ((unsigned long)((((a)&0xff)<<24)|\
	(((r)&0xff)<<16)|(((g)&0xff)<<8)|\
	((b)&0xff)))

#endif