#include "Camera.h"

glm::mat4 Camera::view() const
{
	return glm::lookAt(cameraPos, cameraPos + frontvector, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::change_pos() {
	cameraPos += movement_vector;
}

void Camera::set_movement_vector(glm::vec3 movement_vector) {
	this->movement_vector = movement_vector;
}

void Camera::on_notify(Subject& whonotified) {
	//Car& car = static_cast<Car&>(whonotified);
	//movement_vector = car.get_speed() * car.get_direction();//glm::vec3(0.0f, 0.0f, (car.get_speed() * car.get_direction()).z);
}


void Camera::setpos(glm::vec3 pos) {
	cameraPos = pos;
}

glm::vec3 Camera::getpos() const {
	return cameraPos;
}

glm::vec3 Camera::get_vector() const {
	return movement_vector;
}
