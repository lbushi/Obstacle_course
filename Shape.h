#pragma once
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>


class Shape {
protected:
	unsigned int vbo;
	unsigned int vao;
	unsigned int vertex_num;
	unsigned int texID = 0;
	Shader* shader;
public:
	Shape();
	Shape(float* vertices ,const int*, unsigned int vertices_size,unsigned int, unsigned int texID, Shader* shader);
	void draw();
	void setMatrix(const glm::mat4 matrix, const char* name);
};
