//
// Created by SterlingMeinscher on 2/20/2024.
//

#include "Opponent.h"

Opponent::Opponent(strl::STRLObject* paddle,
	strl::STRLObject* ball,
	strl::Box2DPhysics* physics,
	strl::Box2DPhysicsDefinitions definitions)
	: strl::Physics2DBase(paddle, physics, definitions), ball_(ball)
{

}

void Opponent::on_create()
{
	body_ = physics_->generate_default_body(object_);
}

void Opponent::on_update()
{
	if (ball_->get_position().y - 1.0f > object_->get_position().y)
	{
		body_->SetLinearVelocity({0.0f, 0.3f});
	}
	else if (ball_->get_position().y + 1.0f < object_->get_position().y)
	{
		body_->SetLinearVelocity({0.0f, -0.3f});
	}
	else
	{
		body_->SetLinearVelocity({0.0f, 0.0f});
	}

	object_->set_position_y(body_->GetPosition().y / strl::PHYSICS_SCALE);
	if (object_->get_position().y > 8.0f - object_->get_size().y / 2.0f)
	{
		object_->set_position_y(8.0f - object_->get_size().y / 2.0f);
		body_->SetTransform({body_->GetPosition().x, object_->get_position().y * strl::PHYSICS_SCALE},
			body_->GetAngle());
	}
	else if (object_->get_position().y < -8.0f + object_->get_size().y / 2.0f)
	{
		object_->set_position_y(-8.0f + object_->get_size().y / 2.0f);
		body_->SetTransform({body_->GetPosition().x, object_->get_position().y * strl::PHYSICS_SCALE},
			body_->GetAngle());
	}
}
