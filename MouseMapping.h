/*
 MouseMapping.h
 Written by Eric Rhodes, January 2014

 Inerits from GameInput class. This class is for mapping to cursor input when cursor acceleration is desired.

*/

#pragma once
#include "gameinput.h"
class MouseMapping :
	public GameInput
{
protected:
	//counts the number of cycles the trigger has been held for. At a certain point, accelerate cursor speed
	int cyclesHeld;
	long baseDy,baseDx;
	static const int maxCyclesHeld = 30;
	static const int cursorAcceleration = 2;
public:
	MouseMapping();
	MouseMapping(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, DWORD flags,DWORD releaseFlags, int x, int y);
	~MouseMapping(void);

	void Poll(XINPUT_GAMEPAD gamepad);
};

