#pragma once
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "Figure.h"

class CuadroAbstracto {
private:
	std::vector<Figure> elements;
	unsigned int numberOfVertices = 0;
	unsigned int numberOfIndices = 0;


public:

	~CuadroAbstracto() {
		elements.~vector();
	};

	void init() {
		Figure rectanguloCentral( FigureType::SQUARE, glm::vec3( 0.05f, 0.0f, 0.0f ) );
		rectanguloCentral.scale( 0, 1.1f, 1.5f );
		rectanguloCentral.color( 0, glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
		elements.push_back( rectanguloCentral );

		Figure circles( FigureType::CIRCLE, glm::vec3( 0.0f, 0.0f, 0.1f ) );
		circles.duplicate();
		elements.push_back( circles );

		countVertices();
		countIndices();
	};

	unsigned int getNumberOfVertices() {
		return numberOfVertices;
	};

	unsigned int getNumberOfIndices() {
		return numberOfIndices;
	};

	float* getVertices() {
		return Figure::getAllVertex( elements );
	}

	unsigned int* getIndices() {
		return Figure::getAllIndices( elements );
	}

private:
	void countVertices() {
		for each( Figure figure in elements ) {
			numberOfVertices += figure.numberOfVertices();
		}
	};
	void countIndices() {
		for each( Figure figure in elements ) {
			numberOfIndices += figure.getIndicesSize();
		}
	};
};