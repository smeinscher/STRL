//
// Created by Sterling on 2/8/2024.
//

#ifndef ISHADER_H
#define ISHADER_H

#include <string>

namespace strl
{

class IShader
{
public:
	virtual ~IShader() = 0;

	virtual void bind() = 0;
	virtual void load() = 0;
	virtual bool load(
		const std::string& vertex_shader_path,
		const std::string& fragment_shader_path,
		const std::string& geometry_shader_path) = 0;
};

} // strl

#endif //ISHADER_H
