#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Observer.h"
#include "Car.h"
class Camera: public Observer, public Subject {
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 frontvector = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 movement_vector = glm::vec3(0.0f, 0.0f, 0.0f);
public:
	glm::mat4 view() const;
	void change_pos();
	void set_movement_vector(glm::vec3);
	void on_notify(Subject& whonotified);
	void setpos(glm::vec3);
	glm::vec3 getpos() const;
	glm::vec3 get_vector() const;
};
