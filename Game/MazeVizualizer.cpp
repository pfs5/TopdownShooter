#include "MazeVizualizer.h"
#include "Display.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include "Rendering.h"


namespace sf {
	class RectangleShape;
}

MazeVizualizer::MazeVizualizer(const Maze &maze, float cellSize, float wallThickness) :
	_maze {maze},
	_cellSize {cellSize}
{
	// Initialize visuals
	_cellShape.setSize(sf::Vector2f{cellSize, cellSize});
	_cellShape.setFillColor(sf::Color{ 200, 200, 200 });
	_cellShape.setOutlineColor(sf::Color::Transparent);
	_cellShape.setOrigin(_cellShape.getSize() / 2.f);

	_wallLeftShape.setSize(sf::Vector2f{ wallThickness, cellSize });
	_wallLeftShape.setFillColor(sf::Color{ 100, 100, 100 });
	_wallLeftShape.setOutlineColor(sf::Color::Transparent);
	_wallLeftShape.setOrigin(_cellShape.getSize() / 2.f);

	_wallRightShape.setSize(sf::Vector2f{ wallThickness, cellSize });
	_wallRightShape.setFillColor(sf::Color{ 100, 100, 100 });
	_wallRightShape.setOutlineColor(sf::Color::Transparent);
	_wallRightShape.setOrigin(-cellSize / 2.f + wallThickness, cellSize / 2.f);

	_wallTopShape.setSize(sf::Vector2f{ cellSize, wallThickness});
	_wallTopShape.setFillColor(sf::Color{ 100, 100, 100 });
	_wallTopShape.setOutlineColor(sf::Color::Transparent);
	_wallTopShape.setOrigin(_cellShape.getSize() / 2.f);

	_wallBottomShape.setSize(sf::Vector2f{ cellSize, wallThickness});
	_wallBottomShape.setFillColor(sf::Color{ 100, 100, 100 });
	_wallBottomShape.setOutlineColor(sf::Color::Transparent);
	_wallBottomShape.setOrigin(cellSize / 2.f, -cellSize / 2.f + wallThickness);

	_shapes = std::vector<sf::RectangleShape*> {
		&_cellShape,
		&_wallLeftShape,
		&_wallRightShape,
		&_wallTopShape,
		&_wallBottomShape
	};
}


MazeVizualizer::~MazeVizualizer()
{
}

void MazeVizualizer::update(float _dt)
{
}

void MazeVizualizer::draw()
{
	const auto &nodes = _maze.getNodes();

	for (int y = 0; y < _maze.getRows(); ++y)
	{
		for (int x = 0; x < _maze.getCols(); ++x)
		{
			const sf::Vector2f nodePos{ x * (_cellSize + 0.f), y * (_cellSize + 0.f)};	// TODO remove spacing
			for (const auto &shape : _shapes) { shape->setPosition(nodePos + getLocalPosition()); }
			
			const auto &node = nodes[y][x];
			
			// Draw required shapes
			Rendering::draw(_cellShape);
			if (!node->left) Rendering::draw(_wallLeftShape);
			if (!node->right) Rendering::draw(_wallRightShape);
			if (!node->top) Rendering::draw(_wallTopShape);
			if (!node->bottom) Rendering::draw(_wallBottomShape);
		}
	}
}

void MazeVizualizer::onCollision(Collider* _this, Collider* _other)
{
}

GameObject* MazeVizualizer::clone()
{
	return nullptr;
}

void MazeVizualizer::setLocalPosition(const sf::Vector2f &_pos)
{
	GameObject::setLocalPosition(_pos);
}