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
Shader::~Shader() {
	glDeleteProgram(shaderID);
}
