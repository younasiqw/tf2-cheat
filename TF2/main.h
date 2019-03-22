#ifndef MAIN_H
#define MAIN_H
#ifdef _WIN32
#pragma once

#endif

// dependencies
#include <Windows.h>
#include <assert.h>
#include <Psapi.h>
#include <string>
#include <memory>

// helpers
#include "helpers/util.h"
#include <vector> // This header is part of the containers library.
#include "helpers/vector.h"
#include "helpers/vector_secondary.h"
#include "helpers/color.h"
#include "helpers/vmt.h"

// sdk
#include "sdk/sdk.h"
#include "sdk/math/math.h"
#include "netvars/netvars.h"
#include "netvars/offsets.h"
#include "sdk/XorStr.hpp"

// global
#include "global/interfaces/interfaces.h"
#include "global/hooks/hooks.h"
#include "global/fonts/fonts.h"
#include "global/draw/draw.h"
#include "global/global.h"

// menu/vars
#include "menu/menu.h"
#include "menu/GUI.h"
#include "menu/Controls.h"

// features
#include "features/aimbot.h"
#include "features/antiaim.h"
#include "features/esp.h"
#include "features/backtrack.h"

// setup
#include "setup/setup.h"

// include 
#include <intrin.h>

#endif // !MAIN_H