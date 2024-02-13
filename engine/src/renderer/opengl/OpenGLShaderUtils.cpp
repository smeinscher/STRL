//
// Created by Sterling on 2/9/2024.
//

#include "OpenGLShaderUtils.h"
#include "glad/glad.h"

namespace strl
{

void OpenGLShaderUtils::set_int(unsigned int shader_program, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(shader_program, name), value);
}

void OpenGLShaderUtils::set_int(unsigned int shader_program, const char* name, const int* values, unsigned int count)
{
	glUniform1iv(glGetUniformLocation(shader_program, name), (GLsizei)count, values);
}

void OpenGLShaderUtils::set_float(unsigned int shader_program, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(shader_program, name), value);
}

void OpenGLShaderUtils::set_float(unsigned int shader_program, const char* name, const float* values, unsigned int count)
{
	glUniform1fv(glGetUniformLocation(shader_program, name), (GLsizei)count, values);
}

void OpenGLShaderUtils::set_vec2(unsigned int shader_program, const char* name, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(shader_program, name), 1, &value[0]);
}

void OpenGLShaderUtils::set_ivec2(unsigned int shader_program, const char* name, const glm::ivec2& value)
{
	glUniform2iv(glGetUniformLocation(shader_program, name), 1, &value[0]);
}

void OpenGLShaderUtils::set_ivec2(unsigned int shader_program, const char* name, const glm::ivec2* values, unsigned int count)
{
	glUniform2iv(glGetUniformLocation(shader_program, name), (GLsizei)count, (int*)values);
}

void OpenGLShaderUtils::set_vec3(unsigned int shader_program, const char* name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(shader_program, name), 1, &value[0]);
}

void OpenGLShaderUtils::set_vec3(unsigned int shader_program, const char* name, const glm::vec3* values, unsigned int count)
{
	glUniform3fv(glGetUniformLocation(shader_program, name), (GLsizei)count, (float*)&values[0]);
}

void OpenGLShaderUtils::set_vec4(unsigned int shader_program, const char* name, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(shader_program, name), 1, &value[0]);
}

void OpenGLShaderUtils::set_vec4(unsigned int shader_program, const char* name, const glm::vec4* values, unsigned int count)
{
	glUniform4fv(glGetUniformLocation(shader_program, name), (GLsizei)count, (float*)&values[0]);
}

void OpenGLShaderUtils::set_quat(unsigned int shader_program, const char* name, const glm::quat& value)
{
	glUniform4fv(glGetUniformLocation(shader_program, name), 1, &value[0]);
}

void OpenGLShaderUtils::set_quat(unsigned int shader_program, const char* name, const glm::quat* values, unsigned int count)
{
	glUniform4fv(glGetUniformLocation(shader_program, name), (GLsizei)count, (float*)&values[0]);
}

void OpenGLShaderUtils::set_mat4(unsigned int shader_program, const char* name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shader_program, name), 1, GL_FALSE, &mat[0][0]);
}

void OpenGLShaderUtils::set_mat4(unsigned int shader_program, const char* name, const glm::mat4* mat, unsigned int count)
{
	glUniformMatrix4fv(glGetUniformLocation(shader_program, name), (GLsizei)count, GL_FALSE, (float*)&mat[0][0]);
}

} // strl