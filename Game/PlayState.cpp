#include "PlayState.h"
#include "BoxCharacter.h"
#include "GameStateManager.h"
#include "GamePerimeter.h"
#include "Debug.h"

PlayState::PlayState() {
	// ### Game objects setup ###
	for (int i = 0; i < GameStateManager::objectLayers; ++i) {
		m_gameObjects.push_back(std::vector<GameObject*>());
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
	// Player one
	auto boxChar1 = new BoxCharacter(BoxCharacter::PlayerOne);
	boxChar1->setPosition(sf::Vector2f{ 400.f, 500.f });
	m_gameObjects[1].push_back(boxChar1);

	// Player two
	auto boxChar2 = new BoxCharacter(BoxCharacter::PlayerTwo);
	boxChar2->setPosition(sf::Vector2f{ 700.f, 500.f });
	m_gameObjects[1].push_back(boxChar2);

	// Perimiter
	auto perimiter = new GamePerimeter();
	m_gameObjects[0].push_back(perimiter);
}
