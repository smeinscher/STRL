//
// Created by SterlingMeinscher on 2/19/2024.
//

#ifndef PONGBALL_H
#define PONGBALL_H

#include "strl/strl.h"

class PongBall : public strl::Physics2DBase
{
public:
	using strl::Physics2DBase::STRLPhysics2DBase;
	~PongBall() override = default;
	void on_create() override;
	void on_update() override;

private:
	std::unique_ptr<std::function<void()>> body_script_;
};

#endif //PONGBALL_H
