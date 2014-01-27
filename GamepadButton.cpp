#include "StdAfx.h"
#include "GamepadButton.h"


BYTE GamepadButton::TRIGGER_THRESHOLD =150;

GamepadButton::GamepadButton(){}

GamepadButton::GamepadButton(int x)
{
	id = x;
	pressed = false;
	Pressed = &GamepadButton::PressedButton;
	switch (x){
		case XINPUT_GAMEPAD_A: virtualKey = '1'; break;
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
		return 1;
	}
	else if (pressed){
		pressed = false;
		cout << "releasing button" << endl;
		return 2;
	}
	else{
		return 0;
	}
}
