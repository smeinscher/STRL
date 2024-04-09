//
// Created by Sterling on 4/7/2024.
//

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Unit.h"

Unit::Unit(strl::Object* object,
	strl::ObjectManager* object_manager,
	States* states,
	strl::Camera* camera,
	strl::Object* planet)
	: object_(object), object_manager_(object_manager), states_(states), start_position_(object->get_position()),
		camera_(camera), planet_(planet)
{

}

void Unit::on_create()
{

}

void Unit::on_update()
{
	if (states_->is_making_selection())
	{
		if (object_->get_position().x - object_->get_size().x / 2.0f < states_->get_selection_max_x() &&
			object_->get_position().x + object_->get_size().x / 2.0f > states_->get_selection_min_x() &&
			object_->get_position().y - object_->get_size().y / 2.0f < states_->get_selection_max_y() &&
			object_->get_position().y + object_->get_size().y / 2.0f > states_->get_selection_min_y())
		{
			is_selected_ = true;
			object_->set_color({0.2f, 0.5f, 0.2f, 1.0f});
		}
		else
		{
			is_selected_ = false;
			object_->set_color({0.2f, 0.7f, 0.2f, 1.0f});
		}
	}
	if (states_->is_moving_units() && is_selected_ && !has_processed_move_)
	{
		goal_positions_.emplace_back(states_->get_last_click_position());
		has_processed_move_ = true;
	}
	else if (!states_->is_moving_units() || !is_selected_)
	{
		has_processed_move_ = false;
	}

	if (!goal_positions_.empty() && distance_to_goal_ < 1.0f)
	{
		float rotation_speed = 0.01f;
		distance_to_goal_ += rotation_speed / glm::length(goal_positions_[0] - start_position_);
		glm::vec3 current = glm::normalize(start_position_ - planet_->get_position());
		glm::vec3 desired = glm::normalize(goal_positions_[0] - planet_->get_position());
		auto current_quat = glm::quat(0.0f, current);
		float rotation_angle = acos(glm::dot(current, desired));
		glm::vec3 rotation_axis = glm::normalize(glm::cross(current, desired));

		glm::quat rotation = glm::angleAxis(rotation_angle * distance_to_goal_, rotation_axis);

		glm::vec3 position = glm::rotate(rotation, current) * glm::length(
			goal_positions_[0] - planet_->get_position()) + planet_->get_position();
		object_->set_position(glm::normalize(position) * planet_->get_size() * 1.025f);
	}
	else if (!goal_positions_.empty())
	{
		distance_to_goal_ = 0.0f;
		start_position_ = object_->get_position();
		goal_positions_.erase(goal_positions_.begin());
	}

	glm::quat rotation = glm::toQuat(glm::inverse(camera_->get_view()));
	object_->set_rotation(rotation);
}

void Unit::on_destroy()
{
	object_manager_->remove(object_);
	object_ = nullptr;
}
