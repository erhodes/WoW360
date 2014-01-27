#include "StdAfx.h"
#include "GamepadStick.h"

float GamepadStick::LX_DEADZONE = 10000;
float GamepadStick::LY_DEADZONE = 6000;
float GamepadStick::RX_DEADZONE = 10000;
float GamepadStick::RY_DEADZONE = 8000;
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
	int scollSpeed = 10;
	if (type == LEFT_STICK){
		float LX = gamepad.sThumbLX;
		float LY = gamepad.sThumbLY;
		DirectionHelper('q',-LX,LX_DEADZONE,&pressedRight);
		DirectionHelper('e',LX, LX_DEADZONE,&pressedLeft);
		DirectionHelper('w',LY, LY_DEADZONE,&pressedForward);
		DirectionHelper('s',-LY, LY_DEADZONE,&pressedBackward);
	} else {
		//TODO: clean up this mess. Ugh.
		float RX = gamepad.sThumbRX;
		float RY = gamepad.sThumbRY;
		DirectionHelper('a',-RX, RX_DEADZONE, &pressedRight);
		DirectionHelper('d', RX, RX_DEADZONE, &pressedLeft);
		if (RY > RY_DEADZONE){
			pressedForward = true;
			INPUT input;
			ZeroMemory(&input,sizeof(input));
			input.type = INPUT_MOUSE;
			input.mi.dy = scollSpeed;
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_MOVE;
			SendInput(1,&input,sizeof(input));
		} else if (pressedForward){
			pressedForward = false;
			INPUT input;
			ZeroMemory(&input,sizeof(input));
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1,&input,sizeof(input));
		}
		if (RY < -RY_DEADZONE){
			pressedBackward = true;
			INPUT input;
			ZeroMemory(&input,sizeof(input));
			input.type = INPUT_MOUSE;
			input.mi.dy = -scollSpeed;
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_MOVE;
			SendInput(1,&input,sizeof(input));
		} else if (pressedBackward){
			pressedBackward = false;
			INPUT input;
			ZeroMemory(&input,sizeof(input));
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1,&input,sizeof(input));
		}
	}
	return 1;
}

void GamepadStick::DirectionHelper(char s, float dir, float deadzone, bool* pressed){
	if (dir > deadzone){
		GenerateKey(s);
		*pressed = true;
	} else if (*pressed == true){
		GenerateReleaseKey(s);
		*pressed = false;
	}
}
