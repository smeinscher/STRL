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

	strl::Object* get_object();

	void set_goal_position(glm::vec3 position);

	bool is_selected() const;

private:
	strl::Object* object_ = nullptr;
	strl::ObjectManager* object_manager_ = nullptr;
	strl::Camera* camera_;
	strl::Object* planet_;

	States* states_;

	bool is_selected_ = false;
	bool has_processed_move_ = false;
	glm::vec3 start_position_;
	glm::vec3 goal_position_;
	float distance_to_goal_ = 1.0f;
};


#endif //UNIT_H
