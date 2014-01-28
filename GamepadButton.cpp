#include "StdAfx.h"
#include "GamepadButton.h"


BYTE GamepadButton::TRIGGER_THRESHOLD =150;

GamepadButton::GamepadButton(){}

GamepadButton::GamepadButton(int x)
{
	id = x;
	pressed = false;
	simulateMouse = false;
	Pressed = &GamepadButton::PressedButton;
	
	ZeroMemory(&signal,sizeof(signal));
	ZeroMemory(&signal,sizeof(releaseSignal));
	switch (x){
		case XINPUT_GAMEPAD_A: virtualKey = 0; signal.mi.dwFlags=MOUSEEVENTF_LEFTDOWN,
			releaseSignal.mi.dwFlags = MOUSEEVENTF_LEFTUP, simulateMouse=true; break;
		case XINPUT_GAMEPAD_B: virtualKey = '3'; break;
		case XINPUT_GAMEPAD_X: virtualKey = '1'; break;
		case XINPUT_GAMEPAD_Y: virtualKey = '2'; break;
		case XINPUT_GAMEPAD_RIGHT_SHOULDER: virtualKey = VK_TAB; break;
		case XINPUT_GAMEPAD_DPAD_UP: virtualKey = '4'; break;
		case XINPUT_GAMEPAD_DPAD_RIGHT: virtualKey = '5'; break;
		case XINPUT_GAMEPAD_DPAD_LEFT: virtualKey = '6'; break;
		case XINPUT_GAMEPAD_DPAD_DOWN: virtualKey = '7'; break;
		case XINPUT_GAMEPAD_START: virtualKey = VK_SPACE; break;
		case RIGHT_TRIGGER: virtualKey = VK_RSHIFT;Pressed = &GamepadButton::PressedTrigger; break;
		case LEFT_TRIGGER: virtualKey = VK_LCONTROL;Pressed = &GamepadButton::PressedTrigger; break;
	}
	if (!simulateMouse){
	signal.type = INPUT_KEYBOARD;
	signal.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	signal.ki.wVk = virtualKey;
	releaseSignal.type = INPUT_KEYBOARD;
	releaseSignal.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
	releaseSignal.ki.wVk = virtualKey;
	} else {
		signal.type = INPUT_MOUSE;
		releaseSignal.type = INPUT_MOUSE;
	}
}


GamepadButton::~GamepadButton(void)
{
}

bool GamepadButton::PressedButton(XINPUT_GAMEPAD gamepad){
	return (gamepad.wButtons & id) && (pressed == false);
}

bool GamepadButton::PressedTrigger(XINPUT_GAMEPAD gamepad){
	BYTE magnitude;
	//get the magnitude of the appropriate trigger
	if (id == LEFT_TRIGGER){
		magnitude = gamepad.bLeftTrigger;
	} else if (id == RIGHT_TRIGGER){
		magnitude = gamepad.bRightTrigger;
	}
	//determine if the magnitude is over the deadzone
	if (magnitude > TRIGGER_THRESHOLD){
		return true;
	}else { return false;}
}

//returns 0 if unpressed, 1 if pressed, 2 if released
int GamepadButton::IsPressed(XINPUT_GAMEPAD gamepad){
	if ( (this->*Pressed)(gamepad)){
		// to trigger only on the first press, add: 
		pressed = true;
		SendInput(1,&signal,sizeof(signal));
	}
	else if (pressed){
		pressed = false;
		SendInput(1,&releaseSignal,sizeof(releaseSignal));
		return 2;
	}
	else{
		return 0;
	}
}
