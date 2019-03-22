#include "../main.h"

RecvTable* CNetVars::GetRecvTable(std::string strTableName)
{
	if (m_vpTables.empty())
		return nullptr;

	for (auto &pRecvTable : m_vpTables) // idea: wtfrdum 
	{
		if (!pRecvTable)
			continue;

		if (!strTableName.compare(pRecvTable->GetName()))
			return pRecvTable;
	}

	return nullptr;
}

int CNetVars::GetRecvProp(std::string strTableName, std::string strPropName, RecvProp** ppRecvProp)
{
	RecvTable* pRecvTable = this->GetRecvTable(strTableName);
	if (!pRecvTable)
		return 0;

	return this->GetRecvProp(pRecvTable, strPropName, ppRecvProp);
}

int CNetVars::GetRecvProp(RecvTable* pRecvTable, std::string strPropName, RecvProp** ppRecvProp)
{
	if (strPropName.empty())
		return 0;

	int iExtraOffset = 0;
	for (int i = 0; i < pRecvTable->GetNumProps(); ++i)
	{
		RecvProp* pRecvProp = pRecvTable->GetProp(i);
		RecvTable* pRecvChlidTable = pRecvProp->GetDataTable();

		if (pRecvChlidTable && (pRecvChlidTable->GetNumProps() > 0))
		{
			int iTempOffset = this->GetRecvProp(pRecvChlidTable, strPropName);
			if (iTempOffset)
				iExtraOffset += pRecvProp->GetOffset() + iTempOffset;
		}

		if (strPropName.compare(pRecvProp->GetName()))
			continue;

		if (ppRecvProp)
			*ppRecvProp = pRecvProp;

		return pRecvProp->GetOffset() + iExtraOffset;
	}

	return iExtraOffset;
}

void CNetVars::DumpTable(RecvTable* pRecvTable)
{
	for (int i = 0; i < pRecvTable->GetNumProps(); i++)
	{
		RecvProp* pRecvProp = pRecvTable->GetProp(i);
		if (!pRecvProp)
			continue;

		if (!std::string("baseclass").compare(pRecvProp->GetName()))
			continue;

		if (isdigit(pRecvProp->GetName()[0]))
			continue;

		RecvTable* pRecvDataTable = pRecvProp->GetDataTable();
		if (pRecvDataTable)
			this->DumpTable(pRecvDataTable);
	}
}

CNetVars::CNetVars(ibaseclientdll* pFirstClass)
{
	this->SetFirstClientClass(pFirstClass);
}

bool CNetVars::Setup(void)
{
	m_vpTables.clear();

	if (!m_pFirstClass)
		return false;

	ibaseclientdll* pClass = m_pFirstClass;

	while (pClass)
	{
		RecvTable* pRecvTable = pClass->GetTable();
		m_vpTables.push_back(pRecvTable);

		pClass = pClass->GetNextClass();
	}

	return true;
}

bool CNetVars::HookNetVar(std::string strTableName, std::string strNetVar, RecvVarProxyFn fn)
{
	RecvProp* pRecvProp = 0;
	this->GetRecvProp(strTableName, strNetVar, &pRecvProp);

	if (!pRecvProp)
		return false;

	pRecvProp->SetProxyFn(fn);

	return true;
}

DWORD CNetVars::GetOffset(std::string strTableName, std::string strNetVar)
{
	if (strTableName.empty() || strNetVar.empty())
		return 0;

	return (DWORD)this->GetRecvProp(strTableName, strNetVar);
}

void CNetVars::DumpNetVars(void)
{
	for (ibaseclientdll* pClass = m_pFirstClass; pClass != NULL; pClass = pClass->GetNextClass())
	{
		RecvTable* pRecvTable = pClass->GetTable();
		if (pRecvTable)
		{
			DumpTable(pRecvTable);
		}
	}
}

void CNetVars::SetFirstClientClass(ibaseclientdll* pFirstClass)
{
	m_pFirstClass = pFirstClass;
}