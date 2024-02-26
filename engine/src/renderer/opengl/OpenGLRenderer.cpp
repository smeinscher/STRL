//
// Created by Sterling on 2/7/2024.
//

#include <glad/glad.h>
#include <array>

#include "OpenGLRenderer.h"

namespace strl
{

OpenGLRenderer::OpenGLRenderer() = default;

OpenGLRenderer::~OpenGLRenderer() = default;

void OpenGLRenderer::clear()
{
	glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_STENCIL_BUFFER_BIT*/);
}

void OpenGLRenderer::set_clear_color(glm::vec4 color)
{
	clear_color_ = color;
}

void OpenGLRenderer::setup_render_data(OpenGLRenderData& render_data)
{
	setup_render_data(render_data, VertexDataType::POSITION, VertexDataType::UV, VertexDataType::COLOR);
}

template <VDType... TYPES>
void OpenGLRenderer::setup_render_data(OpenGLRenderData& render_data, TYPES... args)
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	render_data.set_vao(vao);

	std::vector<GLuint> vbos;
	vbos.resize(static_cast<unsigned int>(VertexDataType::LAST_VERTEX_DATA_TYPE), 0);
	std::array<VertexDataType, sizeof ...(TYPES)> types = {{args ...}};
	for (VertexDataType type : types)
	{
		glGenBuffers(1, &vbos[static_cast<unsigned int>(type)]);
	}
	render_data.set_vbos(vbos);
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	render_data.set_ebo(ebo);
	setup_vertices(render_data);
}

void OpenGLRenderer::update_vertex_data(OpenGLRenderData& render_data, VertexDataType type)
{
	std::vector<float> vertices;
	switch (type)
	{
	case VertexDataType::POSITION:
		vertices = render_data.get_positions();
		break;
	case VertexDataType::UV:
		vertices = render_data.get_uvs();
		break;
	case VertexDataType::COLOR:
		vertices = render_data.get_colors();
		break;
	default:
		break;
	}
	// TODO: track when each buffer is updated, only update if necessary
	if (!vertices.empty())
	{
		auto index = static_cast<int>(type);
		glBindBuffer(GL_ARRAY_BUFFER, render_data.get_vbo(index));
		// TODO: track size changes in buffer
		if (render_data.get_last_update_size(index) == vertices.size())
		{
			glBufferSubData(GL_ARRAY_BUFFER, 0,
				static_cast<GLsizeiptr>(vertices.size() * sizeof(float)), vertices.data());
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER,
				static_cast<GLsizeiptr>(vertices.size() * sizeof(float)), vertices.data(),
				GL_DYNAMIC_DRAW);
			render_data.set_last_update_size(index, static_cast<int>(vertices.size()));
		}
	}
}

void OpenGLRenderer::update_index_data(OpenGLRenderData& render_data)
{
	std::vector<int> indices = render_data.get_indices();
	if (!indices.empty())
	{
		auto index = static_cast<int>(VertexDataType::LAST_VERTEX_DATA_TYPE);
		int prev_size = render_data.get_last_update_size(index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_data.get_ebo());
		if (prev_size == indices.size())
		{
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
				static_cast<GLsizeiptr>(indices.size() * sizeof(int)), indices.data());
		}
		else
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, render_data.get_indices().size() * sizeof(int),
				render_data.get_indices().data(), GL_DYNAMIC_DRAW);
			render_data.set_last_update_size(index, static_cast<int>(indices.size()));
		}
	}
}

void OpenGLRenderer::render(OpenGLRenderData& render_data)
{
	if (render_data.has_positions_updated())
	{
		update_vertex_data(render_data, VertexDataType::POSITION);
		render_data.set_positions_updated(false);
	}
	if (render_data.has_uvs_updated())
	{
		update_vertex_data(render_data, VertexDataType::UV);
		render_data.set_uvs_updated(false);
	}
	if (render_data.has_colors_updated())
	{
		update_vertex_data(render_data, VertexDataType::COLOR);
		render_data.set_colors_updated(false);
	}
	if (render_data.has_indices_updated())
	{
		update_index_data(render_data);
		render_data.set_indices_updated(false);
	}

	if (render_data.get_texture() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		render_data.get_texture()->bind();
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBindVertexArray(render_data.get_vao());
	/*glDrawArrays(GL_TRIANGLES, 0,
	static_cast<GLsizei>(render_data.get_last_update_size(
		static_cast<unsigned int>(VertexDataType::POSITION)) / 3))*/;
	glDrawElements(GL_TRIANGLES, render_data.get_indices().size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void OpenGLRenderer::setup_vertices(OpenGLRenderData& render_data)
{
	for (int i = 0; i < static_cast<int>(VertexDataType::LAST_VERTEX_DATA_TYPE); i++)
	{
		if (render_data.get_vbo(i) == 0)
		{
			continue;
		}
		glBindBuffer(GL_ARRAY_BUFFER, render_data.get_vbo(i));
		switch (static_cast<VertexDataType>(i))
		{
		case VertexDataType::POSITION:
			glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(render_data.get_positions().size() * sizeof(float)),
				render_data.get_positions().data(), GL_DYNAMIC_DRAW);
			glVertexAttribPointer(i, STRL_POSITION_VERTEX_SIZE, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			break;
		case VertexDataType::UV:
			glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(render_data.get_uvs().size() * sizeof(float)),
				render_data.get_uvs().data(), GL_DYNAMIC_DRAW);
			glVertexAttribPointer(i, STRL_UV_VERTEX_SIZE, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			break;
		case VertexDataType::COLOR:
			glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(render_data.get_colors().size() * sizeof(float)),
				render_data.get_colors().data(), GL_DYNAMIC_DRAW);
			glVertexAttribPointer(i, STRL_COLOR_VERTEX_SIZE, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
			break;
		case VertexDataType::LAST_VERTEX_DATA_TYPE:
			break;
		}
		glEnableVertexAttribArray(i);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_data.get_ebo());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, render_data.get_indices().size(),
		render_data.get_indices().data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

} // strl
