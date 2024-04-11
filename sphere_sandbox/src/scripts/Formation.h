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
	std::vector<Unit*> units_;

	FormationType current_formation_ = FormationType::RECTANGLE5;
	bool has_processed_move_ = false;
	glm::vec3 current_position_ = {0.0f, 0.0f, 0.0f};
	glm::vec3 start_position_ = {0.0f, 0.0f, 0.0f};
	std::vector<glm::vec3> goal_positions_;
	float distance_to_goal_ = 0.0f;

	States* states_;
	strl::Camera* camera_;
	strl::Object* planet_;

	void set_unit_position(Unit* unit, int index);

};


#endif //FORMATION_H
