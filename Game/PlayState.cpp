#include "PlayState.h"
#include "BoxCharacter.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "RandomMazeGenerator.h"
#include "MazeVizualizer.h"
#include "BacktrackerMazeGenerator.h"

PlayState::PlayState() {
	// ### Game objects setup ###
	for (int i = 0; i < GameStateManager::objectLayers; ++i) {
		m_gameObjects.emplace_back(std::vector<GameObject*>());
	}

	initState();
}


PlayState::~PlayState() {
	// Destroy game objects
	for (auto layer : m_gameObjects) {
		for (GameObject * g : layer) {
			delete g;
		}
	}
}

void PlayState::update(float _dt) {
	for (int i = m_gameObjects.size() - 1; i >= 0; --i) {
		for (GameObject * g : m_gameObjects[i]) {
			if (g->isActive()) {
				g->update(_dt);
			}
		}
	}

	PhysicsEngine::getInstance().update(_dt);

	// Add new objects
	GameObject * newObj = nullptr;
	for (int i = m_gameObjects.size() - 1; i >= 0; --i) {
		while (newObj = GameStateManager::popNewGameObject(i)) {
			m_gameObjects[i].push_back(newObj);
		}
	}

	// Destroy objects
	GameObject * destrObj = nullptr;
	while (destrObj = GameStateManager::popDestroyedGameObject()) {
		for (auto &layer : m_gameObjects) {
			layer.erase(std::remove(layer.begin(), layer.end(), destrObj), layer.end());
		}
		delete destrObj;
	}
}

void PlayState::draw() {
	// Objects
	for (int i = m_gameObjects.size() - 1; i > 0; --i) {
		for (GameObject * g : m_gameObjects[i]) {
			if (g->isActive()) {
				g->draw();
			}
		}
	}

	// Draw foreground object layer
	for (GameObject * g : m_gameObjects[0]) {
		if (g->isActive()) {
			g->draw();
		}
	}

	PhysicsEngine::getInstance().draw();
}

GameObject * PlayState::instantiateObject(GameObject * _gameObject) {
	GameObject * newInstance = _gameObject->clone();

	return newInstance;
}

void PlayState::destroyObject(GameObject * _gameObject) {
	_gameObject->setActive(false);
}

void PlayState::initState() {
	// INITIALIZE STATE

	// Player one
	auto boxChar1 = new BoxCharacter(BoxCharacter::PlayerOne);
	boxChar1->setPosition(sf::Vector2f{ 400.f, 500.f });
	m_gameObjects[1].push_back(boxChar1);

	RandomMazeGenerator mazeGen{ 5, 5 };
	BacktrackerMazeGenerator mazeGen2{ 10, 10 };

	Maze m = mazeGen.generateMaze();
	Maze m2 = mazeGen2.generateMaze();

	auto mazeVisualizer = new MazeVizualizer{ m2, 50.f, 5.f };
	mazeVisualizer->setPosition(sf::Vector2f{200.f, 200.f});
	m_gameObjects[1].push_back(mazeVisualizer);
}
