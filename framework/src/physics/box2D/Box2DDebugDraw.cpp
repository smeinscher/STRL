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
	std::vector<glm::vec3> glm_vertices;
	for (int i = 0; i < vertexCount; i++)
	{
		glm_vertices.emplace_back(vertices[i].x / 0.1f, vertices[i].y / 0.1f, 0.0f);
	}
	std::vector<float> triangulated_vertices = RenderConversions::triangulated_polygon(glm_vertices);
	std::vector<float>& positions = render_data_.get_positions();
	positions.insert(positions.end(), triangulated_vertices.begin(), triangulated_vertices.end());
	render_data_.set_positions_updated(true);
	std::vector<float>& colors = render_data_.get_colors();
	for (int i = 0; i < triangulated_vertices.size() / 3; i++)
	{
		colors.emplace_back(color.r);
		colors.emplace_back(color.g);
		colors.emplace_back(color.b);
		colors.emplace_back(color.a);
	}
	render_data_.set_colors_updated(true);
}

void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{

}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{

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