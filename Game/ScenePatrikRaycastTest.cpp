#include "ScenePatrikRaycastTest.h"
#include "PrototypeMap2.h"
#include "Camera.h"
#include "Enemy.h"

void ScenePatrikRaycastTest::InitState(PlayState & playState)
{
	// Player one
	auto mainChar = new MainCharacter();
	mainChar->setLocalPosition(sf::Vector2f{ 2000.f, 1000.f });
	playState.addGameObjectToState(mainChar, 1);

	// Enemy test
	auto enemy = new Enemy(mainChar);
	enemy->setLocalPosition(sf::Vector2f{ 2300.f, 1000.f });
	playState.addGameObjectToState(enemy, 1);

	// Camera
	auto camera = new Camera(mainChar);
	playState.addGameObjectToState(camera, 1);

	// Map
	playState._map = std::make_unique<PrototypeMap2>(1);
}
