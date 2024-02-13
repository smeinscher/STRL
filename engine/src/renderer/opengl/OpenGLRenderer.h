//
// Created by Sterling on 2/7/2024.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "../IRenderer.h"
#include <glad/glad.h>

namespace strl
{

// RenderGroup's design assumes every Vertex Buffer Object needed is associated with a single Vertex Array Object
// This is useful for rendering multiple objects in one draw call
struct RenderGroup
{
	int index;
	GLuint vao;
	std::vector<GLuint> vbos;
	std::vector<unsigned int> cached_buffer_sizes;
};

class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer() override;

	void clear() override;

	void setup_render_data(STRLObjectRenderData& render_data) override;

	// We only want to worry about VertexDataTypes that we need
	// For example, we might want position and color in the vertex data, but not texture coordinates (uvs)
	template <VDType... TYPES>
	void setup_render_data(STRLObjectRenderData& render_data, TYPES... args);

	// Updates the vertex data based on which VertexDataType it is
	void update_vertex_data(STRLObjectRenderData& render_data) override;

	void render() override;

private:
	std::vector<RenderGroup> render_groups_;

	static void setup_vertices(STRLObjectRenderData& render_data, const std::vector<GLuint>& vbos);
};

} // strl


#endif //OPENGLRENDERER_H
