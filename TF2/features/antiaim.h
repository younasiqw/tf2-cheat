#ifndef ANTIAIM_H
#define ANTIAIM_H
#ifdef _WIN32
#pragma once
#endif

class CAntiAim
{
public:
	void run(user_cmd* cmd);
}; extern CAntiAim* g_antiaim;

#endif // !ANTIAIM_H