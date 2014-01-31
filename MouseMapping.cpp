#include "StdAfx.h"
#include "MouseMapping.h"


MouseMapping::MouseMapping(bool (*PollFunction)(XINPUT_GAMEPAD, void*), int controllerInput, DWORD flags,DWORD releaseFlags, int x, int y){
	pressed = false;
	id = controllerInput;
	IsPressed = PollFunction;
	ZeroMemory(&signal,sizeof(signal));
	signal.type = INPUT_MOUSE;
	signal.mi.dy = y;
	signal.mi.dx = x;
	signal.mi.dwFlags = flags;
	ZeroMemory(&releaseSignal,sizeof(releaseSignal));
	releaseSignal.type = INPUT_MOUSE;
	releaseSignal.mi.dy = 0;
	releaseSignal.mi.dx = 0;
	releaseSignal.mi.dwFlags = releaseFlags;

	cyclesHeld = 0;
	if (y > 0){
		speed = &signal.mi.dy;
	} else {
		speed = &signal.mi.dx;
	}
	baseSpeed = *speed;
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
		cout << cyclesHeld << endl;
		if (cyclesHeld > maxCyclesHeld){
			cyclesHeld = 0;
			signal.mi.dy=10;
		}
	}
	//if the button is not being held, but pressed is true, it indicates that but button was just released
	else if (pressed){
		pressed = false;
		GenerateReleaseSignal();
		signal.mi.dy=1;
	}
}