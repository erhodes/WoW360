#pragma once
#include "stdafx.h"

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
	GameInput(bool (*f)(XINPUT_GAMEPAD, void*), INPUT s, INPUT rs, int x);
	GameInput(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, BYTE keyboardOutput);
	GameInput(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, DWORD flags,DWORD releaseFlags, int x, int y);
	~GameInput(void);

	
	void Poll(XINPUT_GAMEPAD gamepad);
};

