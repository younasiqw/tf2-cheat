#include "../../main.h"

namespace i
{

	// client
	ibaseclientdll*		client{};
	icliententitylist*	entitylist{};
	iclientmodeshared*	clientmode{};

	// engine
	ivengineclient*		engineclient{};
	ienginetrace*		enginetrace{};
	ivdebugoverlay*		debugoverlay{};
	ienginevgui*		enginevgui{};
	ivefx*				efx{};
	ivmodelinfo*		modelinfo{};

	// public
	global_vars_base*	globals{};

	// vgui
	ipanel*				panel{};
	isurface*			surface{};

}