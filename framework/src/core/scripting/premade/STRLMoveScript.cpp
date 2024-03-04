//
// Created by SterlingMeinscher on 2/13/2024.
//

#include <iostream>
#include "STRLMoveScript.h"

namespace strl
{

STRLMoveScript::STRLMoveScript(STRLObject* object)
	: object_(object)
{

}

STRLMoveScript::~STRLMoveScript() = default;

void STRLMoveScript::on_create()
{

}

void STRLMoveScript::on_update()
{
	static float r = 0.0f;
	r += std::numbers::pi / 1000.0f;
	object_->set_rotation({object_->get_rotation().euler.x, r, object_->get_rotation().euler.z});
	static int x = 0.0f;
	x += 1;
	object_->set_position_x(static_cast<float>(x % 1000) / 1000.0f * 24.0f - 12.0f);
}

void STRLMoveScript::on_destroy()
{

}

} // strl