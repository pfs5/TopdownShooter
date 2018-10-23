#include "ScenePatrikTest.h"
#include "PrototypeMap2.h"
#include "Camera.h"
#include "Enemy.h"
#include "ParticleSystem.h"
#include "ResourceManager.h"
#include "Maze.h"
#include "BacktrackerMazeGenerator.h"
#include "GeneratedPrototypeMap.h"
#include "Rendering.h"
#include "PlayerCameraController.h"
#include "BoxObject.h"
#include "EnemySpawnManager.h"
#include "AnimationTesterObject.h"

void ScenePatrikTest::InitState(PlayState & playState)
{
	// Player one
	auto mainChar = new MainCharacter();
	mainChar->setLocalPosition(sf::Vector2f{ 0.f, 0.f });
	//playState.addGameObjectToState(mainChar, 1);

	//// Boxes
	//auto box1 = new BoxObject{ sf::Vector2f{100.f, 100.f}, 100 };
	//box1->setLocalPosition(sf::Vector2f{ 500.f, 500.f });
	//playState.addGameObjectToState(box1);

	// Cameras
	Camera* mainCamera = Rendering::getCameras()[0];
	sf::View defView = Display::getWindow().getDefaultView();
	defView.setViewport(sf::FloatRect{ 0.f, 0.f, 1.f, 1.f });
	mainCamera->setView(defView);

	Camera* minimapCamera = Rendering::createCamera();
	sf::View minimapView = Display::getWindow().getDefaultView();
	minimapView.zoom(10.f);
	minimapView.setViewport(sf::FloatRect{ 0.75f, 0.f, 0.25f, 0.25f });
	minimapCamera->setView(minimapView);
	minimapCamera->setColorTint(sf::Color{ 200, 200, 200, 200 });

	auto cameraCtrl = new PlayerCameraController{ mainChar, mainCamera };
	playState.addGameObjectToState(cameraCtrl);

	// Map
	Maze* mapMaze = BacktrackerMazeGenerator{ 3, 3 }.generateMaze();
	playState._map = std::make_unique<GeneratedPrototypeMap>(mapMaze);

	// Animation testing
	auto testObj = new AnimationTesterObject{};
	playState.addGameObjectToState(testObj);

	//// Managers
	//auto enemySpawnManager = new EnemySpawnManager(new Enemy{mainChar});
	//enemySpawnManager->setSpawnRate(1.f);
	//enemySpawnManager->setSpawnPositions(
	//{
	//	sf::Vector2f{450.f,  350.f},
	//	sf::Vector2f{2450.f, 350.f},
	//	sf::Vector2f{4450.f, 350.f},

	//	sf::Vector2f{ 450.f,  1350.f },
	//	sf::Vector2f{ 2450.f, 1350.f },
	//	sf::Vector2f{ 4450.f, 1350.f },

	//	sf::Vector2f{ 450.f,  2350.f },
	//	sf::Vector2f{ 2450.f, 2350.f },
	//	sf::Vector2f{ 4450.f, 2350.f }
	//});
	//playState.addGameObjectToState(enemySpawnManager);

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
