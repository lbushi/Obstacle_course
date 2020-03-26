#pragma once
#include <glad/glad.h>
#include "Shader.h"
class Environment {
	unsigned int vao, vbo, textureID;
	Shader* program;
public:
	Environment(float* vertices, unsigned int vertices_size, unsigned char* data, int width, int height, Shader* program);
	void draw();
};
