#ifndef AIMBOT_H
#define AIMBOT_H
#ifdef _WIN32
#pragma once
#endif

class CAimbot
{
public:
	void run(user_cmd* cmd);
}; extern CAimbot* g_aimbot;

#endif // !AIMBOT_H