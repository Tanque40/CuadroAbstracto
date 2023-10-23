#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "CudadroAbstracto.h"

const int WIDTH = 600;
const int HEIGHT = 900;

static void error_callback( int error, const char* description );
static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );

int main( void ) {
	GLFWwindow* window;

	glfwSetErrorCallback( error_callback );

	if( !glfwInit() )
		exit( EXIT_FAILURE );

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 4 );

	window = glfwCreateWindow( WIDTH, HEIGHT, "Cuadro Abstracto", NULL, NULL );
	if( !window ) {
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	glfwSetKeyCallback( window, key_callback );

	glfwMakeContextCurrent( window );
	gladLoadGL();
	glfwSwapInterval( 1 );

	// How OpenGL will work with the format of textures
	GLCall( glEnable( GL_BLEND ) );
	GLCall( glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ) );

	Shader mainShader( "res/shaders/CuadroAbstracto.vs", "res/shaders/CuadroAbstracto.fs" );
	CuadroAbstracto cuadro;
	cuadro.init();

	float* vertices = cuadro.getVertices();
	unsigned int* indices = cuadro.getIndices();

	std::cout << cuadro.getNumberOfVertices() << std::endl;

	//for( int i = 0; i < cuadro.getNumberOfVertices(); i++ )
		//std::cout << vertices[ i ] << std::endl;

	VertexArray va;
	VertexBuffer vb( vertices, cuadro.getNumberOfVertices() * sizeof( float ) );
	VertexBufferLayout layout;

	// Add a push per every layer that you add to VertexBuffer, the param is de number of
	// positions that use your layer
	// Each layer represents a level, can be a coordinate, color or texture
	layout.push<float>( 3 ); // XYZ
	layout.push<float>( 4 ); // RGBA
	layout.push<float>( 2 ); // TextCoords
	layout.push<float>( 1 ); // TextSelector
	layout.push<float>( 1 ); // IsCircle
	va.addBuffer( vb, layout );
	va.bind();

	IndexBuffer ib( indices, cuadro.getNumberOfIndices() * sizeof( unsigned int ) );

	// Just write the direction of your Texture
	Texture texture1( "res/textures/nether_brick.png" );
	Texture texture2( "res/textures/amatista_block.png" );
	// If you add more than 1 texture, need to add + 1 in the param per each bind call
	texture1.bind( 0 );
	texture2.bind( 1 );

	Renderer renderer;

	glPolygonMode( GL_FRONT, GL_FILL );

	// Setup ImGui binding
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init( window, true );

	// Setup style
	ImGui::StyleColorsDark();

	glm::mat4x4 projection, model, view;

	int samplers[ 2 ] = { 0, 1 };

	GLCall( glEnable( GL_DEPTH_TEST ) );

	while( !glfwWindowShouldClose( window ) ) {
		GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
		{
			float ratio;
			int width, height;

			view = glm::mat4( 1.0f );
			// note that we're translating the scene in the reverse direction of where we want to move
			view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );

			glfwGetFramebufferSize( window, &width, &height );
			ratio = width / ( float ) height;
			glm::vec3 screenResolution( ( float ) width, ( float ) height, 0.0f );

			glViewport( 0, 0, width, height );

			renderer.clear();

			ImGui_ImplGlfwGL3_NewFrame();

			glm::mat4 m( 1.0f );
			//model = glm::rotate( m, ( float ) glfwGetTime(), glm::vec3( 1.0f ) );
			model = m;
			projection = glm::perspective( glm::radians( 45.0f ), ( float ) width / ( float ) height, 0.1f, 100.0f );

			mainShader.bind();
			mainShader.SetuniformsMat4f( "projection", projection );
			mainShader.SetuniformsMat4f( "view", view );
			mainShader.SetuniformsMat4f( "model", model );
			mainShader.setUniform1iv( "ourTextures", sizeof( samplers ), samplers );

			renderer.draw( va, ib, mainShader );
		}

		ImGui::Begin("Controls");
		{
			ImGui::Text( "Project 2" );

		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData( ImGui::GetDrawData() );

		GLCall( glfwSwapBuffers( window ) );
		GLCall( glfwPollEvents() );
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	exit( EXIT_SUCCESS );
}

static void error_callback( int error, const char* description ) {
	fprintf( stderr, "Error: %s\n", description );
}

static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose( window, GLFW_TRUE );
}