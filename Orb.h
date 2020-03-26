#pragma once
#include "Shader.h"
#include "Observer.h"
class Orb: public Observer {
	float z, bottom_left; // collision detection with the car
	float brightness = 0.0f;
	unsigned int vao, vbo;
	Shader* shader;
public:
	Orb(float* vertices, unsigned int vertices_size, Shader* program, float z, float bottom_left);
	void draw();
	void on_notify(Subject& whonotified);
	float get_z() const;
};
