#include "PhysicsLayers.h"

#include <iostream>

const std::vector<std::vector<bool>> PhysicsLayers::fillIgnoreMatrix() {
	std::vector<std::vector<bool>> matrix;
	
	// Init matrix
	for (int i = 0; i < NUMBER_OF_LAYERS; ++i) {
		std::vector<bool> row(NUMBER_OF_LAYERS, false);
		matrix.push_back(row);
	}

	matrix[3][3] = true;	// bullets with bullets
	matrix[4][4] = true;	// bullets with bullets
	matrix[3][4] = true;	// bullets with bullets
	matrix[4][3] = true;	// bullets with bullets
	
	return matrix;
}

int PhysicsLayers::layerNumber(std::string _name) {
	for (int i = 0; i < layers.size(); ++i) {
		if (_name == layers[i]) {
			return i;
		}
	}

	return -1;
}

std::string PhysicsLayers::layerName(int _number) {
	return layers[_number];
}
