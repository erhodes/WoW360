#include "StdAfx.h"
#include "GamepadStick.h"

float GamepadStick::LX_DEADZONE = 10000;
float GamepadStick::LY_DEADZONE = 10000;
float GamepadStick::RX_DEADZONE = 12000;
float GamepadStick::RY_DEADZONE = 9000;
int GamepadStick::LEFT_STICK = 0;
int GamepadStick::RIGHT_STICK = 1;

GamepadStick::GamepadStick(int x)
{
	pressedLeft = false;
	pressedRight = false;
	pressedForward = false;
	pressedBackward = false;
	type = x;
}


GamepadStick::~GamepadStick(void)
{
}

//returns 0 if unpressed, 1 if pressed, 2 if released
int GamepadStick::IsPressed(XINPUT_GAMEPAD gamepad){
	int scrollSpeed = 10;
	if (type == LEFT_STICK){
		float LX = gamepad.sThumbLX;
		float LY = gamepad.sThumbLY;
		DirectionHelper('a',-LX,LX_DEADZONE,&pressedRight);
		DirectionHelper('d',LX, LX_DEADZONE,&pressedLeft);
		DirectionHelper('w',LY, LY_DEADZONE,&pressedForward);
		DirectionHelper('s',-LY, LY_DEADZONE,&pressedBackward);
	} else {
		//TODO: clean up this mess. Ugh.
		float RX = gamepad.sThumbRX;
		float RY = gamepad.sThumbRY;
		//DirectionHelper('a',-RX, RX_DEADZONE, &pressedRight);
		//DirectionHelper('d', RX, RX_DEADZONE, &pressedLeft);
		if (RY > RY_DEADZONE){
			pressedForward = true;
			GenerateClick(MOUSEEVENTF_MOVE,-scrollSpeed,0);
		} else if (pressedForward){
			pressedForward = false;
		//	GenerateClick(MOUSEEVENTF_LEFTUP,0,0);
		}
		if (RY < -RY_DEADZONE){
			pressedBackward = true;
			GenerateClick(MOUSEEVENTF_MOVE,scrollSpeed,0);
		} else if (pressedBackward){
			pressedBackward = false;
			//because theres currently no clicks involved, no button release is necessary
		}
		if (RX > RX_DEADZONE){
			GenerateClick(MOUSEEVENTF_MOVE,0,scrollSpeed);
		}
		if (RX < -RX_DEADZONE){
			GenerateClick(MOUSEEVENTF_MOVE,0,-scrollSpeed);
		}
	}
	return 1;
}

void GamepadStick::DirectionHelper(char s, float dir, float deadzone, bool* pressed){
	if (dir > deadzone){
		GenerateKey((UCHAR)VkKeyScan(s));
		*pressed = true;
	} else if (*pressed == true){
		GenerateReleaseKey((UCHAR)VkKeyScan(s));
		*pressed = false;
	}
}
