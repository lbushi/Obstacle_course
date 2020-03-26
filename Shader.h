#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
class Shader {
	unsigned int shaderID;
public:
	Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
	void use() const;
	void setMatrix4(const glm::mat4& mat, const char* name);
	void setFloat(const float brightness, const char* name);
	~Shader();
};
