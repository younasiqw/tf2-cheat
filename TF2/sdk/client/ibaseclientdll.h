#ifndef IBASECLIENTDLL_H
#define IBASECLIENTDLL_H
#ifdef _WIN32
#pragma once
#endif

#include "dt_common.h"
#include "dt_recv.h"

class ibaseclientdll
{
public:

	ibaseclientdll(char *pNetworkName, CreateClientClassFn createFn, CreateEventFn createEventFn, RecvTable *pRecvTable)
	{
		m_pNetworkName = pNetworkName;
		m_pCreateFn = createFn;
		m_pCreateEventFn = createEventFn;
		m_pRecvTable = pRecvTable;

		// Link it in
		m_pNext = g_pClientClassHead;
		g_pClientClassHead = this;
	}

	const char* GetName()
	{
		return m_pNetworkName;
	}

	RecvTable* GetTable(void)
	{
		return m_pRecvTable;
	}

	ibaseclientdll* GetNextClass(void)
	{
		return m_pNext;
	}

	int GetClassID(void)
	{
		return m_ClassID;
	}

public:
	CreateClientClassFn		m_pCreateFn;
	CreateEventFn			m_pCreateEventFn;	// Only called for event objects.
	char					*m_pNetworkName;
	RecvTable				*m_pRecvTable;
	ibaseclientdll				*m_pNext;
	int						m_ClassID;	// Managed by the engine.

	ibaseclientdll * GetAllClasses()
	{
		typedef ibaseclientdll*(__thiscall* OriginalFn)(void*);
		return u::call_vfunc<OriginalFn>(this, 8)(this);
	}
};

class IBaseClientDLL
{
public:



};

#define CLIENT_DLL_INTERFACE_VERSION "VClient017"

#endif // IBASECLIENTDLL_H