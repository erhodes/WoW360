// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"


#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Xinput.h>

using namespace std;


void GenerateKey(BYTE vk);
void GenerateReleaseKey(BYTE vk);
void GenerateClick(DWORD flags, LONG y, LONG x);
void GenerateClickRelease(DWORD flags);

// TODO: reference additional headers your program requires here
