//
// Created by Sterling on 2/7/2024.
//

#ifndef IRENDERER_H
#define IRENDERER_H

#include <glm/glm.hpp>
#include <vector>
#include "opengl/OpenGLRenderData.h"
#include "opengl/OpenGLRenderDataManager.h"

namespace strl
{

// enum class for possible types of vertex attributes (used in vertex shader)
enum class VertexDataType
{
	POSITION,
	UV,
	COLOR,
	LAST_VERTEX_DATA_TYPE
};

// useful for parameter packing what vertex data types we need, enforces the VertexDataType type
template <typename T>
concept VDType = std::is_same<T, VertexDataType>::value;

// Interface class, just in case we want a different render API in the future (Vulkan?)
template <typename RENDER_DATA_TYPE>
class IRenderer
{
public:
	virtual ~IRenderer() = default;

	virtual void clear() = 0;
	virtual void set_clear_color(glm::vec4 color) = 0;
	virtual void setup_render_data(RENDER_DATA_TYPE& render_data) = 0;
	virtual void update_vertex_data(RENDER_DATA_TYPE& render_data, VertexDataType type) = 0;
	virtual void update_index_data(RENDER_DATA_TYPE& render_data) = 0;

	virtual void render(RENDER_DATA_TYPE& render_data) = 0;

};

} // strl

#endif //IRENDERER_H
