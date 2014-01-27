#pragma once
#include "gameinput.h"
class GamepadStick :
	public GameInput
{
protected:
	static float LX_DEADZONE;
	static float LY_DEADZONE;
	bool pressedLeft, pressedRight,pressedForward,pressedBackward;
	int direction;
	void GenerateKey(BYTE vk);
	void GenerateReleaseKey(BYTE vk);
public:
	GamepadStick(int x);
	~GamepadStick(void);

	int IsPressed(XINPUT_GAMEPAD gamepad);
};

