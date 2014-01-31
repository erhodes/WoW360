#pragma once
#include "stdafx.h"

const int LEFT = 0;
const int RIGHT = 1;
const int LT_LEFT = 2;
const int LT_RIGHT = 3;
const int LT_UP = 4;
const int LT_DOWN = 5;
const int RT_LEFT = 6;
const int RT_RIGHT = 7;
const int RT_UP = 8;
const int RT_DOWN = 9;
const int scrollSpeed = 8;

class GameInput
{
protected:
	INPUT signal, releaseSignal;
	int id;
	bool pressed;

	bool (*IsPressed)(XINPUT_GAMEPAD, void* data);
	void GenerateSignal();
	void GenerateReleaseSignal();
public:
	GameInput();
	GameInput(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, BYTE keyboardOutput);
	GameInput(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, DWORD flags,DWORD releaseFlags, int x, int y);
	~GameInput(void);

	void Poll(XINPUT_GAMEPAD gamepad);

	static bool PressedButton(XINPUT_GAMEPAD, void* x);
	static bool PressedTrigger(XINPUT_GAMEPAD, void* x);
	static bool PressedThumbstick(XINPUT_GAMEPAD gamepad, void* data);
	
};
 