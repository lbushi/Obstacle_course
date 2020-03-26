#pragma once
#include "Shader.h"
class Shape {
	unsigned int vbo;
	unsigned int vao;
	Shader* shader;
public:
	Shape(float* vertices ,unsigned int vertices_size, Shader* shader);
	void draw();
};
