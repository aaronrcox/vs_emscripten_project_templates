#include "Application.h"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <glm\ext.hpp>


Application::Application(int argc, char **argv) : BaseApplication(argc, argv)
{

}

Application::~Application()
{

}

void Application::Load()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_projection = glm::perspective(45.0f, (float)GetWindowWidth() / (float)GetWindowHeight(), 0.001f, 1000.0f);
	m_view = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	
	LoadShader();
	CreateCube();
}
void Application::Unload()
{
	DestroyCube();
	UnloadShader();
}

void Application::Update(float deltaTime)
{
	// rotate the model 90degrees over 1 second along the z axis
	m_model = glm::rotate(m_model, glm::radians(90.0f * deltaTime), glm::vec3(0, 0, 1));
}

void Application::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Step 1: Before rendering geometry, tell opengl to use our shader program.
	glUseProgram(m_shader);

	// Step 2:	Send uniform values to shader
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "projection"), 1, false, &m_projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "view"), 1, false, &m_view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "model"), 1, false, &m_model[0][0]);

	// Step 3: rendering the cube
	glBindVertexArray(m_cube.vao);
	glDrawElements(GL_TRIANGLES, m_cube.indicesCount, GL_UNSIGNED_BYTE, 0);

	// Step 4: Now that we are done drawing the geometry
	// unbind the vao, we are basicly cleaning the opengl state
	glBindVertexArray(0);

	// Step 5: de-activate the shader program, dont do future rendering with it any more.
	glUseProgram(0);

}

void Application::CreateCube()
{
	// Step 1:
	// Specify the position and color for each vert of a cube
	// for this example, each face does not share a vert, so we have 4 verts for each face of our cube/
	Vertex verts[] = {
		// POSITION				  COLOR	
		// FRONT FACE
		// x	y	  z		w     red	green blue, alpha
		{-0.5f,-0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },	// 0
		{ 0.5f,-0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },	// 1
		{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },	// 2
		{-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },	// 3
											
		// BACK FACE						
		// x	y	  z		w     red	green blue, alpha											
		{-0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },	// 4
		{ 0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },	// 5
		{ 0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },	// 6
		{-0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },	// 7
											
		// LEFT FACE						
		// x	y	  z		w     red	green blue, alpha
		{-0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f },	// 8
		{-0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f },	// 9
		{-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f },	// 10
		{-0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f },	// 11
											
		// RIGHT FACE						
		// x	y	  z		w     red	green blue, alpha
		{ 0.5f,-0.5f,-0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f },	// 12
		{ 0.5f,-0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f },	// 13
		{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f },	// 14
		{ 0.5f, 0.5f,-0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f },	// 15
											
		// TOP FACE							
		// x	y	  z		w     red	green blue, alpha
		{-0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },	// 16
		{-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },	// 17
		{ 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },	// 18
		{ 0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },	// 19
											
		// BOTTOM FACE						
		// x	y	  z		w     red	green blue, alpha
		{-0.5f,-0.5f,-0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f },	// 20
		{-0.5f,-0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f },	// 21
		{ 0.5f,-0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f },	// 22
		{ 0.5f,-0.5f,-0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }	// 23
	};

	// Step 2:
	// From the above verts, we need to construct triangles that opengl can then use to render.
	// Winding order is important, each triangle needs to be described in a clockwise order
	// this defines the faceing direction for the triangle.
	// By default OpenGL will cull pixels that are "facing away" from the camera glCullMode(GL_BACK) is the default setting.
	// Culling can be changed to GL_FRONT or GL_FRONT_AND_BACK, or enabled/dsabled via glEnable(GL_CULL_FACE) / glDisable(GL_CULL_FACE)
	unsigned char indices[] =
	{
		0, 1, 2,	 0, 2, 3,  // front face
		6, 5, 4,	 7, 6, 4,  // back face
		8,9,10,		 8,10,11,  // left face
		14,13,12,	 15,14,12, // right face
		16,17,18,	 16,18,19, // top face
		22,21,20,	 23,22,20  // bottom face
	};

	// Step 3:
	// Its always a good idea to keep track of how many verts and indices we have
	// When drawing the glDrawElements method requires the number if indices
	// sizeof(verts) returns the entire size in bytes of the array
	// sizeof(Vertex) returns the size in bytes of a single vertes
	// we can calculate the number of verts or indices by dividing.
	m_cube.vertCount	= sizeof(verts) / sizeof(Vertex);
	m_cube.indicesCount = sizeof(indices) / sizeof(unsigned char);

	// Step 4:
	// Generate the VAO and Bind bind it.
	// Our VBO (vertex buffer object) and IBO (Index Buffer Object) will be "grouped" with this VAO
	// other settings will also be grouped with the VAO. this is used so we can reduce draw calls in the render method.
	glGenVertexArrays(1, &m_cube.vao);
	glBindVertexArray(m_cube.vao);

	// Step 5:
	// Create our VBO and IBO.
	// Then tell Opengl what type of buffer they are used for
	// VBO a buffer in graphics memory to contains our vertices
	// IBO a buffer in graphics memory to contain our indices.
	// Then Fill the buffers with our generated data.
	// This is taking our verts and indices from ram, and sending them to the graphics card
	glGenBuffers(1, &m_cube.vbo);
	glGenBuffers(1, &m_cube.ibo);

	glBindBuffer(GL_ARRAY_BUFFER, m_cube.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cube.ibo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Step 6:
	// Vertices can have any shape, for us, each vertex has a position and color.
	// The "shape" of our vertex need to be described to OepnGL
	// This is so the vertices can be sent to our shader and be mapped to the correct variables locations.
	Vertex::SetupVertexAttribPointers();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Application::DestroyCube()
{
	// When We're Done, destroy the geometry
	glDeleteBuffers(1, &m_cube.vbo);
	glDeleteBuffers(1, &m_cube.ibo);
	glDeleteVertexArrays(1, &m_cube.vao);
}

void Application::LoadShader()
{

	char vertex_shader[] =
		"																		\n"
		"	attribute vec4 vPosition;											\n"
		"	attribute vec4 vColor;												\n"
		"	varying vec4 fColor;												\n"
		"	uniform mat4 projection;											\n"
		"	uniform mat4 view;													\n"
		"	uniform mat4 model;													\n"
		"	void main ()														\n"
		"	{																	\n"
		"		fColor = vColor;												\n"
		"		gl_Position = projection * view * model * vPosition;			\n"
		"	}																	\n"
		"	";

	char fragment_shader[] =
		"																		\n"
#ifdef __EMSCRIPTEN__
		"	precision mediump float;											\n"
#endif
		"	varying vec4 fColor;												\n"
		"	void main ()														\n"
		"	{																	\n"
		"		gl_FragColor = fColor;											\n"
		"	}																	\n"
		"	";

	const char *vss = vertex_shader;
	const char *fss = fragment_shader;

	// Step 1:
	// Load the vertex shader, provide it with the source code and compile it.
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vss, NULL);
	glCompileShader(vs);

	// Step 2:
	// Load the fragment shader, provide it with the source code and compile it.
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fss, NULL);
	glCompileShader(fs);

	// Step 3:
	// Create the shader program
	m_shader = glCreateProgram();

	// Step 4:
	// Attach the vertex and fragment shaders to the shader program
	glAttachShader(m_shader, vs);
	glAttachShader(m_shader, fs);

	// Step 5:
	// Describe the location of the shader elements
	// NOTE: the method: SetupVertexAttribPointers
	// these locations are used when describing the verts
	glBindAttribLocation(m_shader, 0, "vPosition");
	glBindAttribLocation(m_shader, 1, "vColor");

	glLinkProgram(m_shader);

	// Step 6:
	// destroy the vertex and fragment shader, we are finished with them
	// as they have been combined into the shaderProgram
	glDeleteShader(vs);
	glDeleteShader(fs);

}

void Application::UnloadShader()
{
	glDeleteProgram(m_shader);
}


void Vertex::SetupVertexAttribPointers()
{
	// enable vertex position element
	// notice when we loaded the shader, we described the "position" element to be location 0.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0 (position)
		4,                  // size - how many floats make up the position (x, y, z)
		GL_FLOAT,           // type - our x, y, z are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)0            // offset - bytes from the beginning of the vertex
	);

	// enable vertex color element
	// notice when we loaded the shader, we described the "color" element to be location 1.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 1 (color)
		4,                  // size - how many floats make up the color (r, g, b, a)
		GL_FLOAT,           // type - our r,g,b,a are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)(sizeof(float) *4)            // offset - bytes from the beginning of the vertex
	);
}
