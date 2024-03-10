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

void Opponent::on_update()
{
	float velocity{0.0f};
	if (ball_->get_position().y - 10.0f > object_->get_position().y)
	{
		velocity = 1.0f;
	}
	else if (ball_->get_position().y + 10.0f < object_->get_position().y)
	{
		velocity = -1.0f;
	}

	object_->move_position_y(velocity * speed_);

	if (object_->get_position().y > 600.0f - object_->get_size().y / 2.0f)
	{
		object_->set_position_y(600.0f - object_->get_size().y / 2.0f);
	}
	else if (object_->get_position().y < 0.0f + object_->get_size().y / 2.0f)
	{
		object_->set_position_y(0.0f + object_->get_size().y / 2.0f);
	}
	body_->SetTransform({body_->GetPosition().x, object_->get_position().y * strl::PHYSICS_SCALE},
		body_->GetAngle());
}
