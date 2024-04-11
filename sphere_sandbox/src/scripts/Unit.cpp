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
		goal_position_(object->get_position()), camera_(camera), planet_(planet)
{

}

void Unit::on_create()
{

}

void Unit::on_update()
{
	glm::vec3 direction = glm::normalize(camera_->get_position() - planet_->get_position());
	glm::vec3 relative_position = glm::normalize(object_->get_position() - planet_->get_position());
	float dot = glm::dot(direction, relative_position);
	if (states_->is_making_selection() && dot > 0.2f)
	{
		glm::vec4 clip_space_position = camera_->get_projection() * (camera_->get_view() * glm::vec4{object_->get_position(), 1.0f});
		glm::vec3 ndc_space_position = glm::vec3{clip_space_position} / clip_space_position.w;
		glm::vec2 window_space_position = ((glm::vec2{ndc_space_position} + 1.0f) / 2.0f) * glm::vec2{2.0f, 2.0f} + glm::vec2{-1.0f, -1.0f};

		glm::vec2 selection_point_0_window_space_position = ((glm::vec2{states_->get_selection_points()[0]} + 1.0f) / 2.0f) * glm::vec2{2.0f, 2.0f} + glm::vec2{-1.0f, -1.0f};

		glm::vec2 selection_point_2_window_space_position = ((glm::vec2{states_->get_selection_points()[2]} + 1.0f) / 2.0f) * glm::vec2{ 2.0f, 2.0f} + glm::vec2{ -1.0f, -1.0f};

		float selection_max_x;
		float selection_min_x;
		if (selection_point_0_window_space_position.x > selection_point_2_window_space_position.x)
		{
			selection_max_x = selection_point_0_window_space_position.x;
			selection_min_x = selection_point_2_window_space_position.x;
		}
		else
		{
			selection_max_x = selection_point_2_window_space_position.x;
			selection_min_x = selection_point_0_window_space_position.x;
		}
		float selection_max_y;
		float selection_min_y;
		if (selection_point_0_window_space_position.y > selection_point_2_window_space_position.y)
		{
			selection_max_y = selection_point_0_window_space_position.y;
			selection_min_y = selection_point_2_window_space_position.y;
		}
		else
		{
			selection_max_y = selection_point_2_window_space_position.y;
			selection_min_y = selection_point_0_window_space_position.y;
		}

		if (window_space_position.x < selection_max_x &&
			window_space_position.x > selection_min_x &&
			window_space_position.y < selection_max_y &&
			window_space_position.y > selection_min_y)
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

	if (distance_to_goal_ < 1.0f)
	{
		float rotation_speed = 0.001f;
		distance_to_goal_ += rotation_speed / glm::length(goal_position_ - start_position_);
		glm::vec3 current = glm::normalize(start_position_ - planet_->get_position());
		glm::vec3 desired = glm::normalize(goal_position_ - planet_->get_position());
		auto current_quat = glm::quat(0.0f, current);
		float rotation_angle = acos(glm::dot(current, desired));
		glm::vec3 rotation_axis = glm::normalize(glm::cross(current, desired));

		glm::quat rotation = glm::angleAxis(rotation_angle * distance_to_goal_, rotation_axis);

		glm::vec3 position = glm::rotate(rotation, current) * glm::length(
			goal_position_ - planet_->get_position()) + planet_->get_position();
		object_->set_position(glm::normalize(position) * planet_->get_size() * 1.025f);
	}
	else
	{
		distance_to_goal_ = 1.0f;
		start_position_ = object_->get_position();
	}

	glm::quat rotation = glm::toQuat(glm::inverse(camera_->get_view()));
	object_->set_rotation(rotation);
}

void Unit::on_destroy()
{
	object_manager_->remove(object_);
	object_ = nullptr;
}

strl::Object* Unit::get_object()
{
	return object_;
}

void Unit::set_goal_position(glm::vec3 position)
{
	goal_position_ = position;
	distance_to_goal_ = 0.0f;
}

bool Unit::is_selected() const
{
	return is_selected_;
}
