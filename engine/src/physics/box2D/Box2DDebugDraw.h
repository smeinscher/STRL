//
// Created by SterlingMeinscher on 2/19/2024.
//

#ifndef BOX2DDEBUGDRAW_H
#define BOX2DDEBUGDRAW_H

#include <box2d/b2_draw.h>
#include "../../renderer/opengl/OpenGLRenderDataManager.h"
#include "../../renderer/opengl/OpenGLRenderData.h"

namespace strl
{

class Box2DDebugDraw : public b2Draw
{
public:
	explicit Box2DDebugDraw(OpenGLRenderData& render_data);
	~Box2DDebugDraw() override;
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	void DrawTransform(const b2Transform& xf) override;
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;

	OpenGLRenderData& get_render_data();

private:
	OpenGLRenderData& render_data_;
};

} // strl

#endif //BOX2DDEBUGDRAW_H
