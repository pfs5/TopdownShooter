#include "ScenePatrikTest.h"
#include "PrototypeMap2.h"
#include "Camera.h"
#include "Enemy.h"
#include "ParticleSystem.h"
#include "ResourceManager.h"

void ScenePatrikTest::InitState(PlayState & playState)
{
	// Player one
	auto mainChar = new MainCharacter();
	mainChar->setLocalPosition(sf::Vector2f{ 2000.f, 1000.f });
	playState.addGameObjectToState(mainChar, 1);

	// Camera
	auto camera = new Camera(mainChar);
	playState.addGameObjectToState(camera, 1);

	// Map
	playState._map = std::make_unique<PrototypeMap2>(1);

	// Testing
	/*
	auto partSys = new ParticleSystem(ResourceManager::getTextureStatic("default"), 50u, true, false);
	partSys->setLocalPosition(sf::Vector2f{ 3000.f, 1100.f });
	partSys->setInitialAcceleration(sf::Vector2f{ 0.f, 0.f });
	partSys->setInitialVelocity(sf::Vector2f{ -100.f, -100.f }, sf::Vector2f{ 100.f, 100.f });
	partSys->setLifetime(5.f);
	partSys->setSpawnRate(1.f);
	partSys->setScale(sf::Vector2f{0.2f, 0.2f});
	partSys->setAlphaInTime(new Functions::LinearFunction{ Functions::LinearFunction::twoPoints(sf::Vector2f{ 0.f, 1.f }, sf::Vector2f{ 1.f, 0.f }) });

	playState.addGameObjectToState(partSys);
	*/
	
}
