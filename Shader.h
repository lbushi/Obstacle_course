#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
class Shader {
	unsigned int shaderID;
public:
	Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
	void use() const;
	unsigned int getID() const;
	void setMatrix4(const glm::mat4& mat, const char* name);
	void setFloat(const float brightness, const char* name);
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	~Shader();
};
