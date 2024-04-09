//
// Created by Sterling on 4/8/2024.
//

#ifndef STATES_H
#define STATES_H


#include <glm/vec3.hpp>

class States
{
public:
	[[nodiscard]] double get_mouse_position_x() const;
	void set_mouse_position_x(double x);
	[[nodiscard]] double get_mouse_position_y() const;
	void set_mouse_position_y(double y);

	[[nodiscard]] bool is_create_unit_locked() const;
	void set_is_create_unit_locked(bool b);

	[[nodiscard]] bool is_moving_units() const;
	void set_is_moving_units(bool b);

	[[nodiscard]] bool is_making_selection() const;
	void set_is_making_selection(bool b);

	[[nodiscard]] bool is_moving_planet() const;
	void set_is_moving_planet(bool b);

	[[nodiscard]] float get_selection_max_x() const;
	void set_selection_max_x(float x);
	[[nodiscard]] float get_selection_min_x() const;
	void set_selection_min_x(float x);
	[[nodiscard]] float get_selection_max_y() const;
	void set_selection_max_y(float y);
	[[nodiscard]] float get_selection_min_y() const;
	void set_selection_min_y(float y);

	glm::vec3 get_last_click_position();
	void set_last_click_position(glm::vec3 position);

private:
	double mouse_position_x_ = 0.0f;
	double mouse_position_y_ = 0.0f;
	bool is_create_unit_locked_ = false;
	bool is_moving_units_ = false;
	bool is_making_selection_ = false;
	bool is_moving_planet_ = false;

	float selection_max_x_ = 0.0f;
	float selection_min_x_ = 0.0f;
	float selection_max_y_ = 0.0f;
	float selection_min_y_ = 0.0f;

	glm::vec3 last_click_position_;
};


#endif //STATES_H
