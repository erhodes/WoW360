#pragma once
#include "gameinput.h"

class GamepadButton :
	public GameInput
{
protected:
	bool pressed;
public:
	GamepadButton();
	GamepadButton(int x);
	~GamepadButton(void);

	int IsPressed(XINPUT_GAMEPAD gamepad);

};

