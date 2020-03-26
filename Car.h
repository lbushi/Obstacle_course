#pragma once
#include <glad/glad.h>
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Subject.h"
class Car: public Subject {
	unsigned int vao;
	unsigned int vbo;
	float speed;
	float acceleration;
	glm::vec3 direction;
	glm::mat4 movement_matrix = glm::mat4(1.0f);
	glm::vec3 bottom_back_coords;
	bool collision = 0;
	int orbs_number = 0;
	Shader* program;
public:
	Car(float speed, float acceleration, float* vertices, unsigned int vertices_size, glm::vec3 direction, Shader* program);
	void draw();
	float get_speed() const;
	float get_acceleration() const;
	void set_speed(float new_speed);
	void set_acceleration(float new_acceleration);
	glm::vec3 get_direction() const;
	void set_direction(glm::vec3);
	glm::vec3 get_pos() const;
	void set_collision();
	bool check_collision() const;
	void increase_orbs();
	void decrease_orbs();
};
