//
// Created by SterlingMeinscher on 2/20/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "strl/strl.h"

class Player : public strl::Physics2DMovementBase
{
  public:
    Player(strl::Object *object, strl::EventManager *event_manager, strl::Box2DPhysics *physics,
           strl::Platform *platform, strl::Camera *camera);
    void on_create() override;
    void on_update() override;

  private:
    strl::Platform *platform_ = nullptr;
    strl::Camera *camera_ = nullptr;
    double mouse_position_x_ = 0.0f;
    double mouse_position_y_ = 0.0f;
};

#endif // PLAYER_H
