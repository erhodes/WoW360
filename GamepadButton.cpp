#include "StdAfx.h"
#include "GamepadButton.h"



GamepadButton::GamepadButton(){}

GamepadButton::GamepadButton(int x)
{
	id = x;
	pressed = false;
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
	}
}


GamepadButton::~GamepadButton(void)
{
}

//returns 0 if unpressed, 1 if pressed, 2 if released
int GamepadButton::IsPressed(XINPUT_GAMEPAD gamepad){
	if ( (gamepad.wButtons & id) && (pressed == false)){
		// to trigger only on the first press, add: 
		pressed = true;
		return 1;
	}
	else if (pressed){
		pressed = false;
		return 2;
	}
	else{
		return 0;
	}
}
