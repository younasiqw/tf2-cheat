#include "../main.h"

#include <iostream>

namespace offsets
{
	DWORD m_Local = 0;
	DWORD m_fFlags = 0;
	DWORD m_iTeamNum = 0;
	DWORD m_iHealth = 0;
	DWORD m_iMaxHealth = 0;
	DWORD m_lifeState = 0;
	DWORD m_bIsScoped = 0;
	DWORD m_iClass = 0;
	DWORD m_vecVelocity = 0;
	DWORD m_nPlayerCond = 0;
	DWORD m_vecViewOffset;
	DWORD m_nHitboxSet;
}

void offsets::get_offsets(void)
{
	offsets::m_Local = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_Local")); 
	offsets::m_fFlags = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_fFlags"));
	offsets::m_iTeamNum = g_pNetVars->GetOffset(XorStr("DT_BaseEntity"), XorStr("m_iTeamNum"));
	offsets::m_iHealth = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_iHealth"));
	offsets::m_iMaxHealth = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_iMaxHealth"));
	offsets::m_lifeState = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_lifeState"));
	offsets::m_bIsScoped = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_bIsScoped"));
	offsets::m_iClass = g_pNetVars->GetOffset(XorStr("DT_TFPlayer"), XorStr("m_iClass"));
	offsets::m_vecVelocity = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_vecVelocity[0]"));
	offsets::m_nPlayerCond = g_pNetVars->GetOffset(XorStr("DT_TFPlayer"), XorStr("m_nPlayerCond"));
	offsets::m_vecViewOffset = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_vecViewOffset[0]"));
	offsets::m_nHitboxSet = g_pNetVars->GetOffset(XorStr("DT_BaseAnimating"), XorStr("m_nHitboxSet"));

}