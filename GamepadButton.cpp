#include "StdAfx.h"
#include "GamepadButton.h"



GamepadButton::GamepadButton(){}

GamepadButton::GamepadButton(int x)
{
	id = x;
	pressed = false;
	switch (x){
		case XINPUT_GAMEPAD_A: symbol = '1'; break;
		case XINPUT_GAMEPAD_B: symbol = '2'; break;
		case XINPUT_GAMEPAD_X: symbol = '3'; break;
		case XINPUT_GAMEPAD_Y: symbol = '4'; break;
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
