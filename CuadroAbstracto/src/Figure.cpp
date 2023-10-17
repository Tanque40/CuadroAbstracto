#include "Figure.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

Figure::Figure( FigureType figureType ) {
	type = figureType;
	figurePropierties = createQuad( { 0.0f, 0.0f, 0.0f } );
	for( int i = 0; i < figurePropierties.size(); i++ )
		figurePropierties.at( i ).figureType = { ( float ) figureType };
	if( isTriangle() ) {
		figurePropierties.erase( figurePropierties.begin() + 3 );
		indices = { 0, 1, 2 };
	} else {
		indices = {
			0, 1, 2,
			2, 3, 0
		};
	}
}

Figure::Figure( FigureType figureType, glm::vec3 centerCoordinates ) {
	type = figureType;
	figurePropierties = createQuad( centerCoordinates );
	for( int i = 0; i < figurePropierties.size(); i++ )
		figurePropierties.at( i ).figureType = { ( float ) figureType };
	if( isTriangle() ) {
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

unsigned int* Figure::getIndices() {
	return indices.data();
}

unsigned int Figure::getIndicesSize() {
	return indices.size();
}

void Figure::scale( unsigned int index, float scalar ) {
	unsigned int offset = index * numberOfVertex();
	unsigned int position = 0;

	position = 0 + offset;
	figurePropierties.at( position ).coordinates *= scalar;
	position = 1 + offset;
	figurePropierties.at( position ).coordinates *= scalar;
	position = 2 + offset;
	figurePropierties.at( position ).coordinates *= scalar;
	if( !isTriangle() ) {
		position = 3 + offset;
		figurePropierties.at( position ).coordinates *= scalar;
	}

}

void Figure::scale( unsigned int index, float scalarX, float scalarY ) {
	unsigned int offset = index * numberOfVertex();

	figurePropierties.at( 0 + offset ).coordinates.x *= scalarX;
	figurePropierties.at( 0 + offset ).coordinates.y *= scalarY;
	figurePropierties.at( 1 + offset ).coordinates.x *= scalarX;
	figurePropierties.at( 1 + offset ).coordinates.y *= scalarY;
	figurePropierties.at( 2 + offset ).coordinates.x *= scalarX;
	figurePropierties.at( 2 + offset ).coordinates.y *= scalarY;
	if( !isTriangle() ) {
		figurePropierties.at( 3 + offset ).coordinates.x *= scalarX;
		figurePropierties.at( 3 + offset ).coordinates.y *= scalarY;
	}
}

void Figure::rotate( unsigned int index, glm::vec3 rotationVector, float angle ) {
	unsigned int offset = index * numberOfVertex();
	unsigned int position = 0;
	glm::vec4 auxVector;

	glm::mat4 rotationMatrix( 1.0f );
	rotationMatrix = glm::rotate( rotationMatrix, glm::radians( angle ), rotationVector );

	auxVector = glm::vec4( figurePropierties.at( 0 + offset ).coordinates, 1.0f );
	auxVector = rotationMatrix * auxVector;
	position = 0 + offset;
	figurePropierties.at( position ).coordinates = { auxVector.x, auxVector.y, auxVector.z };

	auxVector = glm::vec4( figurePropierties.at( 1 + offset ).coordinates, 1.0f );
	auxVector = rotationMatrix * auxVector;
	position = 1 + offset;
	figurePropierties.at( position ).coordinates = { auxVector.x, auxVector.y, auxVector.z };

	auxVector = glm::vec4( figurePropierties.at( 2 + offset ).coordinates, 1.0f );
	auxVector = rotationMatrix * auxVector;
	position = 2 + offset;
	figurePropierties.at( position ).coordinates = { auxVector.x, auxVector.y, auxVector.z };


	if( !isTriangle() ) {
		auxVector = glm::vec4( figurePropierties.at( 3 + offset ).coordinates, 1.0f );
		auxVector = rotationMatrix * auxVector;
		position = 3 + offset;
		figurePropierties.at( position ).coordinates = { auxVector.x, auxVector.y, auxVector.z };
	}
}

void Figure::translate( unsigned int index, glm::vec3 translateVector ) {
	unsigned int offset = index * numberOfVertex();
	glm::vec4 auxVector( 1.0f );

	glm::mat4 transformMatrix( 1.0f );
	transformMatrix = glm::translate( transformMatrix, translateVector );

	auxVector = glm::vec4( figurePropierties.at( 0 + offset ).coordinates, 1.0f );
	auxVector = transformMatrix * auxVector;
	figurePropierties.at( 0 + offset ).coordinates = { auxVector.x, auxVector.y, auxVector.z };

	auxVector = glm::vec4( figurePropierties.at( 1 + offset ).coordinates, 1.0f );
	auxVector = transformMatrix * auxVector;
	figurePropierties.at( 1 + offset ).coordinates = { auxVector.x, auxVector.y, auxVector.z };

	auxVector = glm::vec4( figurePropierties.at( 2 + offset ).coordinates, 1.0f );
	auxVector = transformMatrix * auxVector;
	figurePropierties.at( 2 + offset ).coordinates = { auxVector.x, auxVector.y, auxVector.z };

	if( !isTriangle() ) {
		auxVector = glm::vec4( figurePropierties.at( 3 + offset ).coordinates, 1.0f );
		auxVector = transformMatrix * auxVector;
		figurePropierties.at( 3 + offset ).coordinates = { auxVector.x, auxVector.y, auxVector.z };
	}
}

void Figure::duplicate() {
	Vertex duplicateVertex1, duplicateVertex2, duplicateVertex3, duplicateVertex4;

	duplicateIndices();

	duplicateVertex1 = figurePropierties.at( 0 );
	duplicateVertex2 = figurePropierties.at( 1 );
	duplicateVertex3 = figurePropierties.at( 2 );
	figurePropierties.push_back( duplicateVertex1 );
	figurePropierties.push_back( duplicateVertex2 );
	figurePropierties.push_back( duplicateVertex3 );
	if( !isTriangle() ) {
		duplicateVertex4 = figurePropierties.at( 3 );
		figurePropierties.push_back( duplicateVertex4 );
	}

	translate( 0, glm::vec3( -0.3f, 0.0f, 0.0f ) );
	translate( 1, glm::vec3( 0.3f, 0.0f, 0.0f ) );

}

void Figure::duplicateIndices() {
	unsigned int numberOfIndicesToAdd = ( numberOfVertex() == 3 ) ? 3 : 6;
	unsigned int offset = figurePropierties.size();
	for( unsigned int i = 0; i < numberOfIndicesToAdd; i++ ) {
		indices.push_back( indices.at( i ) + offset );
	}
}


void Figure::color( unsigned int index, glm::vec4 newColor ) {
	unsigned int offset = index * numberOfVertex();

	for( unsigned int i = 0; i < numberOfVertex(); i++ )
		figurePropierties.at( i + offset ).colors = newColor;
}

float* Figure::getAllVertex( std::vector<Figure> figures ) {
	unsigned int stride = 0;
	unsigned int numberOfVertex;

	float* vertices = new float[ figures.size() * sizeof( Vertex ) * 4 ];

	unsigned int cont = 0;
	for( int i = 0; i < figures.size(); i++ ) {
		numberOfVertex = figures.at( i ).sizeOfPropierties();
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

unsigned int* Figure::getAllIndices( std::vector<Figure> figures ) {
	unsigned int* indices = new unsigned int[ figures.size() * 6 ];

	unsigned int offset = 0;
	unsigned int cont = 0;
	for( unsigned int i = 0; i < figures.size(); i++ ) {
		unsigned int* figureIndices = figures.at( i ).getIndices();
		for( unsigned int j = 0; j < figures.at( i ).getIndicesSize(); j++ ) {
			indices[ cont ] = figureIndices[ j ] + offset;
			cont++;
		}
		offset += ( figures.at( i ).getType() == FigureType::TRIANGLE ) ? 3 : 4;
	}

	return indices;
}

std::vector<Vertex> Figure::createQuad( glm::vec3 centerCoordinates ) {
	float offset = 0.5f;
	Vertex v0, v1, v2, v3;

	v0.coordinates = { centerCoordinates.x - offset, centerCoordinates.y - offset , centerCoordinates.z };
	v0.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
	v0.textureCoords = { 0.0f, 0.0f };
	v0.textureBool = { 0.0f };
	v0.figureType = { 0.0f };

	v1.coordinates = { centerCoordinates.x - offset, centerCoordinates.y + offset , centerCoordinates.z };
	v1.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
	v1.textureCoords = { 0.0f, 1.0f };
	v1.textureBool = { 0.0f };
	v1.figureType = { 0.0f };

	v2.coordinates = { centerCoordinates.x + offset, centerCoordinates.y + offset , centerCoordinates.z };
	v2.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
	v2.textureCoords = { 1.0f, 1.0f };
	v2.textureBool = { 0.0f };
	v2.figureType = { 0.0f };

	v3.coordinates = { centerCoordinates.x + offset, centerCoordinates.y - offset , centerCoordinates.z };
	v3.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
	v3.textureCoords = { 1.0f, 0.0f };
	v3.textureBool = { 0.0f };
	v3.figureType = { 0.0f };

	return { v0, v1, v2, v3 };
}
