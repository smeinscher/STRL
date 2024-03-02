//
// Created by SterlingMeinscher on 2/20/2024.
//

#ifndef PLAYER_H
#define PLAYER_H


#include "strl/strl.h"

class Player : public strl::Physics2DMovementBase
{
public:
	using strl::Physics2DMovementBase::STRLBasicMovementPhysics2D;
	void on_update() override;
};


#endif //PLAYER_H
