//
// Created by SterlingMeinscher on 2/19/2024.
//

#include "Box2DPhysics.h"

namespace strl
{

Box2DPhysics::Box2DPhysics(float gravity_x, float gravity_y, OpenGLRenderData& debug_draw_render_data)
{
	debug_draw_ = std::make_unique<Box2DDebugDraw>(debug_draw_render_data);
	// TODO: take in args to change this
	debug_draw_->SetFlags(b2Draw::e_shapeBit);
	contact_listener_ = std::make_unique<Box2DContactListener>();
	world_ = std::make_unique<b2World>(b2Vec2(gravity_x, gravity_y));
	world_->SetDebugDraw(debug_draw_.get());
	world_->SetContactListener(contact_listener_.get());
}

void Box2DPhysics::step(float time_step, int velocity_iterations, int position_iterations)
{
	world_->Step(time_step, velocity_iterations, position_iterations);
}

b2Body* Box2DPhysics::generate_default_body(STRLObject* object, std::function<void()>* script)
{
	b2BodyDef body_definition = strl::Box2DPhysics::generate_b2BodyDef(object, script);
	b2Body* body = create_body(body_definition);
	std::unique_ptr<b2Shape> shape = strl::Box2DPhysics::generate_b2Shape(object);
	b2FixtureDef fixture_definition = strl::Box2DPhysics::generate_b2FixtureDef(shape.get());
	strl::Box2DPhysics::create_fixture(body, fixture_definition);

	return body;
}

b2BodyDef Box2DPhysics::generate_b2BodyDef(STRLObject* object, std::function<void()>* script)
{
	b2BodyDef body_definition;
	body_definition.type = b2_dynamicBody;
	body_definition.position.Set(object->get_position().x * PHYSICS_SCALE,
		object->get_position().y * PHYSICS_SCALE);
	body_definition.angle = object->get_rotation().euler.z;
	body_definition.linearDamping = 0.0f;
	body_definition.angularDamping = 0.0f;
	body_definition.userData.pointer = reinterpret_cast<uintptr_t>(script);
	return body_definition;
}

b2Body* Box2DPhysics::create_body(b2BodyDef body_definition)
{
	return world_->CreateBody(&body_definition);
}

std::unique_ptr<b2Shape> Box2DPhysics::generate_b2Shape(STRLObject* object)
{
	std::vector<glm::vec3> points = object->get_adjusted_points();
	if (points.size() > 8)
	{
		std::unique_ptr<b2CircleShape> circle_shape = std::make_unique<b2CircleShape>();
		circle_shape->m_p = {object->get_position().x * PHYSICS_SCALE, object->get_position().y * PHYSICS_SCALE};
		circle_shape->m_radius =
			glm::length(points[0] - points[points.size() / 2]) / 2.0f * PHYSICS_SCALE;
		return circle_shape;
	}
	b2Vec2 b2_points[points.size()];
	for (int i = 0; i < points.size(); i++)
	{
		b2_points[i] = {(points[i].x - object->get_position().x) * PHYSICS_SCALE,
						(points[i].y - object->get_position().y) * PHYSICS_SCALE};
	}
	std::unique_ptr<b2PolygonShape> polygon_shape = std::make_unique<b2PolygonShape>();
	polygon_shape->Set(b2_points, static_cast<int>(points.size()));
	return polygon_shape;
}

b2FixtureDef Box2DPhysics::generate_b2FixtureDef(b2Shape* shape)
{
	b2FixtureDef fixture_definition;
	fixture_definition.shape = shape;
	fixture_definition.density = 1.0f;
	fixture_definition.friction = 0.5f;
	fixture_definition.restitution = 0.9f;
	return fixture_definition;
}

void Box2DPhysics::create_fixture(b2Body* body, b2FixtureDef fixture_definition)
{
	body->CreateFixture(&fixture_definition);
}

std::unique_ptr<b2World>& Box2DPhysics::get_world()
{
	return world_;
}

void Box2DPhysics::prep_debug_render()
{
	debug_draw_->get_render_data().get_positions().clear();
	debug_draw_->get_render_data().get_colors().clear();
	world_->DebugDraw();
}

} // strl