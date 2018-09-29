#pragma once
#include "GameState.h"
#include "PhysicsEngine.h"
#include "IMap.h"

class PlayState : public GameState {
	// Scenes
	friend class SceneJosipTest;
	friend class ScenePatrikTest;

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
	void addGameObjectToState(GameObject* gameObject, unsigned int layer = 0);

private:
	std::vector<std::vector<GameObject*>> m_gameObjects;
	std::shared_ptr<IMap> m_map;
};
