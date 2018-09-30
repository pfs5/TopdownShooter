#pragma once
#include "IScene.h"

class MainCharacter;

class ScenePatrikRaycastTest : IScene
{
public:
	void InitState(PlayState& playState) override;

private:
	void addEnemy(PlayState &playState, sf::Vector2f pos, MainCharacter* mainChar) const;
};
