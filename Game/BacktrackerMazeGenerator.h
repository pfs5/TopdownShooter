#pragma once
#include "IMazeGenerator.h"

class BacktrackerMazeGenerator : IMazeGenerator
{
	unsigned int _rows;
	unsigned int _cols;
public:
	BacktrackerMazeGenerator(unsigned int rows, unsigned int cols);
	~BacktrackerMazeGenerator();

	Maze generateMaze() override;

private:
	static int getNextNode(const Node * curent, const std::vector<Node*> &neighbours);
};

