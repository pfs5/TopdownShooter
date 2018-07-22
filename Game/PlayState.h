#pragma once
#include "GameState.h"
#include "PhysicsEngine.h"

class PlayState : public GameState {
	std::vector<GameObject*> m_gameObjects;

public:
	PlayState();
	~PlayState();

	// Inherited via GameState
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual GameObject * instantiateObject(GameObject * _gameObject) override;
	virtual void destroyObject(GameObject * _gameObject) override;

private:
	void initState();
};