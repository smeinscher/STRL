//
// Created by Sterling on 2/7/2024.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "OpenGLRenderData.h"

namespace strl
{

class OpenGLRenderer
{
public:
	static void set_platform_exists_flag(bool platform_exists);
	static void init(int viewport_width, int viewport_height);
	static void set_viewport_width_and_height(int viewport_width, int viewport_height);

	static void clear(float r, float g, float b, float a);

	static void setup_render_data(OpenGLRenderData& render_data);

	// We only want to worry about VertexDataTypes that we need
	// For example, we might want position and color in the vertex data, but not texture coordinates (uvs)
	template <VDType... TYPES>
	static void setup_render_data(OpenGLRenderData& render_data, TYPES... args);

	// Updates the vertex data based on which VertexDataType it is
	static void update_vertex_data(OpenGLRenderData& render_data, VertexDataType type);
	static void update_index_data(OpenGLRenderData& render_data);

	static void remove_render_data_objects(OpenGLRenderData& render_data);

	static void render(OpenGLRenderData& render_data);

private:
	static bool platform_exists_;
	static void setup_vertices(OpenGLRenderData& render_data);
};

} // strl


#endif //OPENGLRENDERER_H
