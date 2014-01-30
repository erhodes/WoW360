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
void IsButtonPressed(GamepadButton* b, XINPUT_STATE* state);
void SetupKeybdInputs(INPUT* s, INPUT* rs, char c);
bool PressedButton(XINPUT_GAMEPAD, void* x);
bool PressedTrigger(XINPUT_GAMEPAD, void* x);
bool PressedThumbstick(XINPUT_GAMEPAD gamepad, void* data);

//constant definitions
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;
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
	int numButtons = 15;
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
	buttons[12] = GamepadButton(XINPUT_GAMEPAD_RIGHT_THUMB);
	buttons[13] = GamepadButton(XINPUT_GAMEPAD_LEFT_THUMB);
	buttons[14] = GamepadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER);
	//buttons[15] = GamepadButton(XINPUT_GAMEPAD_LEFT_SHOULDER);
	GamepadStick lStick(GamepadStick::LEFT_STICK);
	GamepadStick rStick(GamepadStick::RIGHT_STICK);
	//some testing here
	int numInputs = 3;
	GameInput* inputs;
	inputs = new GameInput[numInputs];
	inputs[0] = GameInput(PressedButton,XINPUT_GAMEPAD_A, '1');
	inputs[1] = GameInput(PressedButton, XINPUT_GAMEPAD_X, 'A');
	inputs[2] = GameInput(PressedButton, XINPUT_GAMEPAD_B, MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP,0,0);
	//inputs[3] = MouseMapping(PressedThumbstick, MOUSEEVENTF_MOVE, MOUSEEVENTF_MOVE, 5,0, new int[LEFT,RIGHT]);


	//the main loop!
	while (true){
		dwResult = XInputGetState(controllerNumber, &state);
		if (state.dwPacketNumber != lastPacketNumber){
			lastPacketNumber = state.dwPacketNumber;
			for (int i = 0; i < numButtons; i++){
				//buttons[i].IsPressed(state.Gamepad);
			}
			//lStick.IsPressed(state.Gamepad);
			//rStick.IsPressed(state.Gamepad);
			for (int i = 0; i < numInputs; i++){
				inputs[i].Poll(state.Gamepad);
			}
		}
	}
	return 0;
}

//HELPER FUNCTIONS
void IsButtonPressed(GamepadButton* b, XINPUT_STATE* state){
	int x = b->IsPressed(state->Gamepad);
	switch (x){
		case 0: break;
		case 1: GenerateKey(b->GetSymbol()); break;
		case 2: GenerateReleaseKey(b->GetSymbol());break;
	}
	return;
}

void SetupKeybdInputs(INPUT* s, INPUT* rs, char c){
	s->ki.wVk = (UCHAR)VkKeyScan(c);
	rs->ki.wVk = (UCHAR)VkKeyScan(c);
}

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
	SHORT x = 0;
	SHORT y = 0;
	SHORT deadzone = 100;
	int* helper = (int*)data;
	int id = *helper;
	int direction = *(helper+1);
	cout << id << "," << helper << endl;
	switch (id){
		case LEFT:  y = gamepad.sThumbLY; x = gamepad.sThumbLX; break;
		case RIGHT:  y = gamepad.sThumbRY;x = gamepad.sThumbRX; break;
	}
	switch (direction){
		case LEFT: return (x>deadzone); break;
		case RIGHT: return (x < deadzone); break;
		case UP: return (y > deadzone); break;
		case DOWN: return (y < deadzone); break;
	}
	return false;
}