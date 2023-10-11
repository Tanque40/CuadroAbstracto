#pragma once

#include <vector>
#include <array>
#include <glm/glm.hpp>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

enum FigureType {
	TRIANGLE = 0,
	SQUARE = 1,
	CIRCLE = 2,
	DONUT = 3
};

struct Vertex {
	glm::vec3 coordinates;	// X, Y, Z
	glm::vec4 colors;		// R, G, B, A
	glm::vec2 textureCoords;// X, Y
	float textureBool;	// 0: If don't use Texture, 1: If uses
	float figureType;	// 0: Triangle, 1: Square, 2: Circle, 3: Donut
};

class Figure {
private:
	std::vector<Vertex> figurePropierties;
	std::vector<unsigned int> indices;
	FigureType type;

public:
	static const unsigned int VertexSize = sizeof( Vertex ) / sizeof( float ); // Means the positions of each vertex

public:
	/// <summary>
	/// Constructor that make a figure centered in the screen
	/// </summary>
	/// <param name="figureType">TRIANGLE = 0, SQUARE = 1, CIRCLE = 2, DONUT = 3 </param>
	Figure( FigureType figureType );
	/// <summary>
	/// Constructor that make a figure centered in the coordinates positions
	/// </summary>
	/// <param name="figureType">TRIANGLE = 0, SQUARE = 1, CIRCLE = 2, DONUT = 3 </param>
	/// <param name="centerCoordinates">The position of the center of the image</param>
	Figure( FigureType figureType, glm::vec3 centerCoordinates );

	~Figure();

	float* getVertex( int position );
	int getVertexSize( int position );
	FigureType getType();
	unsigned int* getIndices();
	unsigned int getIndicesSize();

	void scale( unsigned int index, float scalar );
	void scale( unsigned int index, float scalarX, float scalarY );

	void rotate( unsigned int index, glm::vec3 rotationVector, float angle );

	void translate( unsigned int index, glm::vec3 translateObjetive );

	void duplicate();

	/// <summary>
	/// Convert all figures to a simple float array
	/// </summary>
	/// <param name="figures">the vector of all the figures</param>
	/// <returns>An array of all the vertex buffer mixed</returns>
	static float* getAllVertex( std::vector<Figure> figures );

	static unsigned int* getAllIndices( std::vector<Figure> figures );

private:
	std::vector<Vertex> createQuad( glm::vec3 centerCoordinates );
};