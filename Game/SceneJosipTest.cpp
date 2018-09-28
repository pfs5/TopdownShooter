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
	playState.m_gameObjects[1].push_back(mainChar);

	// Player one
	auto enemy = new Enemy(mainChar);
	enemy->setLocalPosition(sf::Vector2f{ 2300.f, 1000.f });
	playState.m_gameObjects[1].push_back(enemy);

	// Camera
	auto camera = new Camera(mainChar);
	playState.m_gameObjects[1].push_back(camera);

	// Map
	playState.m_map = std::make_unique<PrototypeMap2>(1);
}
