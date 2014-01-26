// WoW360.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "GameInput.h"
#include "GamepadButton.h"

using namespace std;

//function definitions
void GenerateKey(BYTE vk);
void GenerateReleaseKey(BYTE vk);
bool aIsPressed = false;
void IsButtonPressed(GamepadButton* b, XINPUT_STATE* state);

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
	aIsPressed = true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (SetWindow("World of Warcraft"))
		cout << "Game detected\n";
	else
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
	int numButtons = 4;
	GamepadButton* buttons;
	buttons = new GamepadButton[numButtons];
	buttons[0] = GamepadButton(XINPUT_GAMEPAD_A);
	buttons[1] = GamepadButton(XINPUT_GAMEPAD_B);
	buttons[2] = GamepadButton(XINPUT_GAMEPAD_X);
	buttons[3] = GamepadButton(XINPUT_GAMEPAD_Y);
	//the main loop!
	while (true){
		dwResult = XInputGetState(controllerNumber, &state);
		if (state.dwPacketNumber != lastPacketNumber){
			lastPacketNumber = state.dwPacketNumber;
			for (int i = 0; i < 4; i++){
				IsButtonPressed(&buttons[i],&state);
			}
		}
	}
	return 0;
}

void IsButtonPressed(GamepadButton* b, XINPUT_STATE* state){
	int x = b->IsPressed(state->Gamepad);
	switch (x){
		case 0: break;
		case 1: GenerateKey((UCHAR)VkKeyScan(b->GetSymbol())); break;
		case 2: GenerateReleaseKey((UCHAR)VkKeyScan(b->GetSymbol()));break;
	}
	return;
}


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
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	input.ki.wVk = (UCHAR)VkKeyScan(vk);
	SendInput(1,&input,sizeof(input));
}