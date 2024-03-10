//
// Created by SterlingMeinscher on 2/19/2024.
//

#ifndef STRLBASICMOVEMENTPHYSICS2D_H
#define STRLBASICMOVEMENTPHYSICS2D_H

#include "../ISTRLScript.h"
#include "../../../core/object/STRLObject.h"
#include "../../event/STRLEventManager.h"
#include "../../../config/STRLConfig.h"
#include "../../../physics/box2D/Box2DPhysics.h"

namespace strl
{


class STRLBasicMovementPhysics2D : public ISTRLScript
{
public:
	STRLBasicMovementPhysics2D(STRLObject* object,
		STRLEventManager* event_manager,
		Box2DPhysics* physics,
		STRLKey up_key = STRL_KEY_W,
		STRLKey down_key = STRL_KEY_S,
		STRLKey left_key = STRL_KEY_A,
		STRLKey right_key = STRL_KEY_D);
	~STRLBasicMovementPhysics2D() override = default;
	void on_create() override;
	void on_update() override;
	void on_destroy() override;

protected:
	STRLObject* object_;
	STRLEventManager* event_manager_;
	Box2DPhysics* physics_;
	b2Body* body_ = nullptr;
	STRLKey up_key_;
	STRLKey down_key_;
	STRLKey left_key_;
	STRLKey right_key_;

	bool is_moving_up_ = false;
	bool is_moving_down_ = false;
	bool is_moving_left_ = false;
	bool is_moving_right_ = false;

	std::unique_ptr<std::function<void()>> body_script_;

	float speed_ = 5.0f;
};

} // strl

#endif //STRLBASICMOVEMENTPHYSICS2D_H
