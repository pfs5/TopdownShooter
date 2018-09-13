#pragma once
#include "IMazeGenerator.h"

/**
 *	Generates completely random mazes
 */
class RandomMazeGenerator : public IMazeGenerator
{
	unsigned int _rows;
	unsigned int _cols;
public:
	RandomMazeGenerator(unsigned int rows = 0, unsigned int cols = 0);
	~RandomMazeGenerator();

	Maze * generateMaze() override;
};

