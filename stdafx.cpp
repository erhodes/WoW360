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
	input.ki.wVk = (UCHAR)VkKeyScan(vk);
	SendInput(1,&input,sizeof(input));
}

void GenerateReleaseKey(BYTE vk){
	INPUT input;
	ZeroMemory(&input,sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	input.ki.wVk = (UCHAR)VkKeyScan(vk);
	SendInput(1,&input,sizeof(input));
}