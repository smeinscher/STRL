//
// Created by SterlingMeinscher on 2/20/2024.
//

#include "Player.h"

void Player::on_update()
{
	STRLBasicMovementPhysics2D::on_update();
	if (object_->get_position().y > 600.0f - object_->get_size().y / 2.0f)
	{
		object_->set_position_y(600.0f - object_->get_size().y / 2.0f);
		body_->SetTransform({body_->GetPosition().x, object_->get_position().y * strl::PHYSICS_SCALE},
			body_->GetAngle());
	}
	else if (object_->get_position().y < 0.0f + object_->get_size().y / 2.0f)
	{
		object_->set_position_y(0.0f + object_->get_size().y / 2.0f);
		body_->SetTransform({body_->GetPosition().x, object_->get_position().y * strl::PHYSICS_SCALE},
			body_->GetAngle());
	}
}
