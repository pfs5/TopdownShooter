#pragma once
#include "Maze.h"

class IMazeGenerator
{
public:
	virtual ~IMazeGenerator() = default;
	virtual Maze generateMaze() = 0;
};