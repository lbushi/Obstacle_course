#pragma once
#include "Shader.h"
#include "Car.h"
#include "Camera.h"
class Obstacle: public Observer {
	float z; // will be used for collision detection
	unsigned int vao, vbo;
	float bottom_left, height, width;
	Shader* program;
public:
	Obstacle(float*, unsigned int, Shader*, float, float, float, float);
	void draw();
	void on_notify(Subject& whonotified) override;
};
