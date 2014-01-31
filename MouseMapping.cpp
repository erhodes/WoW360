/*
 MouseMapping.cpp
 Written by Eric Rhodes

 See MouseMapping.h for details.

*/

#include "StdAfx.h"
#include "MouseMapping.h"

MouseMapping::MouseMapping(){}
MouseMapping::MouseMapping(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, DWORD flags,DWORD releaseFlags, int x, int y):
	GameInput(PollFunction, controllerInput,flags,releaseFlags,x,y) {

	cyclesHeld = 0;
	//original plan was to have a pointer to the specific delta variable that would change.
	//this proved unworkable as the location of the signal struct moved after the constructor finished, for some reason
	//TODO: reimplement the speed pointer if you ever figure out what the issue was
	baseDy = y;
	baseDx = x;
}


MouseMapping::~MouseMapping(void)
{
}

void MouseMapping::Poll(XINPUT_GAMEPAD gamepad){
	if ( (IsPressed)(gamepad, &id)){
		pressed = true;
		GenerateSignal();
		cyclesHeld++;
		if (cyclesHeld > maxCyclesHeld){
			cyclesHeld = 0;
			if (signal.mi.dy > 0){ signal.mi.dy+=cursorAcceleration;
			}else if (signal.mi.dy < 0) { signal.mi.dy-=cursorAcceleration; }
			if (signal.mi.dx > 0){ signal.mi.dx+=cursorAcceleration;
			}else if (signal.mi.dx < 0) { signal.mi.dx-=cursorAcceleration; }

		}
	}
	else if (pressed){
		pressed = false;
		GenerateReleaseSignal();
		//reset the speed and the duration held
		signal.mi.dy = baseDy;
		signal.mi.dx = baseDx;
		cyclesHeld = 0;
	}
}