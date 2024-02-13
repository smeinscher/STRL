//
// Created by Sterling on 2/7/2024.
//

#ifndef IRENDERER_H
#define IRENDERER_H

#include <glm/glm.hpp>
#include <vector>
#include "../object/STRLObjectRenderData.h"

namespace strl
{

// enum class for possible types of vertex attributes (used in vertex shader)
enum class VertexDataType
{
	POSITION,
	UV,
	COLOR,
	END
};

// useful for parameter packing what vertex data types we need, enforces the VertexDataType type
template <typename T>
concept VDType = std::is_same<T, VertexDataType>::value;

// Interface class, just in case we want a different render API in the future (Vulkan?)
class IRenderer
{
public:
	virtual ~IRenderer();

	virtual void clear() = 0;

	virtual void setup_render_data(STRLObjectRenderData& render_data) = 0;

	virtual void update_vertex_data(STRLObjectRenderData& render_data) = 0;

	virtual void render() = 0;

protected:
	glm::vec4 clear_color_{
		0.5f,
		0.4f,
		0.7f,
		1.0f
	};
};

} // strl

#endif //IRENDERER_H
