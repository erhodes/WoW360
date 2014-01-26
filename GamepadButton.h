#pragma once
#include "gameinput.h"

class GamepadButton :
	public GameInput
{
protected:
	int id;
	bool pressed;
public:
	GamepadButton(char s);
	~GamepadButton(void);

	int IsPressed(XINPUT_GAMEPAD gamepad);

};

