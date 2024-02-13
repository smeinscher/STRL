//
// Created by Sterling on 2/8/2024.
//

#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include "../IShader.h"
#include "glad/glad.h"

namespace strl
{

class OpenGLShader : public IShader
{
public:
	~OpenGLShader();
	void bind() override;
	void load() override;
	bool load(
		const std::string& vertex_shader_path,
		const std::string& fragment_shader_path,
		const std::string& geometry_shader_path) override;

private:
	int shader_program_;
	static unsigned int compile(const std::string& path, GLenum type);
};

} // strl

#endif //OPENGLSHADER_H
