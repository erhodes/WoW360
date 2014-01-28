// WoW360.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "GameInput.h"
#include "GamepadButton.h"
#include "GamepadStick.h"

//function definitions
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
	int numButtons = 12;
	GamepadButton* buttons;
	buttons = new GamepadButton[numButtons];
	buttons[0] = GamepadButton(XINPUT_GAMEPAD_A);
	buttons[1] = GamepadButton(XINPUT_GAMEPAD_B);
	buttons[2] = GamepadButton(XINPUT_GAMEPAD_X);
	buttons[3] = GamepadButton(XINPUT_GAMEPAD_Y);
	buttons[4] = GamepadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER);
	buttons[5] = GamepadButton(XINPUT_GAMEPAD_DPAD_UP);
	buttons[6] = GamepadButton(XINPUT_GAMEPAD_DPAD_LEFT);
	buttons[7] = GamepadButton(XINPUT_GAMEPAD_DPAD_DOWN);
	buttons[8] = GamepadButton(XINPUT_GAMEPAD_DPAD_RIGHT);
	buttons[9] = GamepadButton(XINPUT_GAMEPAD_START);
	buttons[10] = GamepadButton(GamepadButton::LEFT_TRIGGER);
	buttons[11] = GamepadButton(GamepadButton::RIGHT_TRIGGER);
	GamepadStick lStick(GamepadStick::LEFT_STICK);
	GamepadStick rStick(GamepadStick::RIGHT_STICK);
	//the main loop!
	while (true){
		dwResult = XInputGetState(controllerNumber, &state);
		if (state.dwPacketNumber != lastPacketNumber){
			lastPacketNumber = state.dwPacketNumber;
			for (int i = 0; i < numButtons; i++){
				//IsButtonPressed(&buttons[i],&state);
				buttons[i].IsPressed(state.Gamepad);
			}
			lStick.IsPressed(state.Gamepad);
			rStick.IsPressed(state.Gamepad);
		}
	}
	return 0;
}

void IsButtonPressed(GamepadButton* b, XINPUT_STATE* state){
	int x = b->IsPressed(state->Gamepad);
	switch (x){
		case 0: break;
		case 1: GenerateKey(b->GetSymbol()); break;
		case 2: GenerateReleaseKey(b->GetSymbol());break;
	}
	return;
}