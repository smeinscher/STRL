//
// Created by SterlingMeinscher on 4/9/2024.
//

#ifndef FORMATION_H
#define FORMATION_H


#include "strl/strl.h"
#include "Unit.h"

enum class FormationType
{
	LINE_ACROSS,
	LINE_DOWN,
	RECTANGLE5,
	RECTANGLE10,
	CIRCLE
};

struct UnitInfo
{
	Unit* unit;
	float progress_to_formation;
	glm::vec3 start_position;
	glm::vec3 goal_position;

	explicit UnitInfo(Unit* unit)
		: unit(unit), progress_to_formation(0.0f), goal_position({0.0f, 0.0f, 0.0f})
	{
		if (unit != nullptr)
		{
			start_position = unit->get_object()->get_position();
		}
		else
		{
			start_position = {0.0f, 0.0f, 0.0f};
		}
	}
};

class Formation : public strl::Script
{
public:
	Formation(States* states, strl::Camera* camera, strl::Object* planet);
	~Formation() override = default;

	void on_create() override;
	void on_update() override;
	void on_destroy() override;

	void add_unit(Unit* unit);
	void remove_unit(Unit* unit);
	void clear_units();

private:
	std::vector<UnitInfo> units_;

	FormationType current_formation_ = FormationType::RECTANGLE5;
	bool has_processed_move_ = false;
	glm::vec3 current_formation_position_ = { 0.0f, 0.0f, 0.0f};
	glm::vec3 start_position_ = {0.0f, 0.0f, 0.0f};
	std::vector<glm::vec3> goal_positions_;
	float formation_progress_to_goal_ = 0.0f;

	States* states_;
	strl::Camera* camera_;
	strl::Object* planet_;

	const float ROTATION_SPEED = 0.001f;

	bool are_units_in_position_ = false;

	void move_units_to_formation_position();
	void move_units_to_goal_position(bool setting_goal);
	std::vector<glm::vec3> get_lead_positions(bool setting_goal);

	glm::vec3 corrected_position(glm::vec3 position);

	void sort_units_by_position(glm::vec3 position);

	glm::vec3 calculate_position(glm::vec3 goal_position, glm::vec3 start_position, float distance_to_goal);

};


#endif //FORMATION_H
