//
// Created by SterlingMeinscher on 2/19/2024.
//

#include "PongBall.h"

void PongBall::on_create()
{
	body_script_ = std::make_unique<std::function<void()>>([this]()
	{
		b2Vec2 velocity = body_->GetLinearVelocity();
		velocity.x *= strl::Random::get_random_float(-3.0f, -1.0f);
		velocity.y = strl::Random::get_random_float(-0.75f, 0.75f);
		velocity.Normalize();
		velocity *= 0.75;
		body_->SetLinearVelocity(velocity);
	});

	body_ = physics_->generate_default_body(object_, body_script_.get());

	body_->SetLinearVelocity({-0.5f, -0.5f});
}

void PongBall::on_update()
{
	b2Vec2 velocity = body_->GetLinearVelocity();
	if (body_->GetPosition().y > 8.0f * strl::PHYSICS_SCALE ||
		body_->GetPosition().y < -8.0f * strl::PHYSICS_SCALE)
	{
		velocity.y *= -1.0f;
		body_->SetTransform(
			{body_->GetPosition().x, (velocity.y > 0.0f ? -8.0f : 8.0f) * strl::PHYSICS_SCALE},
			body_->GetAngle());
		velocity.Normalize();
		velocity *= 0.75;
		body_->SetLinearVelocity(velocity);
	}
	if (body_->GetPosition().x > 11.0f * strl::PHYSICS_SCALE ||
		body_->GetPosition().x < -11.0f * strl::PHYSICS_SCALE)
	{
		body_->SetTransform(
			{0.0f, 0.0f}, body_->GetAngle());
		velocity.x *= strl::Random::get_random_float(-3.0f, -1.0f);
		velocity.y = strl::Random::get_random_float(-0.75f, 0.75f);
		velocity.Normalize();
		velocity *= 0.75;
		body_->SetLinearVelocity(velocity);
	}

	b2Vec2 position = body_->GetPosition();
	object_->set_position_x(position.x / strl::PHYSICS_SCALE);
	object_->set_position_y(position.y / strl::PHYSICS_SCALE);
}