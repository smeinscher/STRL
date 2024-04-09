//
// Created by Sterling on 4/7/2024.
//

#ifndef UNIT_H
#define UNIT_H


#include "strl/strl.h"
#include "../states/States.h"

class Unit : public strl::Script
{
public:
	Unit(strl::Object* object,
		strl::ObjectManager* object_manager,
		States* states,
		strl::Camera* camera,
		strl::Object* planet);
	~Unit() override = default;
	void on_create() override;
	void on_update() override;
	void on_destroy() override;

private:
	strl::Object* object_ = nullptr;
	strl::ObjectManager* object_manager_ = nullptr;
	strl::Camera* camera_;
	strl::Object* planet_;

	States* states_;

	bool is_selected_ = false;
	bool has_processed_move_ = false;
	glm::vec3 start_position_;
	std::vector<glm::vec3> goal_positions_;
	float distance_to_goal_ = 0.0f;
};


#endif //UNIT_H
