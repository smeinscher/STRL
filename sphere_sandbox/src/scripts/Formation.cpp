//
// Created by SterlingMeinscher on 4/9/2024.
//

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>
#include "Formation.h"

Formation::Formation(States* states, strl::Camera* camera, strl::Object* planet)
	: states_(states), camera_(camera), planet_(planet)
{

}

void Formation::on_create()
{

}

void Formation::on_update()
{
	if (states_->is_moving_units() && !has_processed_move_)
	{
		goal_positions_.emplace_back(states_->get_last_click_position());
		has_processed_move_ = true;
	}
	else if (!states_->is_moving_units())
	{
		has_processed_move_ = false;
	}

	if (!goal_positions_.empty() && distance_to_goal_ < 1.0f)
	{
		if (distance_to_goal_ < 1.0f)
		{
			float rotation_speed = 0.001f;
			distance_to_goal_ += rotation_speed / glm::length(goal_positions_[0] - start_position_);
			glm::vec3 current = glm::normalize(start_position_ - planet_->get_position());
			glm::vec3 desired = glm::normalize(goal_positions_[0] - planet_->get_position());
			auto current_quat = glm::quat(0.0f, current);
			float rotation_angle = acos(glm::dot(current, desired));
			glm::vec3 rotation_axis = glm::normalize(glm::cross(current, desired));

			glm::quat rotation = glm::angleAxis(rotation_angle * distance_to_goal_, rotation_axis);

			current_position_ = glm::normalize(glm::rotate(rotation, current) * glm::length(
				goal_positions_[0] - planet_->get_position()) + planet_->get_position());

			//current_position_ = glm::normalize(position) * planet_->get_size() * 1.025f;

			for (int i = 0; i < units_.size(); i++)
			{
				set_unit_position(units_[i], i);
			}
		}
		else
		{
			distance_to_goal_ = 0.0f;
			start_position_ = current_position_;
			goal_positions_.erase(goal_positions_.begin());
		}

	}
}

void Formation::on_destroy()
{

}

void Formation::add_unit(Unit* unit)
{
	if (units_.empty())
	{
		current_position_ = unit->get_object()->get_position();
		start_position_ = current_position_;
	}
	units_.emplace_back(unit);
}

void Formation::remove_unit(Unit* unit)
{
	auto pred = [unit](Unit* u)
	{
		return unit == u;
	};
	auto it = std::find_if(units_.begin(), units_.end(), pred);
	if (it != units_.end())
	{
		units_.erase(it);
	}
}

void Formation::clear_units()
{
	units_.clear();
}

void Formation::set_unit_position(Unit* unit, int index)
{
	glm::vec3 direction_to_goal = glm::normalize(goal_positions_[0] - current_position_);
	switch (current_formation_)
	{
	case FormationType::LINE_ACROSS:
		break;
	case FormationType::LINE_DOWN:
		unit->set_goal_position(current_position_ * unit->get_object()->get_size() * static_cast<float>(index));
		break;
	case FormationType::RECTANGLE5:
		switch (index % 5)
		{
		case 0:
			unit->set_goal_position(current_position_ -
				(glm::normalize(direction_to_goal) * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f)));
			break;
		case 1:
		{
			glm::vec3 right = glm::cross(direction_to_goal, glm::normalize(unit->get_object()->get_position()));
			unit->set_goal_position(current_position_ + right * unit->get_object()->get_size() -
				(direction_to_goal * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f)));
			break;
		}
		case 2:
		{
			glm::vec3 left = glm::cross(glm::normalize(unit->get_object()->get_position()), direction_to_goal);
			unit->set_goal_position(current_position_ + left * unit->get_object()->get_size() -
				(direction_to_goal * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f)));
			break;
		}
		case 3:
		{
			glm::vec3 right = glm::cross(direction_to_goal, glm::normalize(unit->get_object()->get_position()));
			unit->set_goal_position(current_position_ + right * unit->get_object()->get_size() * 2.0f -
				(direction_to_goal * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f)));
			break;
		}
		case 4:
		{
			glm::vec3 left = glm::cross(glm::normalize(unit->get_object()->get_position()), direction_to_goal);
			unit->set_goal_position(current_position_ + left * unit->get_object()->get_size() * 2.0f -
				(direction_to_goal * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f)));
			break;
		}
		}
		break;
	case FormationType::RECTANGLE10:
		break;
	case FormationType::CIRCLE:
		break;
	default:
		break;
	}
}
