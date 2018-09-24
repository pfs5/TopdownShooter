#include "PlayState.h"
#include "BoxCharacter.h"
#include "GameStateManager.h"
#include "MazeVizualizer.h"
#include "MainCharacter.h"
#include "Camera.h"

#include "Debug.h"
#include "PrototypeMap1.h"
#include "PrototypeMap2.h"
#include "BoxShape.h"

PlayState::PlayState() {
	// ### Game objects setup ###
	for (int i = 0; i < GameStateManager::objectLayers; ++i) 
	{
		m_gameObjects.emplace_back(std::vector<GameObject*>());
	}

	initState();
}


PlayState::~PlayState() {
	// Destroy game objects
	for (auto layer : m_gameObjects) 
	{
		for (GameObject * g : layer) 
		{
			delete g;
		}
	}
}

void PlayState::update(float _dt) {
	// Map
	if (m_map != nullptr)
	{
		m_map->update(_dt);
	}

	for (int i = m_gameObjects.size() - 1; i >= 0; --i) 
	{
		for (GameObject * g : m_gameObjects[i]) 
		{
			if (g->isActive()) 
			{
				g->update(_dt);
			}
		}
	}

	PhysicsEngine::getInstance().update(_dt);

	// Add new objects
	GameObject * newObj = nullptr;
	for (int i = m_gameObjects.size() - 1; i >= 0; --i) 
	{
		while (newObj = GameStateManager::popNewGameObject(i))
		{
			m_gameObjects[i].push_back(newObj);
		}
	}

	// Destroy objects
	GameObject * destrObj = nullptr;
	while (destrObj = GameStateManager::popDestroyedGameObject()) 
	{
		for (auto &layer : m_gameObjects) 
		{
			layer.erase(std::remove(layer.begin(), layer.end(), destrObj), layer.end());
		}
		delete destrObj;
	}
}

void PlayState::draw() {
	// Map
	if (m_map != nullptr)
	{
		m_map->draw();
	}
	
	// Objects
	for (int i = m_gameObjects.size() - 1; i > 0; --i) 
	{
		for (GameObject * g : m_gameObjects[i]) 
		{
			if (g->isActive()) {
				g->draw();
			}
		}
	}

	// Draw foreground object layer
	for (GameObject * g : m_gameObjects[0]) 
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

	// Player one
	auto mainChar = new MainCharacter();
	mainChar->setLocalPosition(sf::Vector2f{ 2000.f, 1000.f });
	m_gameObjects[1].push_back(mainChar);

	// Camera
	auto camera = new Camera(mainChar);
	m_gameObjects[1].push_back(camera);

	// Map
	m_map = std::make_unique<PrototypeMap2>(1);
}
