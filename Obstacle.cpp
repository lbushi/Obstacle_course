#include "Obstacle.h"
#include <iostream>
Obstacle::Obstacle(float* vertices, unsigned int vertices_size, Shader* program, float z, float bottom_left, float width, float height) : program{program}, z{z}, bottom_left{bottom_left}, height{height}, width{width}
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

void Obstacle::draw()
{
	program->use();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Obstacle::on_notify(Subject& whonotified) {
	Car& car = static_cast<Car&>(whonotified);
	const glm::vec3 car_pos = car.get_pos();
	if (((car_pos.x > bottom_left && car_pos.x < bottom_left + width) || (car_pos.x + 2 > bottom_left && car_pos.x + 2 < bottom_left + width)) && abs(car_pos.z - z) <= 2.0f && car_pos.y < -4.0f + height) {
		car.set_collision();
	}
}

