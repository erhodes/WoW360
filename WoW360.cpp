/*
	WOW360 by Eric Rhodes, January 2014.
	This program synthesizes keyboard and mouse events (using the Windows SendInput method)
	in response to input from an attached XBox 360 controller.

	It's intended purpose is to play World of Warcraft with a 360 controller.
*/
#pragma once
#include "stdafx.h"
#include "GameInput.h"
#include "MouseMapping.h"

//this function checks to see if the given window is open.
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
	inputs[0] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_A, '1');
	inputs[1] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_B, VK_ESCAPE);
	inputs[2] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_X, '2');
	inputs[3] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_Y, '3');
	inputs[4] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_DPAD_UP, '4');
	inputs[5] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_DPAD_LEFT, '5');
	inputs[6] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_DPAD_DOWN, '6');
	inputs[7] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_DPAD_RIGHT, '7');
	inputs[8] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_LEFT_SHOULDER, 'q');
	inputs[9] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_RIGHT_SHOULDER, 'e');
	inputs[10] = GameInput(GameInput::PressedTrigger,LEFT,VK_LCONTROL);
	inputs[11] = GameInput(GameInput::PressedTrigger,RIGHT,VK_RSHIFT);
	inputs[12] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_START,VK_SPACE);
	inputs[13] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_BACK,VK_TAB);
	inputs[14] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_LEFT_THUMB,MOUSEEVENTF_LEFTDOWN,MOUSEEVENTF_LEFTUP,0,0);
	inputs[15] = GameInput(GameInput::PressedButton,XINPUT_GAMEPAD_RIGHT_THUMB,MOUSEEVENTF_RIGHTDOWN,MOUSEEVENTF_RIGHTUP,0,0);
	inputs[16] = GameInput(GameInput::PressedThumbstick,LT_LEFT,'a');
	inputs[17] = GameInput(GameInput::PressedThumbstick,LT_RIGHT,'d');
	inputs[18] = GameInput(GameInput::PressedThumbstick,LT_UP,'w');
	inputs[19] = GameInput(GameInput::PressedThumbstick,LT_DOWN,'s');
	int numMouseInputs = 4;
	MouseMapping* mouseInputs = new MouseMapping[numMouseInputs];
	mouseInputs[0] = MouseMapping(GameInput::PressedThumbstick,RT_DOWN,MOUSEEVENTF_MOVE,MOUSEEVENTF_MOVE, 0,scrollSpeed);
	mouseInputs[1] = MouseMapping(GameInput::PressedThumbstick,RT_UP,MOUSEEVENTF_MOVE,MOUSEEVENTF_MOVE, 0,-scrollSpeed);
	mouseInputs[2] = MouseMapping(GameInput::PressedThumbstick,RT_LEFT,MOUSEEVENTF_MOVE,MOUSEEVENTF_MOVE, -scrollSpeed,0);
	mouseInputs[3] = MouseMapping(GameInput::PressedThumbstick,RT_RIGHT,MOUSEEVENTF_MOVE,MOUSEEVENTF_MOVE,scrollSpeed,0);


	//MouseMapping test = MouseMapping(GameInput::PressedThumbstick,RT_DOWN,MOUSEEVENTF_MOVE,MOUSEEVENTF_MOVE,0,scrollSpeed);

	//the main loop!
	DWORD timeElapsed = GetTickCount();
	DWORD timeInterval = 10;
	while (true){

		dwResult = XInputGetState(controllerNumber, &state);
		if (GetTickCount() > timeElapsed +timeInterval){
		//if (state.dwPacketNumber != lastPacketNumber){
			//lastPacketNumber = state.dwPacketNumber;
			timeElapsed = GetTickCount();
			for (int i = 0; i < numInputs; i++){
				inputs[i].Poll(state.Gamepad);
			}
			for (int i = 0; i < numMouseInputs; i++){
				mouseInputs[i].Poll(state.Gamepad);
			}
			//test.Poll(state.Gamepad);
		}
	}
	return 0;
}