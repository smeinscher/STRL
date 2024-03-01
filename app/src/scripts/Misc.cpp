//
// Created by SterlingMeinscher on 2/20/2024.
//

#include "Misc.h"

Misc::Misc(strl::STRLDriver* engine)
	: engine_(engine)
{

}

void Misc::on_create()
{

}

void Misc::on_update()
{
	color_.r += 0.01f * mod_;
	if (color_.r >= 0.3f || color_.r <= 0.0f)
	{
		mod_ *= -1.0f;
	}
	engine_->set_background_color(color_);
}

void Misc::on_destroy()
{

}
