//
// Created by Sterling on 2/9/2024.
//

#ifndef OPENGLSHADERUTILS_H
#define OPENGLSHADERUTILS_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>
#include <glm/detail/type_quat.hpp>

namespace strl
{

class OpenGLShaderUtils
{
public:
	static void set_int(unsigned int shader_program, const char* name, int value);
	static void set_int(unsigned int shader_program, const char* name, const int* values, unsigned int count);
	static void set_float(unsigned int shader_program, const char* name, float value);
	static void set_float(unsigned int shader_program, const char* name, const float* values, unsigned int count);
	static void set_vec2(unsigned int shader_program, const char* name, const glm::vec2& value);
	static void set_ivec2(unsigned int shader_program, const char* name, const glm::ivec2& value);
	static void set_ivec2(unsigned int shader_program, const char* name, const glm::ivec2* values, unsigned int count);
	static void set_vec3(unsigned int shader_program, const char* name, const glm::vec3& value);
	static void set_vec3(unsigned int shader_program, const char* name, const glm::vec3* values, unsigned int count);
	static void set_vec4(unsigned int shader_program, const char* name, const glm::vec4& value);
	static void set_vec4(unsigned int shader_program, const char* name, const glm::vec4* values, unsigned int count);
	static void set_quat(unsigned int shader_program, const char* name, const glm::quat& value);
	static void set_quat(unsigned int shader_program, const char* name, const glm::quat* values, unsigned int count);
	static void set_mat4(unsigned int shader_program, const char* name, const glm::mat4& mat);
	static void set_mat4(unsigned int shader_program, const char* name, const glm::mat4* mat, unsigned int count);
};

} // strl

#endif //OPENGLSHADERUTILS_H
