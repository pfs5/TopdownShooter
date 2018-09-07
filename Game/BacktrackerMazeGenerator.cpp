#include "BacktrackerMazeGenerator.h"
#include <stack>
#include "Util.h"


BacktrackerMazeGenerator::BacktrackerMazeGenerator(unsigned int rows, unsigned int cols):
	_rows {rows},
	_cols {cols}
{
}


BacktrackerMazeGenerator::~BacktrackerMazeGenerator()
{
}


/**
 * \brief Generate maze using the backtracker algorithm
 * \return 
 */
Maze BacktrackerMazeGenerator::generateMaze()
{
	Maze maze{ _rows, _cols };
	if (_rows * _cols <= 1) { return maze; }
	
	auto & nodes = maze.getNodes();

	unsigned int unvisitedNodes = _rows * _cols - 1;
	std::stack<Node*> nodeStack;
	Node * currentNode = &nodes[0][0];
	currentNode->visited = true;

	do
	{
		// -- 1. Move to new nodes --
		std::vector<Node*> neighbours;
		if (currentNode->x > 0) neighbours.push_back(&nodes[currentNode->y][currentNode->x - 1]);
		if (currentNode->y > 0) neighbours.push_back(&nodes[currentNode->y - 1][currentNode->x]);
		if (currentNode->x < _cols - 1) neighbours.push_back(&nodes[currentNode->y][currentNode->x + 1]);
		if (currentNode->y < _rows - 1) neighbours.push_back(&nodes[currentNode->y + 1][currentNode->x]);

		auto nextNodeIndex = getNextNode(currentNode, neighbours);
		if (nextNodeIndex >= 0)
		{
			Node * nextNode = neighbours[nextNodeIndex];

			nodeStack.push(currentNode);

			// break wall
			if (nextNode->x < currentNode->x) { currentNode->left = nextNode; nextNode->right = currentNode; } 
			else if (nextNode->y < currentNode->y) { currentNode->top = nextNode; nextNode->bottom = currentNode; } 
			else if (nextNode->x > currentNode->x) { currentNode->right = nextNode; nextNode->left = currentNode; }
			else { currentNode->bottom = nextNode; nextNode->top = currentNode; }
			
			currentNode = nextNode;
			currentNode->visited = true;
			--unvisitedNodes;
		} else
		{
			// 2 -- Backtrack to previous nodes
			if (!nodeStack.empty()) { currentNode = nodeStack.top(); nodeStack.pop(); }
			else { break; }
		}
	} while (unvisitedNodes > 0);

	return maze;
}

int BacktrackerMazeGenerator::getNextNode(const Node * current, const std::vector<Node*> &neighbours)
{
	std::vector<int> unvisitedNeighbours;
	for (unsigned int i = 0; i<neighbours.size(); ++i)
	{
		if (!neighbours[i]->visited)
		{
			unvisitedNeighbours.push_back(i);
		}
	}

	if (unvisitedNeighbours.empty()) { return -1; }

	return unvisitedNeighbours[Util::randomFromVector(unvisitedNeighbours)];
}
