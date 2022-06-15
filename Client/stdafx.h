// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
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

// FMOD ����� ���̺귯�� �߰�
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

