//
// Created by Sterling on 3/9/2024.
//

#ifndef SPHERESANDBOXSCENE_H
#define SPHERESANDBOXSCENE_H


#include "strl/strl.h"

class SphereSandboxScene : public strl::Scene
{
public:
	using strl::Scene::STRLSceneBase;
	bool init() override;
	void update() override;
	void render() override;

private:
	strl::Object* planet_;
	strl::Object* tank_;
	bool is_left_mouse_button_down_ = false;
	bool is_right_mouse_button_down_ = false;
	double mouse_position_x_ = 0.0f;
	double mouse_position_y_ = 0.0f;

	glm::vec3 goal_position_;
	glm::vec3 start_position_;
	float distance_to_goal_ = 1.0f;

	glm::vec3 planet_up_ = {0.0f, 1.0f, 0.0f};

	std::vector<glm::vec3> nodes_;

};


#endif //SPHERESANDBOXSCENE_H
