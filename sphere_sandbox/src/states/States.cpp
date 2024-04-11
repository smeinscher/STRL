//
// Created by Sterling on 4/8/2024.
//

#include "States.h"

#include <utility>

double States::get_mouse_position_x() const
{
	return mouse_position_x_;
}

void States::set_mouse_position_x(double x)
{
	mouse_position_x_ = x;
}

double States::get_mouse_position_y() const
{
	return mouse_position_y_;
}

void States::set_mouse_position_y(double y)
{
	mouse_position_y_ = y;
}

bool States::is_create_unit_locked() const
{
	return is_create_unit_locked_;
}

void States::set_is_create_unit_locked(bool b)
{
	is_create_unit_locked_ = b;
}

bool States::is_moving_units() const
{
	return is_moving_units_;
}

void States::set_is_moving_units(bool b)
{
	is_moving_units_ = b;
}

bool States::is_making_selection() const
{
	return is_making_selection_;
}

void States::set_is_making_selection(bool b)
{
	is_making_selection_ = b;
}

bool States::is_moving_planet() const
{
	return is_moving_planet_;
}

void States::set_is_moving_planet(bool b)
{
	is_moving_planet_ = b;
}

bool States::is_in_path_mode() const
{
	return is_in_path_mode_;
}

void States::set_is_in_path_mode(bool b)
{
	is_in_path_mode_ = b;
}

std::vector<glm::vec3> States::get_selection_points()
{
	return selection_points_;
}

void States::set_selection_points(std::vector<glm::vec3> points)
{
	selection_points_ = std::move(points);
}

glm::vec3 States::get_last_click_position()
{
	return last_click_position_;
}

void States::set_last_click_position(glm::vec3 position)
{
	last_click_position_ = position;
}
