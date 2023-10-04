#include "Figure.h"

Figure::Figure( FigureType figureType ) {
	type = figureType;
	figurePropierties = createQuad( { 0.0f, 0.0f, 0.0f } );
	for( int i = 0; i < figurePropierties.size(); i++ )
		figurePropierties.at( i ).figureType = { ( float ) figureType };
	if( figureType == FigureType::TRIANGLE ) {
		figurePropierties.erase( figurePropierties.begin() + 3 );
		indices = { 0, 1, 2 };
	} else {
		indices = {
			0, 1, 2,
			2, 3, 0
		};
	}
}

Figure::~Figure() {
	figurePropierties.clear();
	indices.clear();
}

float* Figure::getVertex( int position ) {
	float vertices[] = {
		figurePropierties.at( position ).coordinates.x,
		figurePropierties.at( position ).coordinates.y,
		figurePropierties.at( position ).coordinates.z,
		figurePropierties.at( position ).colors.r,
		figurePropierties.at( position ).colors.g,
		figurePropierties.at( position ).colors.b,
		figurePropierties.at( position ).colors.a,
		figurePropierties.at( position ).textureCoords.x,
		figurePropierties.at( position ).textureCoords.y,
		figurePropierties.at( position ).textureBool,
		figurePropierties.at( position ).figureType,
	};
	return vertices;
}

int Figure::getVertexSize( int position ) {
	return sizeof( figurePropierties.at( position ) );
}

FigureType Figure::getType() {
	return type;
}

float* Figure::getAllVertex( std::vector<Figure> figures ) {
	unsigned int stride = 0;
	unsigned int numberOfVertex;

	float* vertices = new float[ figures.size() * sizeof( Vertex ) * 4 ];

	unsigned int cont = 0;
	for( int i = 0; i < figures.size(); i++ ) {
		if( figures.at( i ).getType() == FigureType::TRIANGLE )
			numberOfVertex = 3;
		else
			numberOfVertex = 4;
		for( unsigned int j = 0; j < numberOfVertex; j++ ) {
			float* eachVertex = figures.at( i ).getVertex( j );
			for( unsigned int k = 0; k < Figure::VertexSize; k++ ) {
				vertices[ cont ] = eachVertex[ k ];
				cont++;
			}
		}
	}
	return vertices;
}

std::vector<Vertex> Figure::createQuad( glm::vec3 centerCoordinates ) {
	float offset = 0.5f;
	Vertex v0, v1, v2, v3;

	v0.coordinates = { centerCoordinates.x - offset, centerCoordinates.y + offset , 0.0f };
	v0.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
	v0.textureCoords = { 0.0f, 0.0f };
	v0.textureBool = { 0.0f };
	v0.figureType = { 0.0f };

	v1.coordinates = { centerCoordinates.x + offset, centerCoordinates.y + offset , 0.0f };
	v1.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
	v1.textureCoords = { 0.0f, 1.0f };
	v1.textureBool = { 0.0f };
	v1.figureType = { 0.0f };

	v2.coordinates = { centerCoordinates.x - offset, centerCoordinates.y - offset , 0.0f };
	v2.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
	v2.textureCoords = { 1.0f, 0.0f };
	v2.textureBool = { 0.0f };
	v2.figureType = { 0.0f };

	v3.coordinates = { centerCoordinates.x + offset, centerCoordinates.y - offset , 0.0f };
	v3.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
	v3.textureCoords = { 1.0f, 1.0f };
	v3.textureBool = { 0.0f };
	v3.figureType = { 0.0f };

	return { v0, v1, v2, v3 };
}
