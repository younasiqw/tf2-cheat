
#pragma once

#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)

class vector_s
{
public:
	float x, y, z;

	float	Dot(const vector_s& vOther) const;

};

inline float vector_s::Dot(const vector_s& vOther) const
{
	const vector_s& a = *this;

	return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}

