//
// Created by SterlingMeinscher on 2/17/2024.
//

#include "STRLPlayerController.h"

namespace strl
{

STRLPlayerController::STRLPlayerController(STRLObject* object,
	STRLEventManager* event_manager,
	STRLKey up_key,
	STRLKey down_key,
	STRLKey left_key,
	STRLKey right_key,
	STRLPlane movement_plane)
	: object_(object), event_manager_(event_manager),
	  up_key_(up_key), down_key_(down_key),
	  left_key_(left_key), right_key_(right_key),
	  movement_plane_(movement_plane)
{

}

void STRLPlayerController::on_create()
{
	STRLEventListenerFunction up_pressed = [this](STRLEvent* event)
	{
		is_moving_up_ = true;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED, up_key_,
		up_pressed, "Player Controller Up Pressed");
	STRLEventListenerFunction up_released = [this](STRLEvent* event)
	{
		is_moving_up_ = false;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_RELEASED, up_key_,
		up_released, "Player Controller Up Released");

	STRLEventListenerFunction down_pressed = [this](STRLEvent* event)
	{
		is_moving_down_ = true;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED, down_key_,
		down_pressed, "Player Controller Down Pressed");
	STRLEventListenerFunction down_released = [this](STRLEvent* event)
	{
		is_moving_down_ = false;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_RELEASED, down_key_,
		down_released, "Player Controller Down Released");

	STRLEventListenerFunction left_pressed = [this](STRLEvent* event)
	{
		is_moving_left_ = true;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED, left_key_,
		left_pressed, "Player Controller Left Pressed");
	STRLEventListenerFunction left_released = [this](STRLEvent* event)
	{
		is_moving_left_ = false;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_RELEASED, left_key_,
		left_released, "Player Controller Left Released");

	STRLEventListenerFunction right_pressed = [this](STRLEvent* event)
	{
		is_moving_right_ = true;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED, right_key_,
		right_pressed, "Player Controller Right Pressed");
	STRLEventListenerFunction right_released = [this](STRLEvent* event)
	{
		is_moving_right_ = false;
	};
	event_manager_->register_event_listener(STRLEventType::STRL_EVENT_KEY_RELEASED, right_key_,
		right_released, "Player Controller Right Released");

}

void STRLPlayerController::on_update()
{
	if (is_moving_up_)
	{
		object_->move_position_y(0.1f);
	}
	if (is_moving_down_)
	{
		object_->move_position_y(-0.1f);
	}
	if (is_moving_left_)
	{
		object_->move_position_x(-0.1f);
	}
	if (is_moving_right_)
	{
		object_->move_position_x(0.01f);
	}
}

void STRLPlayerController::on_destroy()
{

}

} // strl