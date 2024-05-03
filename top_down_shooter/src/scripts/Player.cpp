//
// Created by SterlingMeinscher on 2/20/2024.
//

#include "Player.h"
#include "strl/strl.h"

Player::Player(strl::Object *object, strl::EventManager *event_manager, strl::Box2DPhysics *physics,
               strl::Platform *platform, strl::Camera *camera)
    : strl::Physics2DMovementBase(object, event_manager, physics, strl::STRL_KEY_S, strl::STRL_KEY_W),
      platform_(platform), camera_(camera)
{
}

void Player::on_create()
{
    strl::Physics2DMovementBase::on_create();

    strl::EventListenerFunction mouse_movement = [this](strl::Event *event) {
        auto data = reinterpret_cast<strl::STRLMouseMoveEventData *>(event->get_event_data());
        mouse_position_x_ = data->x_pos;
        mouse_position_y_ = data->y_pos;
    };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_MOVED, 0, mouse_movement,
                                            "Mouse Moved");

    speed_ = 0.01f;
}

void Player::on_update()
{
    strl::Physics2DMovementBase::on_update();

    float dx = ((2.0f * mouse_position_x_) / platform_->get_window_width() - 1.0f) - object_->get_position().x;
    float dy = (1.0f - (2.0f * mouse_position_y_) / platform_->get_window_height()) - object_->get_position().y;
    float angle = atan2(dy, dx);
    object_->set_rotation({0.0f, 0.0f, angle});
}
