#pragma once
#include <vector>
#include <iostream>

#include "Figure.h"

class CuadroAbstracto {
public:
	std::vector<Figure> elements;

public:
	void init() {
		Figure cuadradoCentral( FigureType::SQUARE );
		elements.push_back( cuadradoCentral );
		std::cout << "Wun't" << std::endl;
	};

	float* getVertices() {
		return Figure::getAllVertex( elements );
	}

	unsigned int* getIndices() {
		return Figure::getAllIndices( elements );
	}

};