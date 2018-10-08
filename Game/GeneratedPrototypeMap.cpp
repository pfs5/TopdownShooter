#include "GeneratedPrototypeMap.h"
#include "Display.h"
#include "ResourceManager.h"
#include "VectorOperations.h"
#include "Rendering.h"

GeneratedPrototypeMap::GeneratedPrototypeMap(const Maze * maze) :
	_maze{maze}
{

	sf::Texture* bgTex = ResourceManager::getTextureStatic(TEXTURE_BACKGROUND);
	bgTex->setRepeated(true);
	_backgroundSprite.setTexture(*bgTex);

	int mapWidth = static_cast<int>(_maze->getCols() * (ISLAND_SIZE.x + BRIDGE_HORIZONTAL_LENGTH)) + (Display::getWindow().getSize().x * 2);
	int mapHeight = static_cast<int>(_maze->getRows() * (ISLAND_SIZE.y + BRIDGE_VERTICAL_LENGTH)) + (Display::getWindow().getSize().y * 2);
	_backgroundSprite.setTextureRect(sf::IntRect{ 0, 0, mapWidth, mapHeight });
	_backgroundSprite.setPosition(-VectorOperations::utof(Display::getWindow().getSize()));

	_islandSprite.setTexture(*ResourceManager::getTextureStatic(TEXTURE_ISLAND));
	_bridgeHorizontalSprite.setTexture(*ResourceManager::getTextureStatic(TEXTURE_BRIDGE_HORIZONTAL));
	_bridgeVerticalSprite.setTexture(*ResourceManager::getTextureStatic(TEXTURE_BRIDGE_VERTICAL));
}

void GeneratedPrototypeMap::update(float dt)
{
}

void GeneratedPrototypeMap::draw()
{
	// Draw map
	Rendering::draw(_backgroundSprite);

	auto &nodes = _maze->getNodes();
	for (unsigned int y = 0; y<_maze->getRows(); ++y)
	{
		for (unsigned int x = 0; x<_maze->getCols(); ++x)
		{
			// Draw island
			sf::Vector2f islandPos{ x * (ISLAND_SIZE.x + BRIDGE_HORIZONTAL_LENGTH), y * (ISLAND_SIZE.y + BRIDGE_VERTICAL_LENGTH) };
			_islandSprite.setPosition(islandPos);
			Rendering::draw(_islandSprite);

			// Draw bridges
			if (nodes[y][x]->right != nullptr)
			{
				sf::Vector2f bridgeRightPos = islandPos + sf::Vector2f{ ISLAND_SIZE.x, 0.f };
				_bridgeHorizontalSprite.setPosition(bridgeRightPos);
				Rendering::draw(_bridgeHorizontalSprite);
			}

			if (nodes[y][x]->bottom != nullptr)
			{
				sf::Vector2f bridgeBottomPos = islandPos + sf::Vector2f{ 0.f, ISLAND_SIZE.y };
				_bridgeVerticalSprite.setPosition(bridgeBottomPos);
				Rendering::draw(_bridgeVerticalSprite);
			}
		}
	}
}
