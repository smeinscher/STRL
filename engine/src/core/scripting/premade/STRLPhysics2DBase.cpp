//
// Created by SterlingMeinscher on 2/19/2024.
//

#include "STRLPhysics2DBase.h"

#include <utility>

namespace strl
{

STRLPhysics2DBase::STRLPhysics2DBase(STRLObject* object,
	Box2DPhysics* physics,
	Box2DPhysicsDefinitions physics_definitions)
	: object_(object), physics_(physics), physics_definitions_(physics_definitions)
{

}

void STRLPhysics2DBase::on_create()
{
	body_ = physics_->create_body(physics_definitions_.body_definition);
	std::unique_ptr<b2Shape> shape = Box2DPhysics::generate_b2Shape(object_);
	Box2DPhysics::create_fixture(body_, physics_definitions_.fixture_definition);
}

void STRLPhysics2DBase::on_update()
{
	b2Vec2 position = body_->GetPosition();
	object_->set_position_x(position.x / PHYSICS_SCALE);
	object_->set_position_y(position.y / PHYSICS_SCALE);
}

void STRLPhysics2DBase::on_destroy()
{
	physics_->get_world()->DestroyBody(body_);
}

} // strl