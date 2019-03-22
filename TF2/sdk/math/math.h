#ifndef MATH_H
#define MATH_H
#ifdef _WIN32
#pragma once
#endif

#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define FastSqrt(x)	::sqrtf(x)

namespace M 
{
	extern float DotProduct(vector& v1, float* v2);
	extern float Dot(const vector& v1, vector& v2);
	extern void VectorTransform(vector& in1, matrix3x4_t& in2, vector& out);
	extern void VectorAngles(const vector& forward, vector& angles);
}

#endif // !MATH_H