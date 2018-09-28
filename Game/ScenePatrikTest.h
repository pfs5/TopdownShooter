#pragma once
#include "IScene.h"

class ScenePatrikTest : public IScene
{
public:
	void InitState(PlayState& playState) override;
};