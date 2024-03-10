//
// Created by SterlingMeinscher on 2/19/2024.
//

#include "Box2DDebugDraw.h"
#include "../../util/algorithm/RenderConversions.h"

namespace strl
{

Box2DDebugDraw::Box2DDebugDraw(OpenGLRenderData& render_data)
	: render_data_(render_data)
{
}

Box2DDebugDraw::~Box2DDebugDraw() = default;

void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::vector<float>& positions = render_data_.get_positions();
	std::vector<glm::vec3> glm_vertices;
	for (int i = 0; i < vertexCount; i++)
	{
		positions.insert(positions.end(), {vertices[i].x / PHYSICS_SCALE, vertices[i].y / PHYSICS_SCALE, 0.0f});
		glm_vertices.emplace_back(vertices[i].x / PHYSICS_SCALE, vertices[i].y / PHYSICS_SCALE, 0.0f);
	}
	render_data_.set_positions_updated(true);

	std::vector<float>& colors = render_data_.get_colors();
	for (int i = 0; i < vertexCount; i++)
	{
		colors.emplace_back(color.r);
		colors.emplace_back(color.g);
		colors.emplace_back(color.b);
		colors.emplace_back(color.a);
	}
	render_data_.set_colors_updated(true);

	std::vector<int>& indices = render_data_.get_indices();
	std::vector<int> physics_object_indices = RenderConversions::generate_polygon_indices(glm_vertices);
	int start_index = !indices.empty() ? indices.back() + 1 : 0;
	for (auto& index : physics_object_indices)
	{
		index += start_index;
	}
	indices.insert(indices.end(), physics_object_indices.begin(), physics_object_indices.end());
}

void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{

}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	std::vector<float>& positions = render_data_.get_positions();
	std::vector<glm::vec3> glm_vertices;
	for (int i = 0; i < 32; i++)
	{
		float x = (center.x + radius * std::cos(static_cast<float>(i) * 2.0f * b2_pi / 32.0f)) / PHYSICS_SCALE;
		float y = (center.y + radius * std::sin(static_cast<float>(i) * 2.0f * b2_pi / 32.0f)) / PHYSICS_SCALE;
		positions.insert(positions.end(), {x, y, 0.0f});
		glm_vertices.emplace_back(x, y, 0.0f);
	}
	render_data_.set_positions_updated(true);

	std::vector<float>& colors = render_data_.get_colors();
	for (int i = 0; i < 32; i++)
	{
		colors.emplace_back(color.r);
		colors.emplace_back(color.g);
		colors.emplace_back(color.b);
		colors.emplace_back(color.a);
	}
	render_data_.set_colors_updated(true);

	std::vector<int>& indices = render_data_.get_indices();
	std::vector<int> physics_object_indices = RenderConversions::generate_polygon_indices(glm_vertices);
	int start_index = !indices.empty() ? indices.back() + 1 : 0;
	for (auto& index : physics_object_indices)
	{
		index += start_index;
	}
	indices.insert(indices.end(), physics_object_indices.begin(), physics_object_indices.end());
}

void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

}

void Box2DDebugDraw::DrawTransform(const b2Transform& xf)
{

}

void Box2DDebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{

}

OpenGLRenderData& Box2DDebugDraw::get_render_data()
{
	return render_data_;
}

} // strl