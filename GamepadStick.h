#pragma once
class GamepadStick
{
protected:
	static float LX_DEADZONE, RX_DEADZONE, LY_DEADZONE, RY_DEADZONE;
	int type;
	bool pressedLeft, pressedRight,pressedForward,pressedBackward;
	void DirectionHelper(char s, float dir, float deadzone, bool* pressed);
public:
	static int LEFT_STICK;
	static int RIGHT_STICK;
	GamepadStick(int x);
	~GamepadStick(void);

	int IsPressed(XINPUT_GAMEPAD gamepad);
};

