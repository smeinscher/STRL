//
// Created by Sterling on 2/7/2024.
//

#include <glad/glad.h>
#include <array>

#include "OpenGLRenderer.h"
#include "../../config/STRLConfig.h"

namespace strl
{

bool OpenGLRenderer::platform_exists_ = false;

void OpenGLRenderer::set_platform_exists_flag(bool platform_exists)
{
	platform_exists_ = platform_exists;
}

void OpenGLRenderer::init(int viewport_width, int viewport_height)
{
	if (!platform_exists_)
	{
		// TODO: logging stuff
		std::cout << "Platform needs to be created/existing to init renderer" << std::endl;
		return;
	}
	set_viewport_width_and_height(viewport_width, viewport_height);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);*/

}

void OpenGLRenderer::set_viewport_width_and_height(int viewport_width, int viewport_height)
{
	if (!platform_exists_)
	{
		return;
	}
	glViewport(0, 0, viewport_width, viewport_height);
}

void OpenGLRenderer::clear(float r, float g, float b, float a)
{
	if (!platform_exists_)
	{
		return;
	}
	glClearColor(r, g, b, a);
	// TODO: keep track of if depth/stencil buffer is needed
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_STENCIL_BUFFER_BIT*/);
}

void OpenGLRenderer::setup_render_data(OpenGLRenderData& render_data)
{
	if (!platform_exists_)
	{
		return;
	}
	setup_render_data(render_data, VertexDataType::POSITION, VertexDataType::UV, VertexDataType::COLOR);
}

template <VDType... TYPES>
void OpenGLRenderer::setup_render_data(OpenGLRenderData& render_data, TYPES... args)
{
	if (!platform_exists_)
	{
		return;
	}
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
	if (!platform_exists_)
	{
		return;
	}
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
	if (!platform_exists_)
	{
		return;
	}
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

void OpenGLRenderer::remove_render_data_objects(OpenGLRenderData& render_data)
{
	if (!platform_exists_)
	{
		return;
	}
	glDeleteVertexArrays(1, &render_data.get_vao());
	render_data.set_vao(0);
	std::vector<unsigned int>& vbos = render_data.get_all_vbos();
	glDeleteBuffers(vbos.size(), vbos.data());
	vbos.clear();
	glDeleteBuffers(1, &render_data.get_ebo());
	render_data.set_ebo(0);
}

void OpenGLRenderer::render(OpenGLRenderData& render_data)
{
	if (!platform_exists_)
	{
		return;
	}
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
