#pragma once

constexpr BYTE MONEY = 0x0001; // 0000 0001
constexpr BYTE STONE = 0x0002; // 0000 0010
constexpr BYTE ITEM = 0x0004; // 0000 0100

constexpr DWORD	KEY_LBUTTON = 0x00000001;	//0000 0001
constexpr DWORD KEY_RBUTTON = 0x00000002;	//0000 0010
constexpr DWORD	KEY_ENTER = 0x00000004;		//0000 0100
constexpr DWORD	KEY_SPACE = 0x00000008;		//0000 1000

constexpr DWORD	KEY_1 = 0x00000010;         
constexpr DWORD	KEY_2 = 0x00000020;
constexpr DWORD	KEY_3 = 0x00000040;
constexpr DWORD	KEY_4 = 0x00000080;

constexpr DWORD	KEY_D = 0x00000100;
constexpr DWORD	KEY_F = 0x00000200;
constexpr DWORD	KEY_C = 0x00000400;
constexpr DWORD	KEY_Q = 0x00000800;

constexpr DWORD	KEY_A = 0x00001000;
constexpr DWORD	KEY_H = 0x00002000;
constexpr DWORD	KEY_W = 0x00004000;
constexpr DWORD	KEY_B = 0x00008000;

constexpr DWORD	KEY_5 = 0x00010000;
constexpr DWORD	KEY_6 = 0x00020000;
constexpr DWORD	KEY_7 = 0x00040000;
constexpr DWORD	KEY_8 = 0x00080000;

constexpr DWORD	KEY_S = 0x00100000;
constexpr DWORD	KEY_K = 0x00200000;
constexpr DWORD	KEY_L = 0x00400000;

constexpr DWORD	KEY_F1 = 0x01000000;
constexpr DWORD	KEY_F2 = 0x02000000;
constexpr DWORD	KEY_F3 = 0x04000000;
constexpr DWORD	KEY_F4 = 0x08000000;
constexpr DWORD	KEY_F5 = 0x10000000;
constexpr DWORD	KEY_F6 = 0x20000000;
constexpr DWORD	KEY_F7 = 0x40000000;
constexpr DWORD	KEY_F8 = 0x80000000;



constexpr float SCROLL_DISTANCE = 500.f;
constexpr float SCROLL_SPEED= 1.f;
constexpr int KEY_SIZE = 32;
constexpr int VIRTUAL_KEY_MAX = 0xff;

constexpr TCHAR* STAGE_NAME = L"Act4";

static constexpr int ENEMY_KIND = 100;