#include "Car.h"

Car::Car(float speed, float acceleration, float* vertices, unsigned int vertices_size, glm::vec3 direction, Shader* program) : speed{ speed }, acceleration{ acceleration }, direction{ direction }, program{ program } { 
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
	bottom_back_coords = glm::vec3(vertices[180], vertices[181], vertices[182]);
}

void Car::draw() {
	glBindVertexArray(vao);
	movement_matrix = glm::translate(movement_matrix, speed * direction);
	notify_Observers();
	set_speed(speed + acceleration);
	program->use();
	program->setMatrix4(movement_matrix, "model");
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	bottom_back_coords += speed * direction;
}
float Car::get_speed() const
{
	return speed;
}

float Car::get_acceleration() const
{
	return acceleration;
}

void Car::set_speed(float new_speed)
{
	speed = new_speed;
}

void Car::set_acceleration(float new_acceleration)
{
	acceleration = new_acceleration;
}

glm::vec3 Car::get_direction() const
{
	return direction;
}

void Car::set_direction(glm::vec3 new_dir) {
	new_dir.x = glm::min((3.0f - bottom_back_coords.x) / speed, new_dir.x);
	new_dir.x = glm::max((-5.0f - bottom_back_coords.x) / speed, new_dir.x);
	direction = new_dir;
}

glm::vec3 Car::get_pos() const {
	return bottom_back_coords;
}

void Car::set_collision() {
	if (orbs_number) {
		--orbs_number;
		return;
	}
	collision = 1;
}

bool Car::check_collision() const {
	return collision;
}

void Car::increase_orbs()
{
	++orbs_number;
}
void Car::decrease_orbs() {
	--orbs_number;
}
