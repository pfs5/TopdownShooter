#include "RandomMazeGenerator.h"
#include "Util.h"
#include "Debug.h"

/**
 * \brief Initialize generator with maze size.
 * \param rows 
 * \param cols 
 */
RandomMazeGenerator::RandomMazeGenerator(unsigned int rows, unsigned int cols):
	_rows{rows},
	_cols{cols}
{

}

RandomMazeGenerator::~RandomMazeGenerator()
{
}


/**
 * \brief Generate completely random maze.
 * \return 
 */
Maze RandomMazeGenerator::generateMaze()
{
	Maze maze{ _rows, _cols };

	// Randomly "break walls" of each node
	auto & nodes = maze.getNodes();
	for (int y=0; y<maze.getRows(); ++y)
	{
		for (int x = 0; x < maze.getCols(); ++x)
		{
			auto &node = nodes[y][x];
		
			// check if neighbour broke top or left wall
			if (x > 0 && nodes[y][x - 1].right) { node.left = &nodes[y][x - 1]; }
			if (y > 0 && nodes[y - 1][x].bottom) { node.top = &nodes[y - 1][x]; }
		
			// roll the dice to break bottom or right wall
			if (x < maze.getCols() - 1 && Util::randomFloat() > 0.5f) { node.right = &nodes[y][x + 1]; }
			if (y < maze.getRows() - 1 && Util::randomFloat() > 0.5f) { node.bottom = &nodes[y + 1][x]; }
		}
	}

	return maze;
}
