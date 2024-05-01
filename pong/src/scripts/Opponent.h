//
// Created by SterlingMeinscher on 2/20/2024.
//

#ifndef OPPONENT_H
#define OPPONENT_H

#include "strl/strl.h"

class Opponent : public strl::Physics2DBase
{
public:
	Opponent(strl::STRLObject* paddle,
		strl::STRLObject* ball,
		strl::Box2DPhysics* physics,
		strl::Box2DPhysicsDefinitions definitions = {});
	~Opponent() override = default;
	void on_update() override;

private:
	strl::STRLObject* ball_;
	float speed_ = 5.0f;
};

#endif //OPPONENT_H
