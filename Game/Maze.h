#pragma once
#include <vector>
#include <iostream>

class Node;

class Maze
{
	std::vector<std::vector<Node>> _nodes;

	unsigned int _rows;
	unsigned int _cols;
public:
	Maze(unsigned int rows, unsigned int cols);
	Maze(const std::vector<std::vector<Node>> &nodes);
	~Maze();

	void printMaze() const;

	// Getters
	inline const std::vector<std::vector<Node>>& getNodes() const { return _nodes; };
	inline std::vector<std::vector<Node>>& getNodes() { return _nodes; }

	inline unsigned int getRows() const { return _rows; }
	inline unsigned int getCols() const { return _cols; }
};

class Node
{
	friend class Maze;

private:
	mutable std::vector<Node*> _neighbours;

public:
	bool visited;

	// Neighbour pointers
	Node *left;
	Node *right;
	Node *top;
	Node *bottom;

	unsigned int x;
	unsigned int y;
public:
	Node();

	const std::vector<Node*> &getNeighbours() const;

	// Operators
	friend std::ostream& operator<< (std::ostream& os, const Node &node);
};