#pragma once
#pragma warning(disable: 6066)
#include <windows.h>
#include <iostream>

inline uint64_t UObjectBase, EngineBase, CoreBase, ReturnalBase;

#include "util.hpp"
#include "engine.hpp"
#include "game.hpp"
#include "globals.hpp"

#include "..\detours.hpp"
#pragma comment(lib, "detours.lib")

inline UWorldProxy GWorld;
inline UObject* pFont;