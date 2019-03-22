#ifndef NETVARS_H
#define NETVARS_H
#ifdef _WIN32

#pragma once
#endif

class CNetVars
{
private:
	ibaseclientdll* m_pFirstClass;
	std::vector<RecvTable*>	m_vpTables;
private:
	RecvTable * GetRecvTable(std::string strTableName);
	int	GetRecvProp(std::string strTableName, std::string strPropName, RecvProp ** ppRecvProp = NULL);
	int	GetRecvProp(RecvTable* pRecvTable, std::string strPropName, RecvProp ** ppRecvProp = NULL);
	void DumpTable(RecvTable* pRecvTable);
public:
	CNetVars(ibaseclientdll * pFirstClass);
	bool Setup(void);
	bool HookNetVar(std::string strTableName, std::string strNetVar, RecvVarProxyFn fn);
	DWORD GetOffset(std::string strTableName, std::string strNetVar);
	void DumpNetVars(void);
	void SetFirstClientClass(ibaseclientdll * pFirstClass);
}; extern std::unique_ptr<CNetVars> g_pNetVars;

#endif // NETVARS_H