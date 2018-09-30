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
	addEnemy(playState, sf::Vector2f{ 2300.f, 1100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 2400.f, 1100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 2500.f, 1100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 2600.f, 1100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 2700.f, 1100.f }, mainChar);

	addEnemy(playState, sf::Vector2f{ 3800.f, 1100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 3800.f, 1200.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 3800.f, 1300.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 3800.f, 1400.f }, mainChar);

	addEnemy(playState, sf::Vector2f{ 4000.f, 1100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4000.f, 1200.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4000.f, 1300.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4000.f, 1400.f }, mainChar);

	addEnemy(playState, sf::Vector2f{ 4200.f, 1100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4200.f, 1200.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4200.f, 1300.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4200.f, 1400.f }, mainChar);


	addEnemy(playState, sf::Vector2f{ 3800.f, 2100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 3800.f, 2200.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 3800.f, 2300.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 3800.f, 2400.f }, mainChar);

	addEnemy(playState, sf::Vector2f{ 4000.f, 2100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4000.f, 2200.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4000.f, 2300.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4000.f, 2400.f }, mainChar);

	addEnemy(playState, sf::Vector2f{ 4200.f, 2100.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4200.f, 2200.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4200.f, 2300.f }, mainChar);
	addEnemy(playState, sf::Vector2f{ 4200.f, 2400.f }, mainChar);

	// Camera
	auto camera = new Camera(mainChar);
	playState.addGameObjectToState(camera, 1);

	// Map
	playState._map = std::make_unique<PrototypeMap2>(1);
}

void ScenePatrikRaycastTest::addEnemy(PlayState &playState, sf::Vector2f pos, MainCharacter* mainChar) const
{
	auto enemy = new Enemy(mainChar);
	enemy->setLocalPosition(pos);
	playState.addGameObjectToState(enemy);
}