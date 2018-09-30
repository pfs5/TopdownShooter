#include "SceneJosipTest.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Camera.h"
#include "PrototypeMap2.h"
#include "BoxCharacter.h"

void SceneJosipTest::InitState(PlayState & playState)
{
	// Player one
	auto mainChar = new MainCharacter();
	mainChar->setLocalPosition(sf::Vector2f{ 2000.f, 1000.f });
	mainChar->getRigidBody()->setMass(1.f);
	playState.addGameObjectToState(mainChar, 1);

	// Box1
	auto box1 = new Enemy(sf::Color(0, 255, 0));
	box1->setLocalPosition(sf::Vector2f{ 2000.f, 1100.f });
	box1->getRigidBody()->setMass(1.f);
	playState.addGameObjectToState(box1, 1);

	// Box2
	auto box2 = new Enemy(sf::Color(0, 0, 255));
	box2->setLocalPosition(sf::Vector2f{ 2000.f, 1200.f });
	box2->getRigidBody()->setMass(10.f);
	playState.addGameObjectToState(box2, 1);

	// Box3
	auto box3 = new Enemy();
	box3->setLocalPosition(sf::Vector2f{ 2000.f, 1300.f });
	box3->getRigidBody()->setMass(20.f);
	playState.addGameObjectToState(box3, 1);

	// Camera
	auto camera = new Camera(mainChar);
	playState.addGameObjectToState(camera, 1);

	// Map
	playState._map = std::make_unique<PrototypeMap2>(1);
}
