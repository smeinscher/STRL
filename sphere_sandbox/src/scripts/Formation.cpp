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
	if (units_.empty())
	{
		return;
	}

	if (states_->is_moving_units() && !has_processed_move_)
	{
		if (!states_->is_in_path_mode())
		{
			goal_positions_.clear();
		}
		goal_positions_.emplace_back(corrected_position(states_->get_last_click_position()));
		if (goal_positions_.size() == 1 || !states_->is_in_path_mode())
		{
			sort_units_by_position(goal_positions_[0]);
			current_formation_position_ = units_[0].unit->get_object()->get_position();
			start_position_ = units_[0].unit->get_object()->get_position();
			formation_progress_to_goal_ = 0.0f;

			move_units_to_goal_position(true);
			are_units_in_position_ = false;
		}
		has_processed_move_ = true;
	}
	else if (!states_->is_moving_units())
	{
		has_processed_move_ = false;
	}

	if (are_units_in_position_ && formation_progress_to_goal_ < 1.0f && glm::length(goal_positions_[0] - start_position_) > glm::epsilon<float>())
	{
		formation_progress_to_goal_ += ROTATION_SPEED / glm::length(goal_positions_[0] - start_position_);
		current_formation_position_ = calculate_position(goal_positions_[0], start_position_, formation_progress_to_goal_);
		move_units_to_goal_position(false);
	}
	else if (!are_units_in_position_)
	{
		are_units_in_position_ = true;
		move_units_to_formation_position();
	}
	else
	{
		formation_progress_to_goal_ = 1.0f;
		current_formation_position_ = glm::normalize(goal_positions_[0]) * planet_->get_size() * 1.025f;
		start_position_ = current_formation_position_;
	}
}

void Formation::on_destroy()
{

}

void Formation::add_unit(Unit* unit)
{
	if (units_.empty())
	{
		current_formation_position_ = unit->get_object()->get_position();
		start_position_ = current_formation_position_;
	}
	units_.emplace_back(unit);
}

void Formation::remove_unit(Unit* unit)
{
	auto pred = [unit](const UnitInfo& u)
	{
		return unit == u.unit;
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

void Formation::move_units_to_formation_position()
{
	std::vector<glm::vec3> lead_positions = get_lead_positions(false);
	for (UnitInfo& unit : units_)
	{
		if (unit.progress_to_formation < 1.0f)
		{
			float distance = glm::length(unit.goal_position - unit.start_position);
			if (distance < glm::epsilon<float>())
			{
				unit.progress_to_formation = 1.0f;
				continue;
			}
			are_units_in_position_ = false;
			unit.progress_to_formation += ROTATION_SPEED / distance;
			unit.unit->get_object()->set_position(calculate_position(
				unit.goal_position, unit.start_position, unit.progress_to_formation));
		}
	}

}

void Formation::move_units_to_goal_position(bool setting_goal)
{
	std::vector<glm::vec3> lead_positions = get_lead_positions(setting_goal);

	std::vector<UnitInfo> placed_units;
	std::vector<UnitInfo> unplaced_units = units_;
	while (!unplaced_units.empty())
	{
		for (glm::vec3& position : lead_positions)
		{
			float min_length = -1.0f;
			UnitInfo closest_unit{nullptr};
			for (UnitInfo& unit : unplaced_units)
			{
				float length = glm::length(position - unit.unit->get_object()->get_position());
				auto pred = [unit](const UnitInfo& unit_info)
				{
					return unit.unit == unit_info.unit;
				};
				if (std::find_if(placed_units.begin(), placed_units.end(), pred) == placed_units.end() &&
					(length < min_length || min_length < 0))
				{
					min_length = length;
					closest_unit = unit;
				}
			}
			if (closest_unit.unit == nullptr)
			{
				break;
			}
			glm::vec3 old_position = closest_unit.unit->get_object()->get_position();
			auto pred = [closest_unit](const UnitInfo& unit_info)
			{
				return closest_unit.unit == unit_info.unit;
			};
			if (!setting_goal)
			{
				closest_unit.unit->get_object()->set_position(corrected_position(position));
			}
			else
			{
				auto itr = std::find_if(units_.begin(), units_.end(), pred);
				if (itr != units_.end())
				{
					itr->goal_position = corrected_position(position);
					itr->progress_to_formation = 0.0f;
				}
			}
			placed_units.emplace_back(closest_unit);
			unplaced_units.erase(std::find_if(unplaced_units.begin(), unplaced_units.end(), pred));

			glm::vec3 direction;
			if (!setting_goal)
			{
				direction = glm::normalize(closest_unit.unit->get_object()->get_position() - old_position);
			}
			else
			{
				glm::vec3 projected_center_position = calculate_position(goal_positions_[0], lead_positions[0], 0.01f);
				glm::vec3 center_direction = glm::normalize(projected_center_position - lead_positions[0]);
				if (glm::length(position - lead_positions[0]) > glm::epsilon<float>())
				{
					center_direction -= position;
					center_direction = glm::normalize(center_direction);
				}
				else
				{
				}
				direction = center_direction;
			}
			position -= direction * units_[0].unit->get_object()->get_size() * 2.0f;
		}
	}
}

std::vector<glm::vec3> Formation::get_lead_positions(bool setting_goal)
{
	glm::vec3 direction;
	if (!setting_goal)
	{
		direction = glm::normalize(current_formation_position_ - units_[0].unit->get_object()->get_position());
	}
	else
	{
		glm::vec3 projected_position = calculate_position(goal_positions_[0], units_[0].unit->get_object()->get_position(), 0.01f);
		direction = glm::normalize(projected_position - units_[0].unit->get_object()->get_position());
	}
	glm::vec3 right = glm::cross(direction, glm::normalize(current_formation_position_));
	glm::vec3 up = glm::cross(right, direction);
	glm::vec3 back = glm::cross(right, up);
	std::vector<glm::vec3> lead_positions;
	switch (current_formation_)
	{
	case FormationType::LINE_ACROSS:
		lead_positions.emplace_back(current_formation_position_);
		for (int i = 1; i < units_.size(); i++)
		{
			glm::vec3 offset = right * units_[0].unit->get_object()->get_size().x * std::floor(static_cast<float>(i + 1) / 2.0f) * 2.0f;
			if (i % 2 == 1)
			{
				lead_positions.emplace_back(current_formation_position_ + offset);
			}
			else
			{
				lead_positions.emplace_back(current_formation_position_ - offset);
			}
		}
		break;
	case FormationType::LINE_DOWN:
		lead_positions.emplace_back(current_formation_position_);
		break;
	case FormationType::RECTANGLE5:
	{
		glm::vec3 position = current_formation_position_;
		lead_positions.emplace_back(position);
		position = current_formation_position_ + right * units_[0].unit->get_object()->get_size().x * 2.0f;
		lead_positions.emplace_back(position);
		position = current_formation_position_ - right * units_[0].unit->get_object()->get_size().x * 2.0f;
		lead_positions.emplace_back(position);
		position = current_formation_position_ + right * units_[0].unit->get_object()->get_size().x * 4.0f;
		lead_positions.emplace_back(position);
		position = current_formation_position_ - right * units_[0].unit->get_object()->get_size().x * 4.0f;
		lead_positions.emplace_back(position);
		break;
	}
	case FormationType::RECTANGLE10:
		break;
	case FormationType::CIRCLE:
		break;
	default:
		break;
	}
	return lead_positions;
}

glm::vec3 Formation::corrected_position(glm::vec3 position)
{
	if (glm::length(position) < glm::epsilon<float>())
	{
		return {0.0f, 0.0f, 0.0f};
	}
	return glm::normalize(position) * planet_->get_size() * (1.0f + units_[0].unit->get_object()->get_size().x);
}

void Formation::sort_units_by_position(glm::vec3 position)
{
	auto compare = [position](const UnitInfo& a, const UnitInfo& b)
	{
		float distance_a = glm::length(position - a.unit->get_object()->get_position());
		float distance_b = glm::length(position - b.unit->get_object()->get_position());
		return distance_a < distance_b;
	};
	std::sort(units_.begin(), units_.end(), compare);
}

glm::vec3 Formation::calculate_position(glm::vec3 goal_position, glm::vec3 start_position, float distance_to_goal)
{
	glm::vec3 current = glm::normalize(start_position - planet_->get_position());
	glm::vec3 desired = glm::normalize(goal_position - planet_->get_position());
	auto current_quat = glm::quat(0.0f, current);
	float rotation_angle = acos(glm::dot(current, desired));
	glm::vec3 rotation_axis = glm::normalize(glm::cross(current, desired));

	glm::quat rotation = glm::angleAxis(rotation_angle * distance_to_goal, rotation_axis);

	glm::vec3 position = glm::rotate(rotation, current) * glm::length(
		goal_position - planet_->get_position()) + planet_->get_position();
	return corrected_position(position);
}
