#pragma once
#include "stdafx.h"

class GameInput
{
protected:
	int id;
public:
	GameInput();
	~GameInput(void);

	virtual int IsPressed(XINPUT_GAMEPAD gamepad) = 0;
};

