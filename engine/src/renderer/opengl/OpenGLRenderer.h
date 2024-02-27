//
// Created by Sterling on 2/7/2024.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "../IRenderer.h"
#include "OpenGLRenderData.h"

namespace strl
{

class OpenGLRenderer : public IRenderer<OpenGLRenderData>
{
public:
	OpenGLRenderer(int viewport_width, int viewport_height);
	~OpenGLRenderer() override;

	void clear() override;
	void set_clear_color(glm::vec4 color) override;

	void setup_render_data(OpenGLRenderData& render_data) override;

	// We only want to worry about VertexDataTypes that we need
	// For example, we might want position and color in the vertex data, but not texture coordinates (uvs)
	template <VDType... TYPES>
	void setup_render_data(OpenGLRenderData& render_data, TYPES... args);

	// Updates the vertex data based on which VertexDataType it is
	void update_vertex_data(OpenGLRenderData& render_data, VertexDataType type) override;
	void update_index_data(OpenGLRenderData& render_data) override;

	void remove_render_data_objects(OpenGLRenderData& render_data) override;

	void render(OpenGLRenderData& render_data) override;

private:
	glm::vec4 clear_color_{
		0.5f,
		0.4f,
		0.7f,
		1.0f
	};

	static void setup_vertices(OpenGLRenderData& render_data);
};

} // strl


#endif //OPENGLRENDERER_H
