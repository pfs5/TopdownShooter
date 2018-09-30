#pragma once
#include "PlayState.h"

class IScene
{
public:
	virtual void InitState(PlayState &playState) = 0;
};
