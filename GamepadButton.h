#pragma once

class GamepadButton
{
protected:
	INPUT signal, releaseSignal;
	bool pressed, simulateMouse;
	BYTE virtualKey;
	int id;
	bool (GamepadButton::*Pressed)(XINPUT_GAMEPAD);
	bool PressedButton(XINPUT_GAMEPAD);
	bool PressedTrigger(XINPUT_GAMEPAD);
public:
	static const int RIGHT_TRIGGER = 5;
	static const int LEFT_TRIGGER = 6;
	static BYTE TRIGGER_THRESHOLD;

	GamepadButton();
	GamepadButton(int x);
	~GamepadButton(void);

	int IsPressed(XINPUT_GAMEPAD gamepad);
	BYTE GetSymbol() {return virtualKey; }

};

