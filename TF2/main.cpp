#include "main.h"



/*
* // Credits:
* - https://www.unknowncheats.me/forum/members/2026188.html for the base
* - https://www.unknowncheats.me/forum/members/287475.html - netvar shit
* - wtfrdum curing my autism
* - myself for the ugly ass menu
*/

DWORD WINAPI init(LPVOID lpparam)
{

	if (s::ready_to_blast()) 
	{
		s::setup_interfaces();
		s::setup_hooks();
	}

	Menu::SetupMenu();

	if (i::client)
	{
		g_pNetVars = std::make_unique<CNetVars>(i::client->GetAllClasses());
	}



	if (g_pNetVars->Setup())
	{
		offsets::get_offsets();
	}

	return TRUE;

}

BOOL WINAPI DllMain(
	_In_      HINSTANCE hinstdll,
	_In_      DWORD     fdwreason,
	_In_opt_  LPVOID    lpvreserved)
{
	switch (fdwreason) {
	case DLL_PROCESS_ATTACH:


		AllocConsole();

		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		printf("i just 'hooked' myself, haha.\n");

		DisableThreadLibraryCalls(hinstdll);
		CreateThread(nullptr, 0, init, hinstdll, 0, nullptr);
		return TRUE;
	case DLL_PROCESS_DETACH:
		FreeLibraryAndExitThread(hinstdll, 0);
		return TRUE;
	default:
		return TRUE;
	}
}