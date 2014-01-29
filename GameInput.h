#pragma once
#include "stdafx.h"

class GameInput
{
	INPUT signal, releaseSignal;
	int id;
	bool pressed;

	bool (*IsPressed)(XINPUT_GAMEPAD, void* data);
	void GenerateSignal();
	void GenerateReleaseSignal();
public:
	GameInput();
	GameInput(bool (*f)(XINPUT_GAMEPAD, void*), INPUT s, INPUT rs, int x);
	~GameInput(void);

	
	void Poll(XINPUT_GAMEPAD gamepad);
};

