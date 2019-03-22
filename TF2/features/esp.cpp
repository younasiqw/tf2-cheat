// Visuals
#include "../main.h"

bool CVisuals::world_to_screen(const vector& vFrom, vector& vScr)
{
	return (i::debugoverlay->screen_position(vFrom, vScr) != 1);
}

/*
void CVisuals::draw_bones(c_baseentity* pEntity, int* iBones, int count, color clrCol)
{
	for (int i = 0; i < count; i++)
	{
		if (i == count - 1)
			continue;

		vector vBone1 = pEntity->get_hitbox_position(iBones[i]);
		vector vBone2 = pEntity->get_hitbox_position(iBones[i + 1]);

		vector vScr1, vScr2;

		if (!world_to_screen(vBone1, vScr1) || !world_to_screen(vBone2, vScr2))
			continue;

		d::draw_line(vScr1.x, vScr1.y, vScr2.x, vScr2.y, clrCol);
	}
}
*/

void CVisuals::draw_player_stuff(c_baseentity* pEntity, color Col, player_info_t Info)
{

	if (!pEntity)
		return;

	matrix3x4_t& trans = pEntity->get_rgfl_coordinate_frame();

	vector min = pEntity->get_collideable_mins();
	vector max = pEntity->get_collideable_maxs();

	vector points[] =
	{
		vector(min.x, min.y, min.z),
		vector(min.x, max.y, min.z),
		vector(max.x, max.y, min.z),
		vector(max.x, min.y, min.z),
		vector(max.x, max.y, max.z),
		vector(min.x, max.y, max.z),
		vector(min.x, min.y, max.z),
		vector(max.x, min.y, max.z)
	};

	vector pointsTransformed[8];
	for (int i = 0; i < 8; i++)
	{
		M::VectorTransform(points[i], trans, pointsTransformed[i]);
	}

	vector pos = pEntity->get_abs_origin();
	vector flb;
	vector brt;
	vector blb;
	vector frt;
	vector frb;
	vector brb;
	vector blt;
	vector flt;

	if (!world_to_screen(pointsTransformed[3], flb) || !world_to_screen(pointsTransformed[5], brt)
		|| !world_to_screen(pointsTransformed[0], blb) || !world_to_screen(pointsTransformed[4], frt)
		|| !world_to_screen(pointsTransformed[2], frb) || !world_to_screen(pointsTransformed[1], brb)
		|| !world_to_screen(pointsTransformed[6], blt) || !world_to_screen(pointsTransformed[7], flt))
		return;

	vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 1; i < 8; i++) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}

	float x = left;
	float y = bottom;
	float w = right - left;
	float h = top - bottom;

	int iY = 0;

	int iHealth = pEntity->get_health();

	int iMaxHealth = pEntity->get_max_health();

	if (iHealth > iMaxHealth)
		iHealth = iMaxHealth;

	int iHealthBar = h / iMaxHealth * iHealth;
	int iHealthBarDelta = h - iHealthBar;

	int red = 255 - (iHealth * 2.55);
	int green = iHealth * 2.55;

	if (Menu::Window.VisualsTab.Box.GetState())
	{
		d::draw_outlined_rect(x - 1, y - 1, w + 2, h + 2, color(0, 0, 0, 200));
		d::draw_outlined_rect(x, y, w, h, color(255, 124, 179, 255)); // team color
		d::draw_outlined_rect(x + 1, y + 1, w - 2, h - 2, color(0, 0, 0, 200));
	}

	if (Menu::Window.VisualsTab.Name.GetState())
	{
		d::draw_string(x + w + 5, y + iY, color(255, 255, 255, 255), f::arial, ("%s"), Info.name);
		iY += d::get_esp_height();
	}

	if (Menu::Window.VisualsTab.HealthBar.GetState())
	{
		d::draw_filled_rect(x - 5, y - 1, 3, h + 2, color(0, 0, 0, 255));
		d::draw_filled_rect_secondary(x - 4, y + iHealthBarDelta, 1, iHealthBar, color(0, 255, 0, 255));
	}

	/*
	if (vars::menu_e::esp_conditions)
	{
		if (pEntity->get_player_condition() & TFCond_Cloaked) 
		{
			d::draw_string(x + w + 5, y + iY, color(255, 255, 255, 255), f::arial, ("** CLOAKED **"));
			iY += d::get_esp_height();
		}

		if (pEntity->get_player_condition() & TFCond_Disguised)
		{
			d::draw_string(x + w + 5, y + iY, color(255, 255, 255, 255), f::arial, ("** DISGUISED **"));
			iY += d::get_esp_height();
		}

		if (pEntity->get_player_condition() & TFCond_Ubercharged) 
		{
			d::draw_string(x + w + 5, y + iY, color(255, 255, 255, 255), f::arial, ("** UBER CHARGED **"));
			iY += d::get_esp_height();
		}

		if (pEntity->get_player_condition() & TFCond_Bonked)
		{
			d::draw_string(x + w + 5, y + iY, color(255, 255, 255, 255), f::arial, ("** BONKED **"));
			iY += d::get_esp_height();
		}

		if (pEntity->get_player_condition() & TFCond_OnFire)
		{
			d::draw_string(x + w + 5, y + iY, color(255, 255, 255, 255), f::arial, ("** BURNING **"));
			iY += d::get_esp_height();
		}

		if (pEntity->get_player_condition() & TFCond_MiniCrits || pEntity->get_player_condition() & TFCond_Crits) {
			d::draw_string(x + w + 5, y + iY, color(255, 255, 255, 255), f::arial, ("** CRITS **"));
			iY += d::get_esp_height();
		}
	}
	*/
}

void CVisuals::esp()
{
	player_info_t Info;

	for (int i = 1; i <= i::engineclient->get_max_clients(); i++)
	{
		// esp code 

		auto pEntity = (c_baseentity*)i::entitylist->get_client_entity(i);

		color Col = color(0, 0, 0, 0);

		if (!g::local || !pEntity || 0 >= pEntity->get_health() || pEntity->is_dormant() || i == g::local->get_index() || pEntity->get_life_state() != LIFE_ALIVE || (pEntity->get_team_num() == g::local->get_team_num())) continue;

		i::engineclient->get_player_info(pEntity->get_index(), &Info);

		draw_player_stuff(pEntity, Col, Info);
	}
}