#pragma once
#include "GameState.h"
#include "PhysicsEngine.h"
#include "IMap.h"

class PlayState : public GameState {
	// Scenes
	friend class SceneJosipTest;
	friend class ScenePatrikTest;
	friend class ScenePatrikRaycastTest;

public:
	PlayState();
	~PlayState();

	// Inherited via GameState
	virtual void update(float dt) override;
	virtual void draw() override;
	virtual GameObject * instantiateObject(GameObject * gameObject) override;
	virtual void destroyObject(GameObject * gameObject) override;

private:
	void initState();
	void addGameObjectToState(GameObject* gameObject, unsigned int layer = 0);

private:
	std::vector<std::vector<GameObject*>> _gameObjects;
	std::shared_ptr<IMap> _map;
};
