#ifndef OFFSETS_H
#define OFFSETS_H
#ifdef _WIN32
#pragma once
#endif

namespace offsets
{
	extern DWORD m_Local;
	extern DWORD m_fFlags;
	extern DWORD m_iTeamNum;
	extern DWORD m_iHealth;
	extern DWORD m_iMaxHealth;
	extern DWORD m_lifeState;
	extern DWORD m_bIsScoped;
	extern DWORD m_iClass;
	extern DWORD m_vecVelocity;
	extern DWORD m_nPlayerCond;
	extern DWORD m_vecViewOffset;
	extern DWORD m_nHitboxSet;

	extern void get_offsets(void);

};

#endif // OFFSETS_H

