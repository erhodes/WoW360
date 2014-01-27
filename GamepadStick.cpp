#include "StdAfx.h"
#include "GamepadStick.h"

float GamepadStick::LX_DEADZONE = 10000;
float GamepadStick::LY_DEADZONE = 5000;

GamepadStick::GamepadStick(int x)
{
	pressedLeft = false;
	pressedRight = false;
	pressedForward = false;
	pressedBackward = false;
	direction = 0;
}


GamepadStick::~GamepadStick(void)
{
}

//returns 0 if unpressed, 1 if pressed, 2 if released
int GamepadStick::IsPressed(XINPUT_GAMEPAD gamepad){
	float LX = gamepad.sThumbLX;
	float LY = gamepad.sThumbLY;
	//move left?
	if ( LX < -LX_DEADZONE){
		GenerateKey('q');
		pressedLeft = true;
	} else if (pressedLeft == true){
		pressedLeft = false;
		GenerateReleaseKey('q');
	}
	//move right?
	if ( LX > LX_DEADZONE){
		GenerateKey('e');
		pressedRight = true;
	} else if (pressedRight == true){
		pressedRight = false;
		GenerateReleaseKey('e');
	}
	//move forwards?
	if (LY > LY_DEADZONE){
		GenerateKey('w');
		pressedForward = true;
	} else if (pressedForward == true){
		GenerateReleaseKey('w');
		pressedForward = false;
	}
	//move backwards?
	if (LY < -LY_DEADZONE){
		GenerateKey('s');
		pressedBackward = true;
	} else if (pressedBackward == true){
		GenerateReleaseKey('s');
		pressedBackward = false;
	}
	return 1;
}

void GamepadStick::GenerateKey(BYTE vk){
	INPUT input;
	ZeroMemory(&input,sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	input.ki.wVk = (UCHAR)VkKeyScan(vk);
	SendInput(1,&input,sizeof(input));
}

void GamepadStick::GenerateReleaseKey(BYTE vk){
	INPUT input;
	ZeroMemory(&input,sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	input.ki.wVk = (UCHAR)VkKeyScan(vk);
	SendInput(1,&input,sizeof(input));
}
