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
	if (states_->is_moving_units() && !has_processed_move_ && !units_.empty())
	{
		if (!states_->is_in_path_mode())
		{
			goal_positions_.clear();
		}
		goal_positions_.emplace_back(glm::normalize(states_->get_last_click_position()) * planet_->get_size() * 1.025f);
		has_processed_move_ = true;
	}
	else if (!states_->is_moving_units())
	{
		has_processed_move_ = false;
	}

	if (!goal_positions_.empty())
	{
		are_units_in_position_ = true;
		has_goal_been_reached_ = true;
		for (int i = 0; i < units_.size(); i++)
		{
			if (!are_all_unit_goal_positions_set_)
			{
				units_[i]->set_goal_position(get_relative_formation_goal_position(units_[i], i));
			}
			if (!units_[i]->has_reached_goal())
			{
				has_goal_been_reached_ = false;
			}
		}
		are_all_unit_goal_positions_set_ = true;
		/*if (are_units_in_position_)
		{
			are_all_unit_goal_positions_set_ = false;
		}*/
		if (has_goal_been_reached_)
		{
			goal_positions_.erase(goal_positions_.begin());
			are_all_unit_goal_positions_set_ = false;
		}
		/*if (distance_to_goal_ < 1.0f)
		{
			*//*if (are_units_in_position_)
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
			}*//*
		}
		else
		{
			distance_to_goal_ = 0.0f;
			start_position_ = current_position_;
			goal_positions_.erase(goal_positions_.begin());
		}*/

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

glm::vec3 Formation::get_relative_formation_goal_position(Unit* unit, int index)
{
	glm::vec3 direction_to_goal = glm::normalize(unit->get_object()->get_position() - goal_positions_[0]);
	glm::vec3 right = glm::cross(direction_to_goal, glm::normalize(unit->get_object()->get_position()));
	glm::vec3 up = glm::cross(right, direction_to_goal);
	glm::vec3 back = glm::cross(right, up);
	switch (current_formation_)
	{
	case FormationType::LINE_ACROSS:
		break;
	case FormationType::LINE_DOWN:
		return goal_positions_[0] * back * unit->get_object()->get_size() * static_cast<float>(index);
	case FormationType::RECTANGLE5:
		switch (index % 5)
		{
		case 0:
		{
			glm::vec3 position = goal_positions_[0] -
				(back * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f));
			return corrected_position(position);
		}
		case 1:
		{
			glm::vec3 position = goal_positions_[0] + right * unit->get_object()->get_size() -
				(back * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f));
			return corrected_position(position);
		}
		case 2:
		{
			glm::vec3 position = goal_positions_[0] - right * unit->get_object()->get_size() -
				(back * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f));
			return corrected_position(position);
		}
		case 3:
		{
			glm::vec3 position = goal_positions_[0] + right * unit->get_object()->get_size() * 2.0f -
				(back * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f));
			return corrected_position(position);
		}
		case 4:
		{
			glm::vec3 position = goal_positions_[0] - right * unit->get_object()->get_size() * 2.0f -
				(back * unit->get_object()->get_size() * std::floor(static_cast<float>(index) / 5.0f));
			return corrected_position(position);
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

	return {0.0f, 0.0f, 0.0f};
}

glm::vec3 Formation::corrected_position(glm::vec3 position)
{
	return glm::normalize(position) * planet_->get_size() * 1.025f;
}
