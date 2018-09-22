#pragma once

#include "Maze.h"
#include "IMap.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class MazeMap : public IMap
{
#pragma region Parameters
	const float DEBUG_BLOCK_SIZE = 600.f;
	const float DEBUG_WALL_THICKNESS = 40.f;
	const sf::Color DEBUG_BLOCK_COLOR = sf::Color::White;
	const sf::Color DEBUG_WALL_COLOR = sf::Color::Black;
#pragma endregion

#pragma region Concept
	sf::RectangleShape _cellShape;
	sf::RectangleShape _wallLeftShape;
	sf::RectangleShape _wallRightShape;
	sf::RectangleShape _wallTopShape;
	sf::RectangleShape _wallBottomShape;

	std::vector<sf::RectangleShape*> _shapes;		// shape references array, for easier handling
#pragma endregion

	const Maze * _maze;
	const sf::Vector2f *_playerPosition;

	sf::Vector2u _currentCell;
public:
	MazeMap(const Maze * maze, const sf::Vector2f * playerPosition);
	virtual ~MazeMap() override;

	void update(float _dt) override;
	void draw() override;

private:
	void initMap();
	void drawCellAtPosition(const sf::Vector2f & pos, const sf::Color & color);
};

