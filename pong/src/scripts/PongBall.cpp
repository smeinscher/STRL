//
// Created by SterlingMeinscher on 2/19/2024.
//

#include "PongBall.h"

void PongBall::on_create()
{
	body_script_ = std::make_unique<std::function<void()>>([this]()
	{
		b2Vec2 velocity = body_->GetLinearVelocity();
		// TODO: is this bad? It feels wrong
		do
		{
			velocity.x = strl::Random::get_random_float(-0.75f, 0.75f);
			velocity.y = strl::Random::get_random_float(-0.75f, 0.75f);
			velocity.Normalize();
		} while (abs(velocity.y) > 0.75);
		velocity *= speed_;
		body_->SetLinearVelocity(velocity);
	});

	body_ = physics_->generate_default_body(object_, body_script_.get());

	body_->SetLinearVelocity({-0.5f * speed_, -0.5f * speed_});
}

void PongBall::on_update()
{
	b2Vec2 velocity = body_->GetLinearVelocity();
	// TODO: get screen dimensions from somewhere
	if (body_->GetPosition().y > (600.0f - object_->get_size().y / 2.0f) * strl::PHYSICS_SCALE ||
		body_->GetPosition().y < (0.0f + object_->get_size().y / 2.0f) * strl::PHYSICS_SCALE)
	{
		velocity.y *= -1.0f;
		body_->SetTransform(
			{body_->GetPosition().x, (velocity.y > 0.0f ? 0.0f + object_->get_size().y / 2.0f : 600.0f - object_->get_size().y / 2.0f) * strl::PHYSICS_SCALE},
			body_->GetAngle());
		velocity.Normalize();
		velocity *= speed_;
		body_->SetLinearVelocity(velocity);
	}
	if (body_->GetPosition().x > (800.0f - object_->get_size().x) * strl::PHYSICS_SCALE ||
		body_->GetPosition().x < (0.0f + object_->get_size().x) * strl::PHYSICS_SCALE)
	{
		body_->SetTransform(
			{400.0f * strl::PHYSICS_SCALE, 300.0f * strl::PHYSICS_SCALE}, body_->GetAngle());
		velocity.x *= strl::Random::get_random_float(-3.0f, -1.0f);
		velocity.y = strl::Random::get_random_float(-speed_, speed_);
		velocity.Normalize();
		velocity *= speed_;
		body_->SetLinearVelocity(velocity);
	}

	b2Vec2 position = body_->GetPosition();
	object_->set_position_x(position.x / strl::PHYSICS_SCALE);
	object_->set_position_y(position.y / strl::PHYSICS_SCALE);
}