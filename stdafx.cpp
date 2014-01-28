// stdafx.cpp : source file that includes just the standard includes
// WoW360.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

void GenerateKey(BYTE vk){
	INPUT input;
	ZeroMemory(&input,sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	input.ki.wVk = vk;
	SendInput(1,&input,sizeof(input));
}

void GenerateReleaseKey(BYTE vk){
	INPUT input;
	ZeroMemory(&input,sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
	input.ki.wVk = vk;
	SendInput(1,&input,sizeof(input));
}

void GenerateClick(DWORD flags, LONG y, LONG x){
	INPUT input;
	ZeroMemory(&input,sizeof(input));
	input.type = INPUT_MOUSE;
	input.mi.dy = y;
	input.mi.dx = x;
	input.mi.dwFlags = flags;
	SendInput(1,&input,sizeof(input));
}

void GenerateClickRelease(DWORD flags){
	INPUT input;
	ZeroMemory(&input,sizeof(input));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = flags;
	SendInput(1,&input,sizeof(input));
}
