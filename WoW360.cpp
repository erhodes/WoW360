// WoW360.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <Xinput.h>

using namespace std;

void GenerateKey(BYTE vk);

bool SetWindow(LPCSTR name){
	HWND hwnd = FindWindowA(NULL,name);
	if (hwnd == NULL){
		return false;
	}else{
		SetForegroundWindow(hwnd);
		return true;
	}
}

void PressedA(){
	GenerateKey((UCHAR)VkKeyScan('a'));
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (!SetWindow("World of Warcraft"))
		cout << "Could not find game\n";
	//test to make sure a controller is detected
	DWORD dwResult;
	XINPUT_STATE state;
	DWORD controllerNumber = 0;
	dwResult = XInputGetState(controllerNumber, &state);
	if (dwResult == ERROR_SUCCESS){
		cout << "Controller detected\n";
	} else{
		cout << "No controller detected \n";
	}
	//set up for the main loop
	DWORD lastPacketNumber = 0;
	XINPUT_GAMEPAD gamepad;
	//the main loop!
	while (true){
		dwResult = XInputGetState(controllerNumber, &state);
		if (state.dwPacketNumber != lastPacketNumber){
			lastPacketNumber = state.dwPacketNumber;
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A){
				PressedA();
				cout << "a was pressed\n";
			}
		}
	}
	return 0;
}


void GenerateKey(BYTE vk){
	INPUT input;
	ZeroMemory(&input,sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	input.ki.wVk = vk;
	SendInput(1,&input,sizeof(input));
}