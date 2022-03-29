#pragma once
#include <Windows.h>
typedef struct
{
	int nMax;
	HWND hwnd;
}THREAD;

#define WM_USER_PRIME_COUNT  WM_USER + 0X0400