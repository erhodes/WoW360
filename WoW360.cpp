/*
	WOW360 by Eric Rhodes, January 2014.
	This program synthesizes keyboard and mouse events (using the Windows SendInput method)
	in response to input from an attached XBox 360 controller.

	It's intended purpose is to play World of Warcraft with a 360 controller.
*/
#pragma once
#include "stdafx.h"
#include "GamepadButton.h"
#include "GamepadStick.h"
#include "GameInput.h"

//function definitions
bool PressedButton(XINPUT_GAMEPAD, void* x);
bool PressedTrigger(XINPUT_GAMEPAD, void* x);
bool PressedThumbstick(XINPUT_GAMEPAD gamepad, void* data);

//constant definitions
const int LEFT = 0;
const int RIGHT = 1;
const int LT_LEFT = 2;
const int LT_RIGHT = 3;
const int LT_UP = 4;
const int LT_DOWN = 5;
//this function is unnecessary
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
	//create the buttons
	//some testing here
	int numInputs = 20;
	GameInput* inputs;
	inputs = new GameInput[numInputs];
	inputs[0] = GameInput(PressedButton,XINPUT_GAMEPAD_A, '1');
	inputs[1] = GameInput(PressedButton,XINPUT_GAMEPAD_B, VK_ESCAPE);
	inputs[2] = GameInput(PressedButton,XINPUT_GAMEPAD_X, '2');
	inputs[3] = GameInput(PressedButton,XINPUT_GAMEPAD_Y, '3');
	inputs[4] = GameInput(PressedButton,XINPUT_GAMEPAD_DPAD_DOWN, '4');
	inputs[5] = GameInput(PressedButton,XINPUT_GAMEPAD_DPAD_UP, '5');
	inputs[6] = GameInput(PressedButton,XINPUT_GAMEPAD_DPAD_LEFT, '6');
	inputs[7] = GameInput(PressedButton,XINPUT_GAMEPAD_DPAD_RIGHT, '7');
	inputs[8] = GameInput(PressedButton,XINPUT_GAMEPAD_LEFT_SHOULDER, 'q');
	inputs[9] = GameInput(PressedButton,XINPUT_GAMEPAD_RIGHT_SHOULDER, 'e');
	inputs[10] = GameInput(PressedTrigger,LEFT,VK_LCONTROL);
	inputs[11] = GameInput(PressedTrigger,LEFT,VK_RSHIFT);
	inputs[12] = GameInput(PressedButton,XINPUT_GAMEPAD_START,VK_SPACE);
	inputs[13] = GameInput(PressedButton,XINPUT_GAMEPAD_BACK,VK_TAB);
	inputs[14] = GameInput(PressedButton,XINPUT_GAMEPAD_LEFT_THUMB,MOUSEEVENTF_LEFTDOWN,MOUSEEVENTF_LEFTUP,0,0);
	inputs[15] = GameInput(PressedButton,XINPUT_GAMEPAD_LEFT_THUMB,MOUSEEVENTF_RIGHTDOWN,MOUSEEVENTF_RIGHTUP,0,0);
	inputs[16] = GameInput(PressedTrigger,LT_LEFT,'a');
	inputs[17] = GameInput(PressedTrigger,LT_RIGHT,'d');
	inputs[18] = GameInput(PressedTrigger,LT_UP,'w');
	inputs[19] = GameInput(PressedTrigger,LT_DOWN,'s');


	//the main loop!
	while (true){
		dwResult = XInputGetState(controllerNumber, &state);
		if (state.dwPacketNumber != lastPacketNumber){
			lastPacketNumber = state.dwPacketNumber;
			for (int i = 0; i < numInputs; i++){
				inputs[i].Poll(state.Gamepad);
			}
		}
	}
	return 0;
}

//HELPER FUNCTIONS
bool PressedButton(XINPUT_GAMEPAD gamepad, void* x){
	int id = *((int* )x);
	return (gamepad.wButtons & id);
}

bool PressedTrigger(XINPUT_GAMEPAD gamepad, void* x){
	BYTE magnitude = 0;
	int id = *((int* )x);
	//get the magnitude of the appropriate trigger
	if (id == LEFT){
		magnitude = gamepad.bLeftTrigger;
	} else if (id == RIGHT){
		magnitude = gamepad.bRightTrigger;
	}
	//determine if the magnitude is over the deadzone
	if (magnitude > GamepadButton::TRIGGER_THRESHOLD){
		return true;
	}else { return false;}
}

bool PressedThumbstick(XINPUT_GAMEPAD gamepad, void* data){
	int id = *(int*)(data);
	short deadzone = 4000;
	switch (id){
		case LT_UP: return (gamepad.sThumbLY > deadzone); break;
		case LT_DOWN: return (-gamepad.sThumbLY > deadzone); break;
		case LT_LEFT: return (gamepad.sThumbLY > deadzone); break;
		case LT_RIGHT: return (-gamepad.sThumbLY > deadzone); break;
	}
	return false;
}