//
// Created by SterlingMeinscher on 2/17/2024.
//

#ifndef STRLPLAYERCONTROLLER_H
#define STRLPLAYERCONTROLLER_H

#include "../ISTRLScript.h"
#include "../../../object/STRLObject.h"
#include "../../../config/STRLConfig.h"
#include "../../event/STRLEventManager.h"

namespace strl
{

class STRLPlayerController : public ISTRLScript
{
public:
	STRLPlayerController(STRLObject* object,
		STRLEventManager* event_manager,
		STRLKey up_key = STRL_KEY_W,
		STRLKey down_key = STRL_KEY_S,
		STRLKey left_key = STRL_KEY_A,
		STRLKey right_key = STRL_KEY_D,
		STRLPlane movement_plane = STRLPlane::XY);
	~STRLPlayerController() override = default;
	void on_create() override;
	void on_update() override;
	void on_destroy() override;

private:
	STRLObject* object_;
	STRLEventManager* event_manager_;
	STRLPlane movement_plane_;
	STRLKey up_key_;
	STRLKey down_key_;
	STRLKey left_key_;
	STRLKey right_key_;

	bool is_moving_up_ = false;
	bool is_moving_down_ = false;
	bool is_moving_left_ = false;
	bool is_moving_right_ = false;
};

} // strl

#endif //STRLPLAYERCONTROLLER_H
