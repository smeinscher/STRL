//
// Created by Sterling on 2/8/2024.
//

#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include "../../core/manager/STRLManagedItemBase.h"

namespace strl
{

class OpenGLShader : public STRLManagedItemBase
{
public:
	using STRLManagedItemBase::STRLManagedItemBase;
	~OpenGLShader();
	void bind() const;
	void load();
	bool load(
		std::string_view vertex_shader_path,
		std::string_view fragment_shader_path,
		std::string_view geometry_shader_path);

	// TODO: not this
	[[nodiscard]] int get_shader_program_id() const;

private:
	int shader_program_{};
	static unsigned int compile(std::string_view path, unsigned int type);
};

} // strl

#endif //OPENGLSHADER_H
