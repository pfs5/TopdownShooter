#include "PlayState.h"
#include "BoxCharacter.h"
#include "GameStateManager.h"
#include "MazeVizualizer.h"
#include "MainCharacter.h"
#include "Camera.h"
#include "Enemy.h"

#include "Debug.h"
#include "PrototypeMap1.h"
#include "PrototypeMap2.h"
#include "BoxShape.h"
#include "SceneJosipTest.h"
#include "ScenePatrikTest.h"

PlayState::PlayState() 
{
	// ### Game objects setup ###
	for (int i = 0; i < GameStateManager::objectLayers; ++i) 
	{
		_gameObjects.emplace_back(std::vector<GameObject*>());
	}

	initState();
}


PlayState::~PlayState() 
{
	// Destroy game objects
	for (auto layer : _gameObjects) 
	{
		for (GameObject * g : layer) 
		{
			delete g;
		}
	}
}

void PlayState::update(float dt) 
{
	// Map
	if (_map != nullptr)
	{
		_map->update(dt);
	}

	for (int i = _gameObjects.size() - 1; i >= 0; --i) 
	{
		for (GameObject * g : _gameObjects[i]) 
		{
			if (g->isActive()) 
			{
				g->update(dt);
			}
		}
	}

	PhysicsEngine::getInstance().update(dt);

	// Add new objects
	GameObject * newObj = nullptr;
	for (int i = _gameObjects.size() - 1; i >= 0; --i) 
	{
		while (newObj = GameStateManager::popNewGameObject(i))
		{
			_gameObjects[i].push_back(newObj);
		}
	}

	// Destroy objects
	GameObject * destrObj = nullptr;
	while (destrObj = GameStateManager::popDestroyedGameObject()) 
	{
		for (auto &layer : _gameObjects) 
		{
			layer.erase(std::remove(layer.begin(), layer.end(), destrObj), layer.end());
		}
		delete destrObj;
	}
}

void PlayState::draw() 
{
	// Map
	if (_map != nullptr)
	{
		_map->draw();
	}
	
	// Objects
	for (int i = _gameObjects.size() - 1; i > 0; --i) 
	{
		for (GameObject * g : _gameObjects[i]) 
		{
			if (g->isActive()) {
				g->draw();
			}
		}
	}

	// Draw foreground object layer
	for (GameObject * g : _gameObjects[0]) 
	{
		if (g->isActive()) 
		{
			g->draw();
		}
	}

	PhysicsEngine::getInstance().draw();
}

GameObject * PlayState::instantiateObject(GameObject * _gameObject) 
{
	GameObject * newInstance = _gameObject->clone();

	return newInstance;
}

void PlayState::destroyObject(GameObject * _gameObject) 
{
	_gameObject->setActive(false);
}

Maze * createMaze()
{
	Maze * m = new Maze{ 3, 3 };
	auto &nodes = m->getNodes();

	nodes[1][1]->top = nodes[0][1];
	nodes[1][1]->left = nodes[1][0];
	nodes[1][1]->right = nodes[1][2];
	nodes[1][1]->bottom = nodes[2][1];

	nodes[0][1]->bottom = nodes[1][1];
	nodes[1][0]->right = nodes[1][1];
	nodes[1][2]->left = nodes[1][1];
	nodes[2][1]->top = nodes[1][1];

	return m;
}

void PlayState::initState() 
{
	// INITIALIZE STATE
	ScenePatrikTest scene;
	scene.InitState(*this);
}

void PlayState::addGameObjectToState(GameObject * gameObject, unsigned int layer)
{
	while(_gameObjects.size() < layer + 1)
	{
		_gameObjects.emplace_back(std::vector<GameObject*>());
	}

	_gameObjects[layer].push_back(gameObject);
}
