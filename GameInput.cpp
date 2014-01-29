#include "StdAfx.h"
#include "GameInput.h"

GameInput::GameInput() {}

GameInput::GameInput(bool (*f)(XINPUT_GAMEPAD, void*), INPUT s, INPUT rs, int x){
	IsPressed = f;
	signal = s;
	releaseSignal = rs;
	pressed = false;
	id = x;
}


GameInput::~GameInput(void)
{
}

void GameInput::Poll(XINPUT_GAMEPAD gamepad){
	if ( (IsPressed)(gamepad, &id)){
		// to trigger only on the first press, add: && (!pressed)
		// that does disable the ability to hold a button down though
		pressed = true;
		SendInput(1,&signal,sizeof(signal));
	}
	//if the button is not being held, but pressed is true, it indicates that but button was just released
	else if (pressed){
		pressed = false;
		SendInput(1,&releaseSignal,sizeof(releaseSignal));
	}
}

