#include "SceneJosipTest.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Camera.h"
#include "PrototypeMap2.h"

void SceneJosipTest::InitState(PlayState & playState)
{
	// Player one
	auto mainChar = new MainCharacter();
	mainChar->setLocalPosition(sf::Vector2f{ 2000.f, 1000.f });
	playState.addGameObjectToState(mainChar, 1);

	// Player one
	auto enemy = new Enemy(mainChar);
	enemy->setLocalPosition(sf::Vector2f{ 2300.f, 1000.f });
	playState.addGameObjectToState(enemy, 1);

	// Camera
	//auto camera = new Camera(mainChar);
	//playState.addGameObjectToState(camera, 1);

	// Map
	playState._map = std::make_unique<PrototypeMap2>(1);
}
