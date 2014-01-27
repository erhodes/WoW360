#pragma once
#include "gameinput.h"

class GamepadButton :
	public GameInput
{
protected:
	static BYTE TRIGGER_THRESHOLD;
	bool pressed;
	BYTE virtualKey;
	bool (GamepadButton::*Pressed)(XINPUT_GAMEPAD);
	bool PressedButton(XINPUT_GAMEPAD);
	bool PressedTrigger(XINPUT_GAMEPAD);
public:
	static const int RIGHT_TRIGGER = 5;
	static const int LEFT_TRIGGER = 6; 

	GamepadButton();
	GamepadButton(int x);
	~GamepadButton(void);

	int IsPressed(XINPUT_GAMEPAD gamepad);
	BYTE GetSymbol() {return virtualKey; }

};

