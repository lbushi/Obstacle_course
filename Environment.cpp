#include "Environment.h"
Environment::Environment(float* vertices, unsigned int vertices_size, unsigned int textureID, Shader* program) : program{ program }, textureID{ textureID }
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void Environment::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(vao);
	program->use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
