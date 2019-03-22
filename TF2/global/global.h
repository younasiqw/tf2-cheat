#ifndef GLOBAL_H
#define GLOBAL_H
#ifdef _WIN32
#pragma once
#endif

namespace g
{
	extern c_baseentity*	local;
	extern user_cmd*		cmd;
	extern bool*		send_packet;

	extern int				screen_width;
	extern int				screen_height;
}

#endif // !GLOBAL_H
