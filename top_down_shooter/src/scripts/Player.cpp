//
// Created by SterlingMeinscher on 2/20/2024.
//

#include "Player.h"
#include "../data/Character.h"
#include "strl/strl.h"

Player::Player(strl::Object *top, strl::Object *middle, strl::Object *bottom, strl::EventManager *event_manager,
               strl::Box2DPhysics *physics, strl::Platform *platform, strl::Camera *camera,
               strl::Animation2D *animation2D)
    : strl::Physics2DMovementBase(top, event_manager, physics), middle_(middle), bottom_(bottom), platform_(platform),
      camera_(camera), animation2D_(animation2D)
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

    strl::EventListenerFunction attack = [this](strl::Event *event) {
        animation2D_->restart(middle_);
        animation2D_->restart(object_);
    };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_PRESSED,
                                            strl::STRL_MOUSE_BUTTON_0, attack, "Player Punch");

    strl::EventListenerFunction switch_weapon = [this](strl::Event *event) {
        selected_weapon_++;
        if (selected_weapon_ >= Character::get_weapons().size())
        {
            selected_weapon_ = 0;
        }

        switch (selected_weapon_)
        {
        case 0: {
            strl::Animation2DState top_punch_state;
            top_punch_state.selected_segment_y = 2;
            top_punch_state.start_segment_x = 0;
            top_punch_state.end_segment_x = 31;
            top_punch_state.frame_update_time = 0.025f;
            top_punch_state.repeat = false;
            animation2D_->change_state(object_, top_punch_state);
            animation2D_->stop(object_, true);

            strl::Animation2DState middle_punch_state;
            middle_punch_state.selected_segment_y = 1;
            middle_punch_state.start_segment_x = 0;
            middle_punch_state.end_segment_x = 31;
            middle_punch_state.frame_update_time = 0.025f;
            middle_punch_state.repeat = false;
            animation2D_->set_active(middle_, true);
            animation2D_->change_state(middle_, middle_punch_state);
            animation2D_->stop(middle_, true);
            break;
        }
        case 1: {
            strl::Animation2DState top_bow_state;
            top_bow_state.selected_segment_y = 4;
            top_bow_state.start_segment_x = 0;
            top_bow_state.end_segment_x = 31;
            top_bow_state.frame_update_time = 0.025f;
            top_bow_state.repeat = false;
            animation2D_->change_state(object_, top_bow_state);
            animation2D_->stop(object_, true);

            strl::Animation2DState middle_bow_state;
            middle_bow_state.selected_segment_y = -1;
            middle_bow_state.start_segment_x = -1;
            middle_bow_state.end_segment_x = -1;
            middle_bow_state.frame_update_time = 0.0f;
            middle_bow_state.repeat = false;
            animation2D_->set_active(middle_, false);
            animation2D_->change_state(middle_, middle_bow_state);
            animation2D_->stop(middle_, true);
            break;
        }
        default:

            break;
        }
    };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED, strl::STRL_KEY_TAB,
                                            switch_weapon, "Switch Weapon");
    speed_ = 1.0f;

    strl::Animation2DState top_punch_state;
    top_punch_state.selected_segment_y = 2;
    top_punch_state.start_segment_x = 0;
    top_punch_state.end_segment_x = 31;
    top_punch_state.frame_update_time = 0.025f;
    top_punch_state.repeat = false;
    animation2D_->init_animation(object_, {32, 8}, top_punch_state);

    strl::Animation2DState middle_punch_state;
    middle_punch_state.selected_segment_y = 1;
    middle_punch_state.start_segment_x = 0;
    middle_punch_state.end_segment_x = 31;
    middle_punch_state.frame_update_time = 0.025f;
    middle_punch_state.repeat = false;
    animation2D_->init_animation(middle_, {32, 8}, middle_punch_state);

    strl::Animation2DState bottom_walk_state;
    bottom_walk_state.selected_segment_y = 5;
    bottom_walk_state.start_segment_x = 0;
    bottom_walk_state.end_segment_x = 17;
    bottom_walk_state.frame_update_time = 0.025f;
    bottom_walk_state.repeat = true;
    animation2D_->init_animation(bottom_, {32, 8}, bottom_walk_state);
}

void Player::on_update()
{
    strl::Physics2DMovementBase::on_update();

    float dx = mouse_position_x_ - object_->get_position().x;
    float dy = mouse_position_y_ - object_->get_position().y;
    float angle = atan2(dy, dx);
    object_->set_rotation({0.0f, 0.0f, angle});

    if (!is_moving_up_ && !is_moving_down_ && !is_moving_left_ && !is_moving_right_)
    {
        animation2D_->stop(bottom_, true);
        animation2D_->restart(bottom_);
    }

    if (middle_)
    {
        middle_->set_position({object_->get_position().x, object_->get_position().y, middle_->get_position().z});
        middle_->set_color(object_->get_color());
        middle_->set_rotation(object_->get_rotation().quaternion);
    }
    if (bottom_)
    {
        bottom_->set_position({object_->get_position().x, object_->get_position().y, bottom_->get_position().z});
        bottom_->set_rotation(object_->get_rotation().quaternion);
        bottom_->set_color(object_->get_color());
    }
}
