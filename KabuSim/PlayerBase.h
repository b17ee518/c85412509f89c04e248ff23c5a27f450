#pragma once
#include "Defines.h"

class PlayerBase
{
public:
	PlayerBase();
	~PlayerBase();

public:

protected:
	FW_SYNTHESIZE_WITHINIT(int, _initCapital, InitCapital, 0);
	FW_SYNTHESIZE_WITHINIT(int, _currentCapital, CurrentCapital, 0);
};

