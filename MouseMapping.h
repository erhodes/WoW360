#pragma once
#include "gameinput.h"
class MouseMapping :
	public GameInput
{
protected:
	int cyclesHeld;
	long baseSpeed;
	long* speed;
	static const int maxCyclesHeld = 40;
public:
	MouseMapping(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, DWORD flags,DWORD releaseFlags, int x, int y);
	~MouseMapping(void);

	void Poll(XINPUT_GAMEPAD gamepad);
};

