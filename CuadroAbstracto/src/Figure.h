#pragma once

#include <vector>
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
	glm::vec1 figureType;	// 0: To Square, 1: To Circle
	glm::vec4 colors;		// R, G, B, A
	glm::vec2 textureCoords;// X, Y
	glm::vec1 textureBool;	// 0: If don't use Texture, 1: If uses
};

class Figure {
private:
	VertexArray va;
	IndexBuffer ib;
	VertexBuffer vb;
	VertexBufferLayout layout;

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
	/// <param name="coordinates">The position of the center of the image</param>
	Figure( FigureType figureType, glm::vec3 coordinates );



	/// <summary>
	/// Convert all figures to a simple float array
	/// </summary>
	/// <param name="figures">the vector of all the figures</param>
	/// <returns>An array of all the vertex buffer mixed</returns>
	static float* getAllVertex( std::vector<Figure> figures );
};