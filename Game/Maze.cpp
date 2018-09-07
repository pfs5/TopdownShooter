#include "Maze.h"
#include <iostream>

#pragma region Maze
/**
 * \brief Generate default maze of dimensions rows x cols. By default no node has neighbours.
 * \param rows 
 * \param cols 
 */
Maze::Maze(unsigned int rows, unsigned int cols) : 
	_nodes{ rows, std::vector<Node>{cols, Node{}} },
	_rows {rows},
	_cols {cols}
{
	for (unsigned int y=0; y<rows; ++y)
	{
		for (unsigned int x=0; x<cols; ++x)
		{
			_nodes[y][x].x = x;
			_nodes[y][x].y = y;
		}
	}
}

/**
 * \brief Generate maze from given nodes
 * \param nodes 
 */
Maze::Maze(const std::vector<std::vector<Node>> &nodes) :
	_nodes {nodes},
	_rows {nodes.size()}
{
	_cols = _rows > 0 ? nodes[0].size() : 0;
}


Maze::~Maze()
{
}

void Maze::printMaze() const
{
	for (int y = 0; y<_rows; ++y)
	{
		for (int x = 0; x<_cols; ++x)
		{
			auto node = _nodes[y][x];
			std::cout << node.left << " " << node.right << " " << node.top << " " << node.bottom << " . ";
		}

		std::cout << std::endl;
	}
}

#pragma endregion Maze

#pragma region Node

Node::Node() :
	visited{false},
	left{nullptr},
	right{nullptr},
	top{nullptr},
	bottom{nullptr}
{
}

const std::vector<Node*>& Node::getNeighbours() const
{
	// Late initialization
	if (_neighbours.empty())
	{
		_neighbours.push_back(left);
		_neighbours.push_back(right);
		_neighbours.push_back(top);
		_neighbours.push_back(bottom);
	}

	return _neighbours;
}

std::ostream& operator<< (std::ostream& os, const Node &node)
{
	os << "Node = " << node.left << " " << node.right << " " << node.top << " " << node.bottom << " # " << node.visited;
	return os;
}
#pragma endregion
