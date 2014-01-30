#include "StdAfx.h"
#include "GameInput.h"

GameInput::GameInput() {}

GameInput::GameInput(bool (*f)(XINPUT_GAMEPAD, void*), INPUT s, INPUT rs, int x){
	IsPressed = f;
	signal = s;
	releaseSignal = rs;
	pressed = false;
	id = x;
	cout << "making whatever" << endl;
}
//constructor for a mapping to a keyboard button
GameInput::GameInput(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, BYTE keyboardOutput) {
	IsPressed = PollFunction;
	id = controllerInput;
	ZeroMemory(&signal,sizeof(signal));
	signal.type = INPUT_KEYBOARD;
	signal.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	signal.ki.wVk = keyboardOutput;
	ZeroMemory(&releaseSignal,sizeof(releaseSignal));
	releaseSignal.type = INPUT_KEYBOARD;
	releaseSignal.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
	releaseSignal.ki.wVk = keyboardOutput;
}

//constructor for mapping to a mouse event
GameInput::GameInput(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, DWORD flags,DWORD releaseFlags, int x, int y){
	id = controllerInput;
	IsPressed = PollFunction;
	ZeroMemory(&signal,sizeof(signal));
	signal.type = INPUT_MOUSE;
	signal.mi.dy = y;
	signal.mi.dx = x;
	signal.mi.dwFlags = flags;
	ZeroMemory(&releaseSignal,sizeof(releaseSignal));
	releaseSignal.type = INPUT_MOUSE;
	releaseSignal.mi.dy = y;
	releaseSignal.mi.dx = x;
	releaseSignal.mi.dwFlags = releaseFlags;
}


GameInput::~GameInput(void)
{
}

void GameInput::GenerateSignal(){
	SendInput(1,&signal,sizeof(signal));
}

void GameInput::GenerateReleaseSignal(){
	SendInput(1,&releaseSignal,sizeof(releaseSignal));
}

void GameInput::Poll(XINPUT_GAMEPAD gamepad){
	if ( (IsPressed)(gamepad, &id)){
		// to trigger only on the first press, add: && (!pressed)
		// that does disable the ability to hold a button down though
		pressed = true;
		//SendInput(1,&signal,sizeof(signal));
		GenerateSignal();
	}
	//if the button is not being held, but pressed is true, it indicates that but button was just released
	else if (pressed){
		pressed = false;
		//SendInput(1,&releaseSignal,sizeof(releaseSignal));
		GenerateReleaseSignal();
	}
}

