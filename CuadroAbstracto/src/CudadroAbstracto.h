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
		rectanguloCentral.scale( 0, 1.1f, 1.8f );
		rectanguloCentral.color( 0, glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
		elements.push_back( rectanguloCentral );

		Figure circles( FigureType::CIRCLE, glm::vec3( 0.0f, 0.0f, 0.05f ) );
		circles.scale( 0, 0.7f );
		circles.duplicate();
		circles.translate( 0, glm::vec3( -0.15f, 0.355f, 0.0f ) );
		circles.translate( 1, glm::vec3( -0.2f, -0.2f, 0.01f ) );
		circles.color( 0, glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
		circles.color( 1, glm::vec4( 0.6f, 0.6f, 0.6f, 1.0f ) );
		elements.push_back( circles );

		Figure yellowRectangles( FigureType::SQUARE, glm::vec3( 0.0f, 0.0f, 0.1f ) );
		yellowRectangles.color( 0, glm::vec4( 0.96f, 0.9f, 0.1f, 1.0f ) );
		yellowRectangles.scale( 0, 0.7f, 1.2f );
		yellowRectangles.rotate( 0, glm::vec3( 0.0f, 0.0f, 1.0f ), -45 );
		yellowRectangles.duplicate();
		yellowRectangles.duplicate();
		yellowRectangles.duplicate();
		yellowRectangles.rotate( 2, glm::vec3( 0.0f, 0.0f, 1.0f ), 45 );
		yellowRectangles.rotate( 3, glm::vec3( 0.0f, 0.0f, 1.0f ), -45 );
		yellowRectangles.translate( 0, glm::vec3( 0.0f, 0.2f, 0.0f ) );
		yellowRectangles.translate( 3, glm::vec3( -0.2f, -0.9f, 0.0f ) );
		elements.push_back( yellowRectangles );


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