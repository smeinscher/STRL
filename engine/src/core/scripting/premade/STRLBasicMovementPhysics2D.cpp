//
// Created by SterlingMeinscher on 2/19/2024.
//

#include "STRLBasicMovementPhysics2D.h"

namespace strl
{

STRLBasicMovementPhysics2D::STRLBasicMovementPhysics2D(STRLObject* object,
	STRLEventManager* event_manager,
	Box2DPhysics* physics,
	STRLKey up_key,
	STRLKey down_key,
	STRLKey left_key,
	STRLKey right_key)
	: object_(object), event_manager_(event_manager), physics_(physics),
	up_key_(up_key), down_key_(down_key), left_key_(left_key), right_key_(right_key)
{

}

void STRLBasicMovementPhysics2D::on_create()
{
	STRLEventListenerFunction up_pressed = [this](STRLEvent* event)
	{
		is_moving_up_ = true;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED, up_key_,
		up_pressed, "Basic Movement Physics 2D Up Pressed");
	STRLEventListenerFunction up_released = [this](STRLEvent* event)
	{
		is_moving_up_ = false;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_RELEASED, up_key_,
		up_released, "Basic Movement Physics 2D Up Released");

	STRLEventListenerFunction down_pressed = [this](STRLEvent* event)
	{
		is_moving_down_ = true;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED, down_key_,
		down_pressed, "Basic Movement Physics 2D Down Pressed");
	STRLEventListenerFunction down_released = [this](STRLEvent* event)
	{
		is_moving_down_ = false;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_RELEASED, down_key_,
		down_released, "Basic Movement Physics 2D Down Released");

	STRLEventListenerFunction left_pressed = [this](STRLEvent* event)
	{
		is_moving_left_ = true;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED, left_key_,
		left_pressed, "Basic Movement Physics 2D Left Pressed");
	STRLEventListenerFunction left_released = [this](STRLEvent* event)
	{
		is_moving_left_ = false;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_RELEASED, left_key_,
		left_released, "Basic Movement Physics 2D Left Released");

	STRLEventListenerFunction right_pressed = [this](STRLEvent* event)
	{
		is_moving_right_ = true;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED, right_key_,
		right_pressed, "Basic Movement Physics 2D Right Pressed");
	STRLEventListenerFunction right_released = [this](STRLEvent* event)
	{
		is_moving_right_ = false;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_RELEASED, right_key_,
		right_released, "Basic Movement Physics 2D Right Released");

	body_script_ = std::make_unique<std::function<void()>>([this](){});

	b2BodyDef body_definition = Box2DPhysics::generate_b2BodyDef(object_, body_script_.get());

	body_definition.type = b2_staticBody;
	body_ = physics_->create_body(body_definition);
	std::unique_ptr<b2Shape> shape = Box2DPhysics::generate_b2Shape(object_);
	b2FixtureDef fixture_definition = Box2DPhysics::generate_b2FixtureDef(shape.get());
	Box2DPhysics::create_fixture(body_, fixture_definition);
}

void STRLBasicMovementPhysics2D::on_update()
{
	glm::vec2 velocity{0.0f, 0.0f};
	if (is_moving_up_)
	{
		velocity.y += 1.0f;
	}
	if (is_moving_down_)
	{
		velocity.y -= 1.0f;
	}
	if (is_moving_left_)
	{
		velocity.x -= 1.0f;
	}
	if (is_moving_right_)
	{
		velocity.x += 1.0f;
	}
	if (glm::length(velocity) != 0.0f)
	{
		velocity = glm::normalize(velocity);
	}
	object_->move_position_x(velocity.x * 0.1f);
	object_->move_position_y(velocity.y * 0.1f);
	body_->SetTransform(
		{object_->get_position().x * PHYSICS_SCALE, object_->get_position().y * PHYSICS_SCALE},
		body_->GetAngle());
}

void STRLBasicMovementPhysics2D::on_destroy()
{

}
} // strl