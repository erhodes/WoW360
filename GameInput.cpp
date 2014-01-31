#include "StdAfx.h"
#include "GameInput.h"

GameInput::GameInput() {}

//constructor for a mapping to a keyboard button
GameInput::GameInput(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, BYTE keyboardOutput) {
	pressed = false;
	IsPressed = PollFunction;
	id = controllerInput;
	if ((keyboardOutput >= 97) && (keyboardOutput <= 122))
		keyboardOutput = (UCHAR)VkKeyScan(keyboardOutput);
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
	pressed = false;
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

bool GameInput::PressedButton(XINPUT_GAMEPAD gamepad, void* x){
	int id = *((int* )x);
	return (gamepad.wButtons & id);
}

bool GameInput::PressedTrigger(XINPUT_GAMEPAD gamepad, void* x){
	BYTE magnitude = 0;
	int id = *((int* )x);
	//get the magnitude of the appropriate trigger
	if (id == LEFT){
		magnitude = gamepad.bLeftTrigger;
	} else if (id == RIGHT){
		magnitude = gamepad.bRightTrigger;
	}
	else { cout << "that aint right" << endl; }
	//determine if the magnitude is over the deadzone
	if (magnitude > 50){
		return true;
	}else { return false;}
}

bool GameInput::PressedThumbstick(XINPUT_GAMEPAD gamepad, void* data){
	int id = *(int*)(data);
	short deadzone = 10000;
	switch (id){
		case LT_UP: return (gamepad.sThumbLY > deadzone); break;
		case LT_DOWN: return (-gamepad.sThumbLY > deadzone); break;
		case LT_RIGHT: return (gamepad.sThumbLX > deadzone); break;
		case LT_LEFT: return (-gamepad.sThumbLX > deadzone); break;
		case RT_UP: return (gamepad.sThumbRY > deadzone); break;
		case RT_DOWN: return (-gamepad.sThumbRY > deadzone); break;
		case RT_RIGHT: return (gamepad.sThumbRX > deadzone); break;
		case RT_LEFT: return (-gamepad.sThumbRX > deadzone); break;
	}
	return false;
}