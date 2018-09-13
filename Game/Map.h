#pragma once
#include "GameObject.h"
#include "Maze.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Map : public GameObject
{
#pragma region Parameters
	const float DEBUG_BLOCK_SIZE = 500.f;
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
	Map(const Maze * maze, const sf::Vector2f * playerPosition );
	~Map();
	
	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setPosition(const sf::Vector2f &pos) override;

private:
	void initMap();
	void drawCellAtPosition(const sf::Vector2f & pos, const sf::Color & color);
};

