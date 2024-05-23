//
// Created by SterlingMeinscher on 2/20/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "strl/strl.h"

class Player : public strl::Physics2DMovementBase
{
  public:
    Player(strl::Object *top, strl::Object *middle, strl::Object *bottom, strl::EventManager *event_manager,
           strl::Box2DPhysics *physics, strl::Platform *platform, strl::Camera *camera, strl::Animation2D *animation2D);
    void on_create() override;
    void on_update() override;

  private:
    strl::Object *middle_ = nullptr;
    strl::Object *bottom_ = nullptr;
    strl::Platform *platform_ = nullptr;
    strl::Camera *camera_ = nullptr;
    strl::Animation2D *animation2D_;
    double mouse_position_x_ = 0.0f;
    double mouse_position_y_ = 0.0f;

    int selected_weapon_ = 0;
};

#endif // PLAYER_H
