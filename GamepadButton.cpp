#include "StdAfx.h"
#include "GamepadButton.h"


GamepadButton::GamepadButton(char s)
{
	symbol = s;
	pressed = false;
	switch (symbol){
		case 'a': id = XINPUT_GAMEPAD_A; break;
		case 'b': id = XINPUT_GAMEPAD_B; break;
		case 'x': id = XINPUT_GAMEPAD_X; break;
		case 'y': id = XINPUT_GAMEPAD_Y; break;
	}
}


GamepadButton::~GamepadButton(void)
{
}

//returns 0 if unpressed, 1 if pressed, 2 if released
int GamepadButton::IsPressed(XINPUT_GAMEPAD gamepad){
	if ( (gamepad.wButtons & XINPUT_GAMEPAD_A) ){
		// to trigger only on the first press, add: && (pressed == false)
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
