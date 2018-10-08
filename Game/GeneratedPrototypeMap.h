#pragma once
#include "IMap.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Maze.h"
#include <SFML/Graphics/Sprite.hpp>

class GeneratedPrototypeMap : public IMap
{
public:
	GeneratedPrototypeMap(const Maze * maze);

	void update(float dt) override;
	void draw() override;

private:
	// Constants
	const sf::Vector2f ISLAND_SIZE = sf::Vector2f{ 998.f, 798.f };
	const float BRIDGE_HORIZONTAL_LENGTH = 918.f;
	const float BRIDGE_VERTICAL_LENGTH = 198.f;

	const std::string TEXTURE_BACKGROUND = "prototype-map-1-bg";
	const std::string TEXTURE_ISLAND = "prototype-map-1-island";
	const std::string TEXTURE_BRIDGE_HORIZONTAL = "prototype-map-1-bridge-horizontal";
	const std::string TEXTURE_BRIDGE_VERTICAL = "prototype-map-1-bridge-vertical";

	const Maze* _maze;

	// Visuals
	sf::Sprite _backgroundSprite;
	sf::Sprite _islandSprite;
	sf::Sprite _bridgeHorizontalSprite;
	sf::Sprite _bridgeVerticalSprite;

	sf::RectangleShape _debugIslandShape;
	sf::RectangleShape _debugBridgeHorizontalShape;
	sf::RectangleShape _debugBridgeVerticalShape;
};
