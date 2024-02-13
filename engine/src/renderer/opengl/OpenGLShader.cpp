//
// Created by Sterling on 2/8/2024.
//

#include <strl-config.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <format>
#include "OpenGLShader.h"

namespace strl
{

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(shader_program_);
}

void OpenGLShader::bind()
{
	glUseProgram(shader_program_);
}

void OpenGLShader::load()
{
	load(std::format("{}/{}", ENGINE_DIRECTORY_LOCATION, "resources/shaders/default.vert"),
		std::format("{}/{}", ENGINE_DIRECTORY_LOCATION, "resources/shaders/default.frag"),
		"");
}

bool OpenGLShader::load(
	const std::string& vertex_shader_path,
	const std::string& fragment_shader_path,
	const std::string& geometry_shader_path)
{
	unsigned int vertex_shader = compile(vertex_shader_path, GL_VERTEX_SHADER);
	if (vertex_shader == 0)
	{
		// TODO: logging stuff
		std::cout << "Vertex shader failed to compile" << std::endl;
		return false;
	}
	unsigned int fragment_shader = compile(fragment_shader_path, GL_FRAGMENT_SHADER);
	if (fragment_shader == 0)
	{
		// TODO: logging stuff
		std::cout << "Fragment shader failed to compile" << std::endl;
		return false;
	}
	unsigned int geometry_shader;
	if (!geometry_shader_path.empty())
	{
		geometry_shader = compile(geometry_shader_path, GL_GEOMETRY_SHADER);
		if (geometry_shader == 0)
		{
			// TODO: logging stuff
			std::cout << "Geometry shader failed to compile" << std::endl;
			return false;
		}
	}

	shader_program_ = glCreateProgram();

	glAttachShader(shader_program_, vertex_shader);
	glAttachShader(shader_program_, fragment_shader);
	if (!geometry_shader_path.empty())
	{
		glAttachShader(shader_program_, geometry_shader);
	}

	int success;
	glLinkProgram(shader_program_);
	glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info_log[512];
		glGetProgramInfoLog(shader_program_, 512, nullptr, info_log);
		// TODO: logging stuff
		std::cout << "Failed to link program\n" << info_log << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	if (!geometry_shader_path.empty())
	{
		glDeleteShader(geometry_shader);
	}

	bind();

	return success;
}

unsigned int OpenGLShader::compile(const std::string& path, GLenum type)
{
	std::ostringstream sstream;
	std::ifstream file(path);

	if (!file.is_open())
	{
		// TODO: logging stuff
		std::cout << "Failed to open file when compiling shader" << std::endl;
		return 0;
	}

	sstream << file.rdbuf();
	std::string shader_source_string = sstream.str();
	const char* shader_source = shader_source_string.c_str();

	unsigned int shader;
	shader = glCreateShader(type);

	glShaderSource(shader, 1, &shader_source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info_log[512];
		glGetShaderInfoLog(shader, 512, nullptr, info_log);
		// TODO: logging stuff
		std::cout << "Failed to compile shader\n" << info_log << std::endl;
		return 0;
	}

	return shader;
}

} // strl