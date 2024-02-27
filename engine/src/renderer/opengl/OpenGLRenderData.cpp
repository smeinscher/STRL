//
// Created by Sterling on 2/9/2024.
//

#include "OpenGLRenderData.h"
#include "../../util/algorithm/RenderConversions.h"
#include "strl-config.h"
#include "../IRenderer.h"

namespace strl
{

OpenGLRenderData::OpenGLRenderData(std::string name, std::vector<std::string> tags)
	: STRLManagedItemBase(std::move(name), std::move(tags))
{
	last_updated_size_.resize(static_cast<int>(VertexDataType::LAST_VERTEX_DATA_TYPE) + 1, 0);
}

OpenGLRenderData::~OpenGLRenderData()
{
	if (vao_ != 0 || !vbos_.empty() || ebo_ != 0)
	{
		// TODO: logging stuff
		std::cout << "Destroying render data before OpenGL cleanup" << std::endl;
	}

}

std::vector<float>& OpenGLRenderData::get_positions()
{
	return positions_;
}

void OpenGLRenderData::set_positions(const std::vector<float>& positions)
{
	positions_ = positions;
}

std::vector<float>& OpenGLRenderData::get_uvs()
{
	return uvs_;
}

void OpenGLRenderData::set_uvs(const std::vector<float>& uvs)
{
	uvs_ = uvs;
}

std::vector<float>& OpenGLRenderData::get_colors()
{
	return colors_;
}

void OpenGLRenderData::set_colors(const std::vector<float>& colors)
{
	colors_ = colors;
}

std::vector<int>& OpenGLRenderData::get_indices()
{
	return indices_;
}

void OpenGLRenderData::set_indices(const std::vector<int>& indices)
{
	indices_ = indices;
}

void OpenGLRenderData::update_positions(STRLObject* object)
{
	if (object->get_render_data_positions_location() == -1)
	{
		object->set_render_data_position_location(positions_.size());
	}

	auto float_points = get_float_points(object);

	if (positions_.size() >= object->get_render_data_positions_location() + float_points.size())
	{
		positions_.erase(positions_.begin() + object->get_render_data_positions_location(),
			positions_.begin() + object->get_render_data_positions_location() + float_points.size());
	}
	else
	{
		object->set_render_data_position_location(positions_.size());
	}
	positions_.insert(positions_.begin() + object->get_render_data_positions_location(), float_points.begin(),
		float_points.end());

	positions_updated_ = true;
}

void OpenGLRenderData::update_uvs(STRLObject* object)
{
	if (texture_ == nullptr)
	{
		return;
	}
	auto float_points = get_float_points(object);
	int index = object->get_render_data_positions_location() / STRL_POSITION_VERTEX_SIZE * STRL_UV_VERTEX_SIZE;
	int last_index = index + static_cast<int>(float_points.size()) / STRL_POSITION_VERTEX_SIZE * STRL_UV_VERTEX_SIZE;
	if (uvs_.size() >= last_index)
	{
		uvs_.erase(uvs_.begin() + index, uvs_.begin() + last_index);
	}
	for (int i = 0; i < (last_index - index) / 2; i++)
	{
		std::vector<float> uv_vertex{object->get_uv()[i].x, object->get_uv()[i].y};
		uvs_.insert(uvs_.begin() + index + i * 2, uv_vertex.begin(), uv_vertex.end());
	}
}

void OpenGLRenderData::update_colors(STRLObject* object)
{
	auto float_points = get_float_points(object);
	int index = object->get_render_data_positions_location() / STRL_POSITION_VERTEX_SIZE * STRL_COLOR_VERTEX_SIZE;
	int last_index = index + static_cast<int>(float_points.size()) / STRL_POSITION_VERTEX_SIZE * STRL_COLOR_VERTEX_SIZE;
	if (colors_.size() >= last_index)
	{
		colors_.erase(colors_.begin() + index,
			colors_.begin() + last_index);
	}
	for (int i = index / STRL_COLOR_VERTEX_SIZE; i < last_index / STRL_COLOR_VERTEX_SIZE; i++)
	{
		std::vector<float> color_vertices{object->get_color().r, object->get_color().g,
		                                  object->get_color().b, object->get_color().a};
		colors_.insert(colors_.begin() + i * STRL_COLOR_VERTEX_SIZE,
			color_vertices.begin(), color_vertices.end());
	}

	colors_updated_ = true;
}

void OpenGLRenderData::update_indices(STRLObject* object)
{
	if (object->get_render_data_indices_location() == -1)
	{
		object->set_render_data_indices_location(indices_.size());
	}

	std::vector<int> object_indices = get_object_indices(object);

	for (auto& index : object_indices)
	{
		index += object->get_render_data_positions_location() / STRL_POSITION_VERTEX_SIZE;
	}

	if (indices_.size() >= object->get_render_data_indices_location() + object_indices.size())
	{
		indices_.erase(indices_.begin() + object->get_render_data_indices_location(),
			indices_.begin() + object->get_render_data_indices_location() + object_indices.size());
	}
	indices_.insert(indices_.begin() + object->get_render_data_indices_location(),
		object_indices.begin(), object_indices.end());

	indices_updated_ = true;
}

void OpenGLRenderData::add_points(STRLObject* updated_object, int points_added, std::vector<STRLObject*>& objects)
{
	int indices_added = points_added != updated_object->get_points().size()
	                    ? points_added * 3
	                    : (updated_object->get_points().size() - 2) * 3;
	if (updated_object->get_face_count() == 1)
	{
		updated_position_index_and_count_.emplace_back(
			updated_object->get_render_data_positions_location(), points_added * 3);
		updated_indices_index_and_count_.emplace_back(
			updated_object->get_render_data_indices_location(), indices_added);
	}
	else
	{
		updated_position_index_and_count_.emplace_back(
			updated_object->get_render_data_positions_location(), points_added * 3);
		updated_indices_index_and_count_.emplace_back(
			updated_object->get_render_data_indices_location(), indices_added * 2);
	}
	update_locations(objects);
	for (auto object : objects)
	{
		update_indices(object);
		update_positions(object);
		update_uvs(object);
		update_colors(object);
	}

}

void OpenGLRenderData::remove(STRLObject* remove_object, std::vector<STRLObject*>& objects)
{
	auto float_points = get_float_points(remove_object);
	int index = remove_object->get_render_data_positions_location();
	int last_index = index + static_cast<int>(float_points.size());
	// TODO: remove these checks as they might be useless
	if (positions_.size() >= last_index)
	{
		updated_position_index_and_count_.emplace_back(index, -(last_index - index));
		positions_.erase(positions_.begin() + index, positions_.begin() + last_index);
	}
	index = remove_object->get_render_data_positions_location() / STRL_POSITION_VERTEX_SIZE * STRL_UV_VERTEX_SIZE;
	last_index = index + static_cast<int>(float_points.size()) / STRL_POSITION_VERTEX_SIZE * STRL_UV_VERTEX_SIZE;
	if (uvs_.size() >= last_index)
	{
		uvs_.erase(uvs_.begin() + index, uvs_.begin() + last_index);
	}
	index = remove_object->get_render_data_positions_location() / STRL_POSITION_VERTEX_SIZE * STRL_COLOR_VERTEX_SIZE;
	last_index = index + static_cast<int>(float_points.size()) / STRL_POSITION_VERTEX_SIZE * STRL_COLOR_VERTEX_SIZE;
	if (colors_.size() >= last_index)
	{
		colors_.erase(colors_.begin() + index, colors_.begin() + last_index);
	}
	index = remove_object->get_render_data_indices_location();
	last_index = index + static_cast<int>(get_object_indices(remove_object).size());
	if (indices_.size() >= last_index)
	{
		updated_indices_index_and_count_.emplace_back(index, -(last_index - index));
		indices_.erase(indices_.begin() + index, indices_.begin() + last_index);
	}
	remove_object->set_render_data_position_location(-1);
	remove_object->set_render_data_indices_location(-1);
	update_locations(objects);
	for (auto object : objects)
	{
		if (object == remove_object)
		{
			continue;
		}
		update_indices(object);
		update_positions(object);
		update_uvs(object);
		update_colors(object);
	}
}

void OpenGLRenderData::update_locations(std::vector<STRLObject*>& objects)
{
	for (auto& object: objects)
	{
		for (auto& index_and_count : updated_position_index_and_count_)
		{
			if (object->get_render_data_positions_location() > index_and_count.first)
			{
				object->move_render_data_position_location(index_and_count.second);
			}
		}

		for (auto& index_and_count : updated_indices_index_and_count_)
		{
			if (object->get_render_data_indices_location() > index_and_count.first)
			{
				object->move_render_data_indices_location(index_and_count.second);
			}
		}
	}
	updated_position_index_and_count_.clear();
	updated_indices_index_and_count_.clear();
}

bool OpenGLRenderData::has_positions_updated() const
{
	return positions_updated_;
}

void OpenGLRenderData::set_positions_updated(bool positions_updated)
{
	positions_updated_ = positions_updated;
}

bool OpenGLRenderData::has_uvs_updated() const
{
	return uvs_updated_;
}

void OpenGLRenderData::set_uvs_updated(bool uvs_updated)
{
	uvs_updated_ = uvs_updated;
}

bool OpenGLRenderData::has_colors_updated() const
{
	return colors_updated_;
}

void OpenGLRenderData::set_colors_updated(bool colors_updated)
{
	colors_updated_ = colors_updated;
}

bool OpenGLRenderData::has_indices_updated() const
{
	return indices_updated_;
}

void OpenGLRenderData::set_indices_updated(bool indices_updated)
{
	indices_updated_ = indices_updated;
}

unsigned int& OpenGLRenderData::get_vao()
{
	return vao_;
}

void OpenGLRenderData::set_vao(unsigned int vao)
{
	vao_ = vao;
}

unsigned int& OpenGLRenderData::get_vbo(int index)
{
	return vbos_[index];
}

std::vector<unsigned int>& OpenGLRenderData::get_all_vbos()
{
	return vbos_;
}

void OpenGLRenderData::set_vbo(int index, unsigned int vbo)
{
	vbos_[index] = vbo;
}

void OpenGLRenderData::set_vbos(std::vector<unsigned int> vbos)
{
	vbos_ = std::move(vbos);
}

unsigned int& OpenGLRenderData::get_ebo()
{
	return ebo_;
}

void OpenGLRenderData::set_ebo(unsigned int ebo)
{
	ebo_ = ebo;
}

int OpenGLRenderData::get_last_update_size(int index)
{
	return last_updated_size_[index];
}

void OpenGLRenderData::set_last_update_size(int index, int size)
{
	last_updated_size_[index] = size;
}

std::unique_ptr<OpenGLTexture>& OpenGLRenderData::get_texture()
{
	return texture_;
}

void OpenGLRenderData::set_texture(std::unique_ptr<OpenGLTexture>& texture)
{
	texture_ = std::move(texture);
}

void OpenGLRenderData::create_texture(const std::string& path)
{
	texture_ = std::make_unique<OpenGLTexture>();
	bool success = texture_->generate(
		!path.empty()
		? path
		: std::format("{}/{}", ENGINE_DIRECTORY_LOCATION, "resources/textures/default_texture.png"));

	if (!success)
	{
		// TODO: logging stuff
		std::cout << "Applying error texture" << std::endl;
		texture_->generate(
			std::format("{}/{}", ENGINE_DIRECTORY_LOCATION, "resources/textures/error_texture.png"));
	}

}

int OpenGLRenderData::get_last_object_index() const
{
	return last_object_index_;
}

void OpenGLRenderData::set_last_object_index(int object_index)
{
	last_object_index_ = object_index;
}

std::pair<int, int> OpenGLRenderData::get_min_max_indices(STRLObject* object)
{
	std::vector<int> object_indices = get_object_indices(object);
	int min_index = INT32_MAX;
	int max_index = 0;
	for (auto index : object_indices)
	{
		index += object->get_render_data_index();
		if (index < min_index)
		{
			min_index = index;
		}
		else if (index > max_index)
		{
			max_index = index;
		}
	}

	return {min_index, max_index};
}

std::vector<int> OpenGLRenderData::get_object_indices(STRLObject* object)
{
	std::vector<int> object_indices;
	if (object->get_face_count() == 1)
	{
		object_indices = RenderConversions::generate_polygon_indices(object->get_adjusted_points());
	}
	else if (texture_ != nullptr)
	{
		object_indices = RenderConversions::textured_cube_indices();
	}
	else
	{
		object_indices = RenderConversions::cube_indices();
	}
	return object_indices;
}

std::vector<float> OpenGLRenderData::get_float_points(STRLObject* object)
{
	std::vector<glm::vec3> adjusted_points;
	if (object->get_face_count() == 1 || texture_ == nullptr)
	{
		adjusted_points = object->get_adjusted_points();
	}
	else
	{
		adjusted_points = RenderConversions::points_for_textures(object->get_adjusted_points());
	}
	std::vector<float> float_points = RenderConversions::point_vec_to_float_vec(adjusted_points);

	return float_points;
}

} // strl