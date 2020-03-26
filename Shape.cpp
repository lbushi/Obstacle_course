#include "Shape.h"
#include <iostream>
Shape::Shape(float* vertices, unsigned int vertices_size, Shader* shader): shader{shader}
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void Shape::draw()
{
	glBindVertexArray(vao);
	shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
