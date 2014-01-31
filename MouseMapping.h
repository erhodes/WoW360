#pragma once
#include "gameinput.h"
class MouseMapping :
	public GameInput
{
protected:
	int cyclesHeld;
	long baseDy,baseDx;
	LONG* speed;
	static const int maxCyclesHeld = 30;
	static const int cursorAcceleration = 2;
public:
	MouseMapping();
	MouseMapping(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, DWORD flags,DWORD releaseFlags, int x, int y);
	~MouseMapping(void);

	void Poll(XINPUT_GAMEPAD gamepad);
};

