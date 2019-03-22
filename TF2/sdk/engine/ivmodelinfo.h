#ifndef IVMODELINFO_H
#define IVMODELINFO_H
#ifdef _WIN32
#pragma once
#endif

class ivmodelinfo
{
public:
	DWORD* get_model(int index)
	{
		typedef DWORD*(__thiscall* GetModelFn)(void*, int);
		return u::call_vfunc<GetModelFn>(this, 1)(this, index);
	}

	int	get_model_index(const char* name)
	{
		typedef int(__thiscall* GetModelIndexFn)(void*, const char*);
		return u::call_vfunc< GetModelIndexFn >(this, 2)(this, name);
	}

	const char* get_model_name(const DWORD* model)
	{
		typedef const char* (__thiscall* GetModelNameFn)(void*, const DWORD*);
		return u::call_vfunc< GetModelNameFn >(this, 3)(this, model);
	}

	studiohdr_t* get_studiomodel(const DWORD *mod)
	{
		typedef studiohdr_t* (__thiscall* GetStudiomodelFn)(void*, const DWORD*);
		return u::call_vfunc< GetStudiomodelFn >(this, 28)(this, mod);
	}
};


#endif // !IVMODELINFO_H
