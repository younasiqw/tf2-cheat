#include "../main.h"

CAimbot*	g_aimbot;
CAntiAim*	g_antiaim;
CVisuals*	g_visuals;

std::unique_ptr<CNetVars>	g_pNetVars = nullptr;

bool __fastcall hk_create_move(iclientmodeshared* ecx, PVOID edx, float input_sample_time, user_cmd* cmd)
{
	static auto original_create_move = h::client_mode_hook->get_original_function< decltype(&hk_create_move) >(21);

	if (!cmd->command_number)
		return false;

	// acquire a pointer to our local player
	g::local = reinterpret_cast<c_baseentity*>(i::entitylist->get_client_entity(i::engineclient->get_local_player()));

	// acquire a pointer to bsendpacket
	uintptr_t _bp; __asm mov _bp, ebp;
	g::send_packet = (bool*)(***(uintptr_t***)_bp - 1);

	// set up a global usercmd pointer
	if (g::local != nullptr || cmd != nullptr)
	{
		g_aimbot->run(cmd);
		//g_antiaim->run(cmd);
	}

	// misc features
	if (!(g::local->get_flags() & FL_ONGROUND) && cmd->buttons & IN_JUMP)
	{
		if (Menu::Window.MiscTab.Bunnyhop.GetState())
		{
			cmd->buttons &= ~IN_JUMP;
		}

		if (Menu::Window.MiscTab.AutoStrafe.GetState())
		{
			if (cmd->moused_x > 1 || cmd->moused_x < -1)
			{
				cmd->side_move = cmd->moused_x > 1 ? 450.f : -450.f;
			}
		}
	}

	return false;

}

/*
void __stdcall hk_get_override_fov(CViewSetup* pSetup)
{
	static auto original_get_viewmodel_fov = h::client_mode_hook->get_original_function< decltype(&hk_get_override_fov) >(16);

	if (pSetup->m_fov != 20.0f && !g::local->is_scoped() && pSetup->m_fov != vars::menu_e::misc_fov)
	{
		pSetup->m_fov = vars::menu_e::misc_fov;
	}

}
*/

float __fastcall hk_get_viewmodel_fov(iclientmodeshared* ecx, int edx)
{
	typedef void(__thiscall *override_view_t)(void* _this, CViewSetup* setup);
	typedef float(__thiscall *get_fov_t)(void*);

	static auto original_get_viewmodel_fov = h::client_mode_hook->get_original_function< decltype(&hk_get_viewmodel_fov) >(32);

	float flOriginalFOV = original_get_viewmodel_fov(ecx, edx);

	/*
	if (vars::menu_e::misc_viewmodel_fov)
	{
		return flOriginalFOV + vars::menu_e::misc_viewmodel_fov;
	}
	*/

	return flOriginalFOV;

}

/*
int __fastcall hk_key_event(ibaseclientdll* ecx, PVOID edx, int event_code, int key_num, const char* current_binding)
{

	static auto original_key_event = h::client_hook->get_original_function< decltype(&hk_key_event) >(20);

	if (event_code == 1) {
		menu::handle_input(key_num);
	}

	return original_key_event(ecx, edx, event_code, key_num, current_binding);

}
*/

void __fastcall hk_paint_traverse(ipanel* ecx, PVOID edx, unsigned int vgui_panel, bool force_repaint, bool allow_force)
{
	static auto original_paint_traverse = h::panel_hook->get_original_function< decltype(&hk_paint_traverse) >(41);
	original_paint_traverse(ecx, edx, vgui_panel, force_repaint, allow_force);

	static unsigned int vgui_focus_overlay;

	if (vgui_focus_overlay == NULL)
	{
		const char* szName = i::panel->get_name(vgui_panel);
		if (szName[0] == 'F' && szName[5] == 'O' &&  szName[12] == 'P') 
		{
			vgui_focus_overlay = vgui_panel;
		}
	}

	auto quick_do_fonts = [&]()
	{
		f::arial = i::surface->create_font();
		i::surface->set_font_glyph_set(f::arial, "Calibri", 16, 0, 0, 0, FONTFLAG_OUTLINE);

		f::verdana = i::surface->create_font();
		i::surface->set_font_glyph_set(f::verdana, "Verdana", 14, 400, 0, 0, FONTFLAG_DROPSHADOW);

		f::menu_elements = i::surface->create_font();
		i::surface->set_font_glyph_set(f::menu_elements, "Calibri", 16, 50, 0, 0, FONTFLAG_OUTLINE);

		f::menu_tabs = i::surface->create_font();
		i::surface->set_font_glyph_set(f::menu_tabs, "Calibri", 16, 50, 0, 0, FONTFLAG_OUTLINE);

		f::menu_main = i::surface->create_font();
		i::surface->set_font_glyph_set(f::menu_main, "Verdana", 12, 400, 0, 0, FONTFLAG_ANTIALIAS);

		f::menu_main_verdana = i::surface->create_font();
		i::surface->set_font_glyph_set(f::menu_main_verdana, "Verdana", 12, 700, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE | FONTFLAG_DROPSHADOW);

		f::esp = i::surface->create_font();
		i::surface->set_font_glyph_set(f::esp, "Calibri", 16, 50, 0, 0, FONTFLAG_OUTLINE);

		i::engineclient->get_screen_size(g::screen_width, g::screen_height);
	};

	static bool once = true;
	if (once)
	{
		quick_do_fonts();
		once = false;
	}

	if (vgui_focus_overlay == vgui_panel)
	{
		player_info_t Info;

		d::draw_string(5, 60, color(255, 255, 255), f::arial, "built " __DATE__ " at " __TIME__);

		g_visuals->esp();

		Menu::DoUIFrame();
		//i::panel->set_mouse_input_enabled(vgui_panel, GUI.enabled);
	}

	if (vgui_panel == i::enginevgui->get_panel(PANEL_CLIENTDLL))
	{
		int width, height; i::engineclient->get_screen_size(width, height);

		if (g::screen_width != width || g::screen_height != height) 
		{
			i::engineclient->get_screen_size(g::screen_width, g::screen_height);
			quick_do_fonts();
		}

		g_visuals->esp();
	}
}

namespace s
{

	void setup_interfaces()
	{

		create_interface_fn client	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface"));
		create_interface_fn engine	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"));
		create_interface_fn vgui	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("vgui2.dll"), "CreateInterface"));
		create_interface_fn mat		= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("vguimatsurface.dll"), "CreateInterface"));

		// client
		i::client		= static_cast<ibaseclientdll*>(client("VClient017", nullptr));
		i::entitylist	= static_cast<icliententitylist*>(client("VClientEntityList003", nullptr));
		i::clientmode	= **(iclientmodeshared***)((*(DWORD**)i::client)[10] + 0x5);

		// engine
		i::engineclient	= static_cast<ivengineclient*>(engine("VEngineClient013", nullptr));
		i::enginetrace	= static_cast<ienginetrace*>(engine("EngineTraceClient003", nullptr));
		i::debugoverlay = static_cast<ivdebugoverlay*>(engine("VDebugOverlay003", nullptr));
		i::enginevgui	= static_cast<ienginevgui*>(engine("VEngineVGui001", nullptr));
		i::efx			= static_cast<ivefx*>(engine("VEngineEffects001", nullptr));
		i::modelinfo	= static_cast<ivmodelinfo*>(engine("VModelInfoClient006", nullptr));

		// public
		i::globals		= *reinterpret_cast<global_vars_base**>(u::find_signature("engine.dll", "A1 ? ? ? ? 8B 11 68") + 8);

		// vgui
		i::surface		= static_cast<isurface*>(mat("VGUI_Surface030", nullptr));
		i::panel		= static_cast<ipanel*>(vgui("VGUI_Panel009", nullptr));

	}

	void setup_hooks()
	{

		if (i::clientmode != nullptr) {

			h::client_mode_hook = std::make_unique<vmt_manager>(i::clientmode);

			h::client_mode_hook->hook_function(reinterpret_cast<bool*>(hk_create_move), 21);
			h::client_mode_hook->hook_function(reinterpret_cast<float*>(hk_get_viewmodel_fov), 32);
			//h::client_mode_hook->hook_function(reinterpret_cast<void*>(hk_get_override_fov), 16);

		}


		if (i::client != nullptr) 
		{
			h::client_hook = std::make_unique<vmt_manager>(i::client);
			//h::client_hook->hook_function(reinterpret_cast<int*>(hk_key_event), 20);
		}

		if (i::panel != nullptr)
		{
			h::panel_hook = std::make_unique<vmt_manager>(i::panel);
			h::panel_hook->hook_function(reinterpret_cast<void*>(hk_paint_traverse), 41);
		}

	}

	bool ready_to_blast()
	{

		if (i::client == nullptr)
			return true;

		return false;

	}

}
