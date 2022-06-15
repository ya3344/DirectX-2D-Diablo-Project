// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <fstream>
#include <d3d9.h>
#include <d3dx9.h>
#include <assert.h>
#include <time.h>
#include <process.h>
#include <io.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;

// FMOD 헤더와 라이브러리 추가
#include "fmod.h"
#include "fmod.hpp"

#pragma comment(lib, "fmodex_vc.lib")

// Console Command
//#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")

// Header
#include "Macro.h"
#include "Extern.h"
#include "Function.h"
#include "MyStruct.h"
#include "Enum.h"
#include "MyConstant.h"
#include "Typedef.h"
#include "Extern.h"

// Device
#include "Device.h"

// Design
#include "ObjFactory.h"

// Manager
#include "TileMgr.h"
#include "TextureMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "MathMgr.h"
#include "DebugMgr.h"
#include "MathMgr.h"
#include "StringMgr.h"
#include "CollisionMgr.h"
#include "EnemyMgr.h"
#include "SubjectMgr.h"
#include "SoundMgr.h"

