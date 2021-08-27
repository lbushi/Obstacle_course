#include "Shape.h"
#include <iostream>
Shape::Shape() {}
Shape::Shape(float* vertices, const int* vertex_info, unsigned int vertex_info_length, unsigned int vertex_num, unsigned int texID, Shader* shader): shader{shader}, vertex_num{vertex_num}, texID{texID}
{
	int* partials = new int[vertex_info_length];
	partials[0] = 0;
	for (int i = 1; i < vertex_info_length; ++i) {
		partials[i] = partials[i - 1] + vertex_info[i-1];
	}
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (partials[vertex_info_length-1]+vertex_info[vertex_info_length-1]) * sizeof(float) * vertex_num, vertices, GL_STATIC_DRAW);
	for (int i = 0; i < vertex_info_length; ++i) {
		glVertexAttribPointer(i, vertex_info[i], GL_FLOAT, GL_FALSE, (partials[vertex_info_length-1]+vertex_info[vertex_info_length-1]) * sizeof(float), (void*)(partials[i] * sizeof(float)));
		glEnableVertexAttribArray(i);
	}
	glBindVertexArray(0);
	free(partials);
}

void Shape::draw()
{
	glBindVertexArray(vao);
	shader->use();
	if (texID) {
		glBindTexture(GL_TEXTURE_2D, texID);
	}
	glDrawArrays(GL_TRIANGLES, 0, vertex_num);
	glBindVertexArray(0);
}

void Shape::setMatrix(const glm::mat4 matrix, const char* name) {
	shader->use();
	shader->setMatrix4(matrix, name);
}
