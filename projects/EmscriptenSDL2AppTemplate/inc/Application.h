#pragma once

#include "BaseApplication.h"
#include <vector>

#include <glm\glm.hpp>

struct Vertex
{
	float x, y, z, w;
	float r, g, b, a;

	static void SetupVertexAttribPointers();
};

struct GLMesh
{
	unsigned int vertCount;
	unsigned int indicesCount;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
};

class Application : public BaseApplication
{
public:

	Application(int argc, char **argv);
	virtual ~Application();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void CreateCube();
	void DestroyCube();

	void LoadShader();
	void UnloadShader();

private:

	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	
	GLMesh m_cube;
	unsigned int m_shader;
};