#pragma once
#include "stdafx.h"

class GameInput
{
protected:
	char symbol;
	int id;
public:
	GameInput();
	~GameInput(void);

	virtual int IsPressed(XINPUT_GAMEPAD gamepad) = 0;
	char GetSymbol() { return symbol; }
};

