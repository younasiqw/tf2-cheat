// Math

#include "../../main.h"

float M::DotProduct(vector& v1, float* v2)
{
	return v1.x*v2[0] + v1.y*v2[1] + v1.z*v2[2];
}

float M::Dot(const vector& v1, vector& v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void M::VectorTransform(vector& in1, matrix3x4_t& in2, vector& out)
{
	out.x = DotProduct(in1, in2[0]) + in2[0][3];
	out.y = DotProduct(in1, in2[1]) + in2[1][3];
	out.z = DotProduct(in1, in2[2]) + in2[2][3];
}

void M::VectorAngles(const vector& forward, vector& angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f) {
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
		angles[1] = 0.0f; //yaw left/right
	}
	else {
		angles[0] = atan2(-forward[2], forward.length2d()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90)
			angles[1] -= 180;
		else if (angles[1] < 90)
			angles[1] += 180;
		else if (angles[1] == 90)
			angles[1] = 0;
	}

	angles[2] = 0.0f;
}