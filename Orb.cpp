#include "Orb.h"
#include "Car.h"

Orb::Orb(float* vertices, unsigned int vertices_size, Shader* shader, float z, float bottom_left): shader{shader}, z{z}, bottom_left{bottom_left}
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

void Orb::draw()
{
	brightness += 0.01f;
	glBindVertexArray(vao);
	shader->use();
	shader->setFloat(brightness, "brightness");
	glDrawArrays(GL_TRIANGLES, 0, 30);
	glBindVertexArray(0);
	shader->setFloat(0.0f, "brightness");
	if (brightness >= 0.5f) {
		brightness = 0.0f;
	}
}

void Orb::on_notify(Subject& whonotified)
{
	Car& car = static_cast<Car&>(whonotified);
	const glm::vec3 car_pos = car.get_pos();
	if (((car_pos.x > bottom_left && car_pos.x < bottom_left + 5) || (car_pos.x + 2 > bottom_left && car_pos.x + 2 < bottom_left + 5)) && abs(car_pos.z - z) <= 2.0f) {
		car.increase_orbs();
	}
}

float Orb::get_z() const
{
	return z;
}
