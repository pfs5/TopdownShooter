#include "PlayState.h"

PlayState::PlayState() {
	
}


PlayState::~PlayState() {
	// Destroy game objects
	for (GameObject * g : m_gameObjects) {
		delete g;
	}
}

void PlayState::update(float _dt) {
	for (GameObject * g : m_gameObjects) {
		if (g->isActive()) {
			g->update(_dt);
		}
	}

	PhysicsEngine::getInstance().update(_dt);

}

void PlayState::draw() {
	for (GameObject * g : m_gameObjects) {
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
