#include "StdAfx.h"
#include "MouseMapping.h"

MouseMapping::MouseMapping(){}
MouseMapping::MouseMapping(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, DWORD flags,DWORD releaseFlags, int x, int y):
	GameInput(PollFunction, controllerInput,flags,releaseFlags,x,y) {

	cyclesHeld = 0;
	baseDy = y;
	baseDx = x;
}


MouseMapping::~MouseMapping(void)
{
}

void MouseMapping::Poll(XINPUT_GAMEPAD gamepad){
	if ( (IsPressed)(gamepad, &id)){
		// to trigger only on the first press, add: && (!pressed)
		// that does disable the ability to hold a button down though
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
	//if the button is not being held, but pressed is true, it indicates that but button was just released
	else if (pressed){
		pressed = false;
		GenerateReleaseSignal();
		signal.mi.dy = baseDy;
		signal.mi.dx = baseDx;
		cyclesHeld = 0;
	}
}