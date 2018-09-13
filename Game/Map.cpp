#include "Map.h"
#include <SFML/Graphics/Color.hpp>
#include "Display.h"
#include "VectorOperations.h"
#include "Debug.h"

Map::Map(const Maze *maze, const sf::Vector2f * playerPosition) :
	_maze{ maze },
	_playerPosition{playerPosition},
	_currentCell{0u, 0u}
{
	initMap();

	m_position = sf::Vector2f{ 0.f, 0.f };

	for (unsigned int y = 0; y<_maze->getRows(); ++y)
	{
		for (unsigned int x = 0; x<_maze->getCols(); ++x)
		{
			std::cout << &_maze->getNodes()[y][x] << std::endl;
		}
	}
}


Map::~Map()
{
}

template <typename T>
float clamp(const T value, const T min, const T max)
{
	return std::min(std::max(value, min), max);
}

void Map::update(float _dt)
{
	// Calculate current cell
	_currentCell.x = clamp(static_cast<unsigned int>(floorf(((*_playerPosition).x + DEBUG_BLOCK_SIZE / 2.f) / DEBUG_BLOCK_SIZE)), 0u, _maze->getCols() - 1u);
	_currentCell.y = clamp(static_cast<unsigned int>(floorf(((*_playerPosition).y + DEBUG_BLOCK_SIZE / 2.f) / DEBUG_BLOCK_SIZE)), 0u, _maze->getRows() - 1u);

}
void Map::draw()
{
	const auto &nodes = _maze->getNodes();
	const auto &currentNode = nodes[_currentCell.y][_currentCell.x];

	// -- Draw cells --
	drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x, _currentCell.y }) * DEBUG_BLOCK_SIZE, DEBUG_BLOCK_COLOR); // middle cell

	// neighbouring cells
	if (currentNode->left) { drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x - 1u, _currentCell.y }) * DEBUG_BLOCK_SIZE, DEBUG_BLOCK_COLOR); }
	if (currentNode->right) { drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x + 1u, _currentCell.y }) * DEBUG_BLOCK_SIZE, DEBUG_BLOCK_COLOR); }
	if (currentNode->top) { drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x, _currentCell.y - 1u}) * DEBUG_BLOCK_SIZE, DEBUG_BLOCK_COLOR); }
	if (currentNode->bottom) { drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x, _currentCell.y + 1u}) * DEBUG_BLOCK_SIZE, DEBUG_BLOCK_COLOR); }

	// corner cells
	//if ((currentNode.left && currentNode.left->top) || (currentNode.top && currentNode.top->left))
	//{
	//	float distance = VectorOperations::distance(VectorOperations::utof(sf::Vector2u{ _currentCell.x - 1u, _currentCell.y - 1u }) * DEBUG_BLOCK_SIZE, *_playerPosition);
	//	float alpha = 1.f - clamp(distance / (2.f * DEBUG_BLOCK_SIZE), 0.f, 1.f);

	//	drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x - 1u, _currentCell.y - 1u }) * DEBUG_BLOCK_SIZE, sf::Color{255, 255, 255, static_cast<sf::Uint8>(alpha * 255)});
	//}

	//std::cout << currentNode << std::endl;

	float distanceX_1 = (currentNode->left && currentNode->left->top) ? abs(static_cast<float>(currentNode->left->x) * DEBUG_BLOCK_SIZE - _playerPosition->x) : std::numeric_limits<float>::max();
	float distanceY_1 = (currentNode->top && currentNode->top->left) ? abs(static_cast<float>(currentNode->top->y) - _playerPosition->y) : std::numeric_limits<float>::max();
	float distance_1 = std::min(distanceX_1, distanceY_1);
	float alpha_1 = clamp(1.5f - distance_1 / DEBUG_BLOCK_SIZE, 0.f, 1.f);
	drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x - 1u, _currentCell.y - 1u }) * DEBUG_BLOCK_SIZE, sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha_1 * 255) });

	//std::cout << (currentNode.left && currentNode.left->top) << " # # " << (currentNode.top && currentNode.top->left) << std::endl;

	/*
	if ((currentNode.top && currentNode.top->right) || (currentNode.right && currentNode.right->top))
	{
		float distance = VectorOperations::distance(VectorOperations::utof(sf::Vector2u{ _currentCell.x + 1u, _currentCell.y - 1u }) * DEBUG_BLOCK_SIZE, *_playerPosition);
		float alpha = 1.f - clamp(distance / (2.f * DEBUG_BLOCK_SIZE), 0.f, 1.f);

		drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x + 1u, _currentCell.y - 1u }) * DEBUG_BLOCK_SIZE, sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha * 255) });
	}

	if ((currentNode.right && currentNode.right->bottom) || (currentNode.bottom && currentNode.bottom->right))
	{
		float distance = VectorOperations::distance(VectorOperations::utof(sf::Vector2u{ _currentCell.x + 1u, _currentCell.y + 1u }) * DEBUG_BLOCK_SIZE, *_playerPosition);
		float alpha = 1.f - clamp(distance / (2.f * DEBUG_BLOCK_SIZE), 0.f, 1.f);

		drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x + 1u, _currentCell.y + 1u }) * DEBUG_BLOCK_SIZE, sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha * 255) });
	}

	if ((currentNode.bottom && currentNode.bottom->left) || (currentNode.left && currentNode.left->bottom))
	{
		float distance = VectorOperations::distance(VectorOperations::utof(sf::Vector2u{ _currentCell.x - 1u, _currentCell.y + 1u }) * DEBUG_BLOCK_SIZE, *_playerPosition);
		float alpha = 1.f - clamp(distance / (2.f * DEBUG_BLOCK_SIZE), 0.f, 1.f);

		drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x - 1u, _currentCell.y + 1u }) * DEBUG_BLOCK_SIZE, sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha * 255) });
	}
	*/
}

void Map::onCollision(Collider * _this, Collider * _other)
{
}

GameObject* Map::clone()
{
	return new Map(_maze, _playerPosition);
}

void Map::setPosition(const sf::Vector2f & pos)
{
	m_position = pos;
}

void Map::initMap()
{
	// Initialize visuals
	_cellShape.setSize(sf::Vector2f{ DEBUG_BLOCK_SIZE, DEBUG_BLOCK_SIZE });
	_cellShape.setFillColor(DEBUG_BLOCK_COLOR);
	_cellShape.setOutlineColor(sf::Color{50, 50, 50, 0});
	_cellShape.setOutlineThickness(-10.f);
	_cellShape.setOrigin(_cellShape.getSize() / 2.f);

	_wallLeftShape.setSize(sf::Vector2f{ DEBUG_WALL_THICKNESS, DEBUG_BLOCK_SIZE });
	_wallLeftShape.setFillColor(DEBUG_WALL_COLOR);
	_wallLeftShape.setOutlineColor(sf::Color::Transparent);
	_wallLeftShape.setOrigin(_cellShape.getSize() / 2.f);

	_wallRightShape.setSize(sf::Vector2f{ DEBUG_WALL_THICKNESS, DEBUG_BLOCK_SIZE });
	_wallRightShape.setFillColor(DEBUG_WALL_COLOR);
	_wallRightShape.setOutlineColor(sf::Color::Transparent);
	_wallRightShape.setOrigin(-DEBUG_BLOCK_SIZE / 2.f + DEBUG_WALL_THICKNESS, DEBUG_BLOCK_SIZE / 2.f);

	_wallTopShape.setSize(sf::Vector2f{ DEBUG_BLOCK_SIZE, DEBUG_WALL_THICKNESS });
	_wallTopShape.setFillColor(DEBUG_WALL_COLOR);
	_wallTopShape.setOutlineColor(sf::Color::Transparent);
	_wallTopShape.setOrigin(_cellShape.getSize() / 2.f);

	_wallBottomShape.setSize(sf::Vector2f{ DEBUG_BLOCK_SIZE, DEBUG_WALL_THICKNESS });
	_wallBottomShape.setFillColor(DEBUG_WALL_COLOR);
	_wallBottomShape.setOutlineColor(sf::Color::Transparent);
	_wallBottomShape.setOrigin(DEBUG_BLOCK_SIZE / 2.f, -DEBUG_BLOCK_SIZE / 2.f + DEBUG_WALL_THICKNESS);

	_shapes = std::vector<sf::RectangleShape*>{
		&_cellShape,
		&_wallLeftShape,
		&_wallRightShape,
		&_wallTopShape,
		&_wallBottomShape
	};
}

void Map::drawCellAtPosition(const sf::Vector2f & pos, const sf::Color & color)
{
	_cellShape.setPosition(pos);
	_cellShape.setFillColor(color);
	Display::draw(_cellShape);
}
