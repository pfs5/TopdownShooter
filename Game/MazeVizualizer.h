#pragma once
#include "GameObject.h"
#include "Maze.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class MazeVizualizer : public GameObject
{
	Maze _maze;
	float _cellSize;

	// Visuals
	sf::RectangleShape _cellShape;
	sf::RectangleShape _wallLeftShape;
	sf::RectangleShape _wallRightShape;
	sf::RectangleShape _wallTopShape;
	sf::RectangleShape _wallBottomShape;

	std::vector<sf::RectangleShape*> _shapes;		// shape references array, for easier handling
public:
	MazeVizualizer(const Maze &maze, float cellSize = 50.f, float wallThickness = 5.f);
	~MazeVizualizer();

	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setLocalPosition(const sf::Vector2f &_pos) override;
};

