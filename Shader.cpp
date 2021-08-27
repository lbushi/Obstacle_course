#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	std::ostringstream out;
	std::ifstream in{ vertexShaderSource };
	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		out << line << '\n';
	}
	std::string vertexCode = out.str();
	const char* c_vertexCode = vertexCode.c_str();
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &c_vertexCode, nullptr);
	glCompileShader(vertex_shader);
	GLint vertex_success;
	char vertex_infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_success);
	if (!vertex_success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, vertex_infoLog);
		std::cout << vertex_infoLog;
	}
	out = std::ostringstream();
	in = std::ifstream{ fragmentShaderSource };
	while (!in.eof()) {
		std::getline(in, line);
		out << line << '\n';
	}
	std::string fragmentCode = out.str();
	const char* c_fragmentCode = fragmentCode.c_str();
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &c_fragmentCode, nullptr);
	glCompileShader(fragment_shader);
	GLint fragment_success;
	char fragment_infoLog[512];
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_success);
	if (!fragment_success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, fragment_infoLog);
		std::cout << fragment_infoLog;
	}
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex_shader);
	glAttachShader(shaderID, fragment_shader);
	glLinkProgram(shaderID);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	GLint success;
	char infoLog[512];
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << infoLog;
	}
}

void Shader::use() const
{
	glUseProgram(shaderID);
}
unsigned int Shader::getID() const {
	return shaderID;
}

void Shader::setMatrix4(const glm::mat4& mat, const char* name)
{
	use();
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setFloat(const float brightness, const char* name)
{
	use();
	glUniform1f(glGetUniformLocation(shaderID, name), brightness);
}

void Shader::setBool(const std::string& name, bool value) const
{
	use();
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value) const
{
	use();
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	use();
	glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y) const
{
	use();
	glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	use();
	glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	use();
	glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}


Shader::~Shader() {
	glDeleteProgram(shaderID);
}
