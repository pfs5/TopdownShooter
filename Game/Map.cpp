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
}


Map::~Map()
{
	delete _maze;
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

	// -- Neighbouring cells --
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

	// -- Corner cells --
	const float distanceX_1 = (currentNode->left && currentNode->left->top) ? abs(static_cast<float>(currentNode->left->x) * DEBUG_BLOCK_SIZE - _playerPosition->x) : std::numeric_limits<float>::max();
	const float distanceY_1 = (currentNode->top && currentNode->top->left) ? abs(static_cast<float>(currentNode->top->y) * DEBUG_BLOCK_SIZE - _playerPosition->y) : std::numeric_limits<float>::max();
	const float distance_1 = std::min(distanceX_1, distanceY_1);
	const float alpha_1 = clamp(1.5f - distance_1 / DEBUG_BLOCK_SIZE, 0.f, 1.f);
	drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x - 1u, _currentCell.y - 1u }) * DEBUG_BLOCK_SIZE, sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha_1 * 255) });

	const float distanceX_2 = (currentNode->right && currentNode->right->top) ? abs(static_cast<float>(currentNode->right->x) * DEBUG_BLOCK_SIZE - _playerPosition->x) : std::numeric_limits<float>::max();
	const float distanceY_2 = (currentNode->top && currentNode->top->right) ? abs(static_cast<float>(currentNode->top->y) * DEBUG_BLOCK_SIZE - _playerPosition->y) : std::numeric_limits<float>::max();
	const float distance_2 = std::min(distanceX_2, distanceY_2);
	const float alpha_2 = clamp(1.5f - distance_2 / DEBUG_BLOCK_SIZE, 0.f, 1.f);
	drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x + 1u, _currentCell.y - 1u }) * DEBUG_BLOCK_SIZE, sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha_2 * 255) });
	
	const float distanceX_3 = (currentNode->right && currentNode->right->bottom) ? abs(static_cast<float>(currentNode->right->x) * DEBUG_BLOCK_SIZE - _playerPosition->x) : std::numeric_limits<float>::max();
	const float distanceY_3 = (currentNode->bottom && currentNode->bottom->right) ? abs(static_cast<float>(currentNode->bottom->y) * DEBUG_BLOCK_SIZE - _playerPosition->y) : std::numeric_limits<float>::max();
	const float distance_3 = std::min(distanceX_3, distanceY_3);
	const float alpha_3 = clamp(1.5f - distance_3 / DEBUG_BLOCK_SIZE, 0.f, 1.f);
	drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x + 1u, _currentCell.y + 1u }) * DEBUG_BLOCK_SIZE, sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha_3 * 255) });
	
	const float distanceX_4 = (currentNode->left && currentNode->left->bottom) ? abs(static_cast<float>(currentNode->left->x) * DEBUG_BLOCK_SIZE - _playerPosition->x) : std::numeric_limits<float>::max();
	const float distanceY_4 = (currentNode->bottom && currentNode->bottom->left) ? abs(static_cast<float>(currentNode->bottom->y) * DEBUG_BLOCK_SIZE - _playerPosition->y) : std::numeric_limits<float>::max();
	const float distance_4 = std::min(distanceX_4, distanceY_4);
	const float alpha_4 = clamp(1.5f - distance_4 / DEBUG_BLOCK_SIZE, 0.f, 1.f);
	drawCellAtPosition(VectorOperations::utof(sf::Vector2u{ _currentCell.x - 1u, _currentCell.y + 1u }) * DEBUG_BLOCK_SIZE, sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha_4 * 255) });
	
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
