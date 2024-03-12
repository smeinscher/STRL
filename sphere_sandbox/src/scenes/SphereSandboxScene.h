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
	void render() override;

private:
	strl::Object* planet_;
	strl::Object* person_;
	bool is_left_mouse_button_down_ = false;
	double mouse_position_x_ = 0.0f;
	double mouse_position_y_ = 0.0f;

};


#endif //SPHERESANDBOXSCENE_H
