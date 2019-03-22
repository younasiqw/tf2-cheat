#ifndef VISUALS_H
#define VISUALS_H
#ifdef _WIN32
#pragma once
#endif

class CVisuals
{
public:
	bool world_to_screen(const vector& vFrom, vector& vScr);
	void draw_player_stuff(c_baseentity* pEntity, color Col, player_info_t Info);
	void draw_bones(c_baseentity* pEntity, int* iBones, int count, color clrCol);
	void esp();
}; extern CVisuals* g_visuals;

#endif // !VISUALS_H