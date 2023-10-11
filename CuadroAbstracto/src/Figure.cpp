#include "Figure.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

unsigned int* Figure::getIndices() {
	return indices.data();
}

unsigned int Figure::getIndicesSize() {
	return indices.size();
}

void Figure::scale( unsigned int index, float scalar ) {

	bool isTriangle = type == FigureType::TRIANGLE;
	unsigned int offset = index * ( isTriangle ) ? 3 : 4;

	figurePropierties.at( 0 + offset ).coordinates *= scalar;
	figurePropierties.at( 1 + offset ).coordinates *= scalar;
	figurePropierties.at( 2 + offset ).coordinates *= scalar;
	if( isTriangle )
		figurePropierties.at( 3 + offset ).coordinates *= scalar;

}
void Figure::scale( unsigned int index, float* scalarX, float* scalarY ) {

	void Figure::scale( unsigned int index, float scalarX, float scalarY ) {
		bool isTriangle = type == FigureType::TRIANGLE;
		unsigned int offset = index * ( isTriangle ) ? 3 : 4;

		float scalarPerSideX = scalarX / 2.0;
		float scalarPerSideY = scalarY / 2.0;

		figurePropierties.at( 0 + offset ).coordinates.x *= scalarPerSideX;
		figurePropierties.at( 0 + offset ).coordinates.y *= scalarPerSideY;
		figurePropierties.at( 1 + offset ).coordinates.x *= scalarPerSideX;
		figurePropierties.at( 1 + offset ).coordinates.y *= scalarPerSideY;
		figurePropierties.at( 2 + offset ).coordinates.x *= scalarPerSideX;
		figurePropierties.at( 2 + offset ).coordinates.y *= scalarPerSideY;
		if( isTriangle ) {
			figurePropierties.at( 3 + offset ).coordinates.x *= scalarPerSideX;
			figurePropierties.at( 3 + offset ).coordinates.y *= scalarPerSideY;
		}
	}

	void Figure::rotate( unsigned int index, glm::vec3 rotationVector, float angle ) {
		bool isTriangle = type == FigureType::TRIANGLE;
		unsigned int offset = index * ( isTriangle ) ? 3 : 4;
		glm::vec4 auxVector;

		glm::mat4 rotationMatrix( 1.0f );
		rotationMatrix = glm::rotate( rotationMatrix, glm::radians( angle ), rotationVector );

		auxVector = glm::vec4( figurePropierties.at( 0 + offset ).coordinates, 1.0f );
		auxVector = auxVector * rotationMatrix;
		figurePropierties.at( 0 + offset ).coordinates = { auxVector.x, auxVector.y, auxVector.z };

		auxVector = glm::vec4( figurePropierties.at( 1 + offset ).coordinates, 1.0f );
		auxVector = auxVector * rotationMatrix;
		figurePropierties.at( 1 + offset ).coordinates = { auxVector.x, auxVector.y, auxVector.z };

		auxVector = glm::vec4( figurePropierties.at( 2 + offset ).coordinates, 1.0f );
		auxVector = auxVector * rotationMatrix;
		figurePropierties.at( 2 + offset ).coordinates = { auxVector.x, auxVector.y, auxVector.z };


		if( isTriangle ) {
			auxVector = glm::vec4( figurePropierties.at( 3 + offset ).coordinates, 1.0f );
			auxVector = auxVector * rotationMatrix;
			figurePropierties.at( 3 + offset ).coordinates = { auxVector.x, auxVector.y, auxVector.z };
		}
	}

	void Figure::translate( unsigned int index, glm::vec3 translateVector ) {
		bool isTriangle = type == FigureType::TRIANGLE;
		unsigned int offset = index * ( isTriangle ) ? 3 : 4;
		glm::vec4 auxVector;

		glm::mat3 transformMatrix( 1.0f );
		transformMatrix = glm::translate( translateVector );

		figurePropierties.at( 0 + offset ).coordinates = figurePropierties.at( 0 + offset ).coordinates * transformMatrix;
		figurePropierties.at( 1 + offset ).coordinates = figurePropierties.at( 1 + offset ).coordinates * transformMatrix;
		figurePropierties.at( 2 + offset ).coordinates = figurePropierties.at( 2 + offset ).coordinates * transformMatrix;

		if( isTriangle ) {
			figurePropierties.at( 3 + offset ).coordinates = figurePropierties.at( 3 + offset ).coordinates * transformMatrix;
		}
	}

	void Figure::duplicate() {
		bool isTriangle = type == FigureType::TRIANGLE;
		Vertex duplicateVertex1, duplicateVertex2, duplicateVertex3, duplicateVertex4;

		duplicateVertex1 = figurePropierties.at( 0 );
		duplicateVertex2 = figurePropierties.at( 1 );
		duplicateVertex3 = figurePropierties.at( 2 );
		if( isTriangle ) {
			duplicateVertex4 = figurePropierties.at( 3 );
		}

		translate( 0, glm::vec3( -0.3f, 0.0f, 0.0f ) );
		translate( 1, glm::vec3( 0.3f, 0.0f, 0.0f ) );
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

		v0.coordinates = { centerCoordinates.x - offset, centerCoordinates.y - offset , 0.0f };
		v0.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
		v0.textureCoords = { 0.0f, 0.0f };
		v0.textureBool = { 0.0f };
		v0.figureType = { 0.0f };

		v1.coordinates = { centerCoordinates.x - offset, centerCoordinates.y + offset , 0.0f };
		v1.colors = { 1.0f, 1.0f, 1.0f, 1.0f };
		v1.textureCoords = { 0.0f, 1.0f };
		v1.textureBool = { 0.0f };
		v1.figureType = { 0.0f };

		v2.coordinates = { centerCoordinates.x + offset, centerCoordinates.y + offset , 0.0f };
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
