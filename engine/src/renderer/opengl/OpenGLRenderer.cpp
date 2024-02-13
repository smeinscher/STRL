//
// Created by Sterling on 2/7/2024.
//

#include <glad/glad.h>
#include <algorithm>
#include <array>
#include <iostream>

#include "OpenGLRenderer.h"
namespace strl
{

OpenGLRenderer::OpenGLRenderer() = default;

OpenGLRenderer::~OpenGLRenderer() = default;

void OpenGLRenderer::clear()
{
	glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::setup_render_data(STRLObjectRenderData& render_data)
{
	setup_render_data(render_data, VertexDataType::POSITION, VertexDataType::UV, VertexDataType::COLOR);
}

template <VDType... TYPES>
void OpenGLRenderer::setup_render_data(STRLObjectRenderData& render_data, TYPES... args)
{
	int index = static_cast<int>(render_groups_.size());
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<GLuint> vbos;
	vbos.resize(static_cast<unsigned int>(VertexDataType::END), 0);
	std::array<VertexDataType, sizeof ...(TYPES)> types = {{args ...}};
	for (VertexDataType type : types)
	{
		glGenBuffers(1, &vbos[static_cast<unsigned int>(type)]);
	}
	setup_vertices(render_data, vbos);

	std::vector<unsigned int> cached_buffer_sizes;
	cached_buffer_sizes.resize(static_cast<int>(VertexDataType::END), 0);
	for (int i = 0; i < cached_buffer_sizes.size(); i++)
	{
		switch (static_cast<VertexDataType>(i))
		{
		case VertexDataType::POSITION:
			cached_buffer_sizes[i] = render_data.get_positions().size();
			break;
		case VertexDataType::UV:
			cached_buffer_sizes[i] = render_data.get_uvs().size();
			break;
		case VertexDataType::COLOR:
			cached_buffer_sizes[i] = render_data.get_colors().size();
			break;
		case VertexDataType::END:
			break;
		}
	}

	render_data.set_render_group_index(index);
	render_groups_.emplace_back(index, vao, std::move(vbos), std::move(cached_buffer_sizes));
}

void OpenGLRenderer::update_vertex_data(STRLObjectRenderData& render_data)
{
	auto pred = [render_data](const RenderGroup& render_group)
	{
		return render_data.get_render_group_index() == render_group.index;
	};
	auto it = std::find_if(render_groups_.begin(), render_groups_.end(), pred);
	if (it == render_groups_.end())
	{
		// TODO: figure out how to handle this
		// TODO: logging stuff
		std::cout << "Render data index not found in render groups" << std::endl;
		return;
	}
	auto& positions = render_data.get_positions();
	auto& uvs = render_data.get_uvs();
	auto& colors = render_data.get_colors();
	auto& render_group = *it;
	// TODO: track when each buffer is updated, only update if necessary
	if (!positions.empty())
	{
		auto index = static_cast<unsigned int>(VertexDataType::POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, render_group.vbos[index]);
		// TODO: track size changes in buffer
		if (render_group.cached_buffer_sizes[index] == positions.size())
		{
			glBufferSubData(GL_ARRAY_BUFFER, 0, positions.size() * sizeof(float), positions.data());
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_DYNAMIC_DRAW);
			render_group.cached_buffer_sizes[index] = positions.size();
		}
	}
	if (!uvs.empty())
	{
		auto index = static_cast<unsigned int>(VertexDataType::UV);
		glBindBuffer(GL_ARRAY_BUFFER, render_group.vbos[index]);
		// TODO: track size changes in buffer
		if (render_group.cached_buffer_sizes[index] == uvs.size())
		{
			glBufferSubData(GL_ARRAY_BUFFER, 0, uvs.size() * sizeof(float), uvs.data());
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_DYNAMIC_DRAW);
			render_group.cached_buffer_sizes[index] = uvs.size();
		}
	}
	if (!colors.empty())
	{
		auto index = static_cast<unsigned int>(VertexDataType::COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, render_group.vbos[index]);
		// TODO: track size changes in buffer
		if (render_group.cached_buffer_sizes[index] == colors.size())
		{
			glBufferSubData(GL_ARRAY_BUFFER, 0, colors.size() * sizeof(float), colors.data());
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_DYNAMIC_DRAW);
			render_group.cached_buffer_sizes[index] = colors.size();
		}
	}

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << err << std::endl;
	}

}

void OpenGLRenderer::render()
{
	for (const auto& group : render_groups_)
	{
		glBindVertexArray(group.vao);
		glDrawArrays(GL_TRIANGLES, 0,
			static_cast<GLsizei>(group.cached_buffer_sizes[static_cast<unsigned int>(VertexDataType::POSITION)]) / 3);
	}
	glBindVertexArray(0);
}

void OpenGLRenderer::setup_vertices(STRLObjectRenderData& render_data, const std::vector<GLuint>& vbos)
{
	for (int i = 0; i < vbos.size(); i++)
	{
		if (vbos[i] == 0)
		{
			continue;
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
		switch (static_cast<VertexDataType>(i))
		{
		case VertexDataType::POSITION:
			glBufferData(GL_ARRAY_BUFFER, render_data.get_positions().size() * sizeof(float),
				render_data.get_positions().data(), GL_DYNAMIC_DRAW);
			glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			break;
		case VertexDataType::UV:
			glBufferData(GL_ARRAY_BUFFER, render_data.get_uvs().size() * sizeof(float),
				render_data.get_uvs().data(), GL_DYNAMIC_DRAW);
			glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			break;
		case VertexDataType::COLOR:
			glBufferData(GL_ARRAY_BUFFER, render_data.get_colors().size() * sizeof(float),
				render_data.get_colors().data(), GL_DYNAMIC_DRAW);
			glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
			break;
		case VertexDataType::END:
			break;
		}
		glEnableVertexAttribArray(i);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

} // strl
