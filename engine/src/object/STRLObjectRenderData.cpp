//
// Created by Sterling on 2/9/2024.
//

#include "STRLObjectRenderData.h"
#include "../renderer/IRenderer.h"
#include "../util/algorithm/Triangulation.h"

namespace strl
{

STRLObjectRenderData::STRLObjectRenderData(IRenderer* renderer)
	: renderer_(renderer) {}

STRLObjectRenderData::~STRLObjectRenderData() = default;

int STRLObjectRenderData::get_render_group_index() const
{
	return render_group_index_;
}

void STRLObjectRenderData::set_render_group_index(int render_group_index)
{
	render_group_index_ = render_group_index;
}

std::vector<float>& STRLObjectRenderData::get_positions()
{
	return positions_;
}

void STRLObjectRenderData::set_positions(const std::vector<float>& positions)
{
	positions_ = positions;
}

std::vector<float>& STRLObjectRenderData::get_uvs()
{
	return uvs_;
}

void STRLObjectRenderData::set_uvs(const std::vector<float>& uvs)
{
	uvs_ = uvs;
}

std::vector<float>& STRLObjectRenderData::get_colors()
{
	return colors_;
}

void STRLObjectRenderData::set_colors(const std::vector<float>& colors)
{
	colors_ = colors;
}

void STRLObjectRenderData::add_renderer(IRenderer* renderer)
{
	renderer_ = renderer;
	renderer_->setup_render_data(*this);
}

void STRLObjectRenderData::publish()
{
	renderer_->update_vertex_data(*this);
}

void STRLObjectRenderData::update(const STRLObjectMessage& message)
{
	switch (message.update_type)
	{
	case STRLObjectMessage::POSITION:
	case STRLObjectMessage::SIZE:
	case STRLObjectMessage::ROTATION:
	case STRLObjectMessage::POINTS:
		update_positions(message.object);
		break;
	case STRLObjectMessage::COLOR:
		update_colors(message.object);
		break;
	}
}

void STRLObjectRenderData::update_positions(STRLObject* object)
{
	auto adjusted_points = object->get_adjusted_points();

	auto triangulated_shape = Triangulation::triangulated_polygon(adjusted_points);
	size_t old_position_size = positions_.size();

	if (positions_.size() > object->get_render_data_index() + triangulated_shape.size())
	{
		positions_.erase(positions_.begin() + object->get_render_data_index() * 3,
			positions_.begin() + object->get_render_data_index() * 3 + triangulated_shape.size());
	}
	positions_.insert(positions_.begin() + object->get_render_data_index() * 3, triangulated_shape.begin(),
		triangulated_shape.end());

	if (positions_.size() != old_position_size)
	{
		update_uvs(object);
		update_colors(object);
	}
	else
	{
		// TODO: call this somewhere else
		publish();
	}
}

void STRLObjectRenderData::update_uvs(STRLObject* object)
{
	// TODO: maybe later
}

void STRLObjectRenderData::update_colors(STRLObject* object)
{
	// TODO: not this
	auto triangulated_shape = Triangulation::triangulated_polygon(object->get_adjusted_points());
	if (!colors_.empty())
	{
		colors_.erase(colors_.begin() + object->get_render_data_index() * 4,
			colors_.begin() + object->get_render_data_index() * 4 + triangulated_shape.size() / 3 * 4);
	}
	for (int i = 0; i < triangulated_shape.size() / 3 * 4; i++)
	{
		std::vector<float> color_vertices{object->get_color().r, object->get_color().g,
		                                  object->get_color().b, object->get_color().a};
		colors_.insert(colors_.begin() + (object->get_render_data_index() + i) * 4,
			color_vertices.begin(), color_vertices.end());
	}

	// TODO: call this somewhere else
	publish();
}

} // strl