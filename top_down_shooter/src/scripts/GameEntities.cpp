#include "GameEntities.h"
#include "../data/Character.h"
#include "Projectile.h"
#include "strl/strl.h"
#include <glm/ext/scalar_constants.hpp>
#include <memory>

GameEntities::GameEntities(strl::ObjectManager *object_manager, strl::RenderDataManager *render_data_manager,
                           strl::EventManager *event_manager, strl::Box2DPhysics *physics, strl::Platform *platform,
                           strl::Shader *shader, strl::Camera *main_camera, strl::Animation2D *animation2D,
                           strl::STRLScriptManager *script_manager)
    : object_manager_(object_manager), render_data_manager_(render_data_manager), event_manager_(event_manager),
      physics_(physics), platform_(platform), shader_(shader), main_camera_(main_camera), animation2D_(animation2D),
      script_manager_(script_manager)
{
}

void GameEntities::on_create()
{
    strl::STRLEventListenerFunction up_pressed = [this](strl::STRLEvent *event) { is_pressing_up_ = true; };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED, strl::STRL_KEY_W, up_pressed,
                                            "Up Pressed");
    strl::STRLEventListenerFunction up_released = [this](strl::STRLEvent *event) { is_pressing_up_ = false; };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED, strl::STRL_KEY_W, up_released,
                                            "Up Released");

    strl::STRLEventListenerFunction down_pressed = [this](strl::STRLEvent *event) { is_pressing_down_ = true; };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED, strl::STRL_KEY_S, down_pressed,
                                            "Down Pressed");
    strl::EventListenerFunction down_released = [this](strl::STRLEvent *event) { is_pressing_down_ = false; };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED, strl::STRL_KEY_S,
                                            down_released, "Down Released");

    strl::EventListenerFunction left_pressed = [this](strl::STRLEvent *event) { is_pressing_left_ = true; };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED, strl::STRL_KEY_A, left_pressed,
                                            "Left Pressed");
    strl::EventListenerFunction left_released = [this](strl::STRLEvent *event) { is_pressing_left_ = false; };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED, strl::STRL_KEY_A,
                                            left_released, "Left Released");

    strl::EventListenerFunction right_pressed = [this](strl::STRLEvent *event) { is_pressing_right_ = true; };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED, strl::STRL_KEY_D,
                                            right_pressed, "Right Pressed");
    strl::EventListenerFunction right_released = [this](strl::STRLEvent *event) { is_pressing_right_ = false; };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED, strl::STRL_KEY_D,
                                            right_released, "Right Released");

    strl::EventListenerFunction mouse_movement = [this](strl::Event *event) {
        auto data = reinterpret_cast<strl::STRLMouseMoveEventData *>(event->get_event_data());
        mouse_position_x_ = data->x_pos;
        mouse_position_y_ = data->y_pos;
    };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_MOVED, 0, mouse_movement,
                                            "Mouse Moved");

    strl::RenderData *arrow_render_data = render_data_manager_->create("Arrow", {"Arrow"}, shader_, main_camera_);
    arrow_render_data->create_texture("resources/textures/arrow.png");

    strl::EventListenerFunction attack = [this](strl::Event *event) {
        if (!player_controlled_entity_)
        {
            return;
        }
        animation2D_->restart(player_controlled_entity_->top);
        animation2D_->restart(player_controlled_entity_->middle);

        strl::ObjectDefinition arrow_definition;
        arrow_definition.name = "Arrow" + player_controlled_entity_->top->get_name();
        arrow_definition.tags = {"Arrow"};
        arrow_definition.size = {50.0f, 50.0f, 0.0f};
        arrow_definition.position = player_controlled_entity_->top->get_position();
        strl::Object *arrow = object_manager_->create(arrow_definition);
        object_manager_->assign_render_data("Arrow", arrow);

        strl::ScriptHandler *arrow_script_handler = script_manager_->create("Arrow", std::vector<std::string>{"Arrow"});
        arrow_script_handler->bind<Projectile>(arrow, player_controlled_entity_->top, object_manager_, physics_,
                                               main_camera_, &mouse_position_x_, &mouse_position_y_, script_manager_,
                                               arrow_script_handler->get_id());
    };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_PRESSED,
                                            strl::STRL_MOUSE_BUTTON_0, attack, "Player Punch");

    strl::EventListenerFunction switch_weapon = [this](strl::Event *event) {
        if (!player_controlled_entity_)
        {
            return;
        }
        player_controlled_entity_->selected_weapon++;
        if (player_controlled_entity_->selected_weapon >= Character::get_weapons().size())
        {
            player_controlled_entity_->selected_weapon = 0;
        }

        switch (player_controlled_entity_->selected_weapon)
        {
        case 0: {
            strl::Animation2DState top_punch_state;
            top_punch_state.selected_segment_y = 2;
            top_punch_state.start_segment_x = 0;
            top_punch_state.end_segment_x = 31;
            top_punch_state.frame_update_time = 0.025f;
            top_punch_state.repeat = false;
            animation2D_->change_state(player_controlled_entity_->top, top_punch_state);
            animation2D_->stop(player_controlled_entity_->top, true);

            strl::Animation2DState middle_punch_state;
            middle_punch_state.selected_segment_y = 1;
            middle_punch_state.start_segment_x = 0;
            middle_punch_state.end_segment_x = 31;
            middle_punch_state.frame_update_time = 0.025f;
            middle_punch_state.repeat = false;
            animation2D_->set_active(player_controlled_entity_->middle, true);
            animation2D_->change_state(player_controlled_entity_->middle, middle_punch_state);
            animation2D_->stop(player_controlled_entity_->middle, true);
            break;
        }
        case 1: {
            strl::Animation2DState top_bow_state;
            top_bow_state.selected_segment_y = 4;
            top_bow_state.start_segment_x = 0;
            top_bow_state.end_segment_x = 31;
            top_bow_state.frame_update_time = 0.025f;
            top_bow_state.repeat = false;
            animation2D_->change_state(player_controlled_entity_->top, top_bow_state);
            animation2D_->stop(player_controlled_entity_->top, true);

            strl::Animation2DState middle_bow_state;
            middle_bow_state.selected_segment_y = -1;
            middle_bow_state.start_segment_x = -1;
            middle_bow_state.end_segment_x = -1;
            middle_bow_state.frame_update_time = 0.0f;
            middle_bow_state.repeat = false;
            animation2D_->set_active(player_controlled_entity_->middle, false);
            animation2D_->change_state(player_controlled_entity_->middle, middle_bow_state);
            animation2D_->stop(player_controlled_entity_->middle, true);
            break;
        }
        default:

            break;
        }
    };
    event_manager_->register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED, strl::STRL_KEY_TAB,
                                            switch_weapon, "Switch Weapon");

    strl::RenderData *character_render_data =
        render_data_manager_->create("Character", {"Character"}, shader_, main_camera_);
    character_render_data->create_texture("resources/textures/character8.png");

    std::vector<glm::vec2> uvs = {
        // top right
        {1.0f / 32.0f, 1.0f},
        // top left
        {0.0f, 1.0f},
        // bottom left
        {0.0f, 1.0f - 1.0f / 8.0f},
        // bottom right
        {1.0f / 32.0f, 1.0f - 1.0f / 8.0f},
    };
    strl::ObjectDefinition character_definition{strl::STRL_SHAPE2D_SQUARE_VERTICES, uvs, strl::STRLObjectType::SHAPE2D};
    character_definition.size = {50.0f, 50.0f, 0.0f};

    for (int i = 0; i < 1; i++)
    {
        std::unique_ptr<Entity> entity = std::make_unique<Entity>();

        character_definition.position = {300.0f, 200.0f, 0.2f};
        entity->bottom = object_manager_->create(character_definition);
        object_manager_->assign_render_data("Character", entity->bottom);

        character_definition.position.z = 0.3f;
        entity->middle = object_manager_->create(character_definition);
        object_manager_->assign_render_data("Character", entity->middle);

        character_definition.position.z = 0.4f;
        entity->top = object_manager_->create(character_definition);
        object_manager_->assign_render_data("Character", entity->top);

        entity->physics_body_data = std::make_unique<strl::Box2DBodyData>();
        b2BodyDef body_definition =
            strl::Box2DPhysics::generate_b2BodyDef(entity->top, entity->physics_body_data.get());
        entity->physics_body = physics_->create_body(body_definition);
        std::unique_ptr<b2Shape> shape = strl::Box2DPhysics::generate_b2Shape(entity->top);
        b2FixtureDef fixture_definition = strl::Box2DPhysics::generate_b2FixtureDef(shape.get());
        strl::Box2DPhysics::create_fixture(entity->physics_body, fixture_definition);

        strl::Animation2DState top_punch_state;
        top_punch_state.selected_segment_y = 2;
        top_punch_state.start_segment_x = 0;
        top_punch_state.end_segment_x = 31;
        top_punch_state.frame_update_time = 0.025f;
        top_punch_state.repeat = false;
        animation2D_->init_animation(entity->top, {32, 8}, top_punch_state);

        strl::Animation2DState middle_punch_state;
        middle_punch_state.selected_segment_y = 1;
        middle_punch_state.start_segment_x = 0;
        middle_punch_state.end_segment_x = 31;
        middle_punch_state.frame_update_time = 0.025f;
        middle_punch_state.repeat = false;
        animation2D_->init_animation(entity->middle, {32, 8}, middle_punch_state);

        strl::Animation2DState bottom_walk_state;
        bottom_walk_state.selected_segment_y = 5;
        bottom_walk_state.start_segment_x = 0;
        bottom_walk_state.end_segment_x = 17;
        bottom_walk_state.frame_update_time = 0.025f;
        bottom_walk_state.repeat = true;
        animation2D_->init_animation(entity->bottom, {32, 8}, bottom_walk_state);

        entities_.push_back(std::move(entity));
    }
    player_controlled_entity_ = entities_[0].get();
    focused_entity_ = player_controlled_entity_;
    player_controlled_entity_->physics_body->SetTransform({platform_->get_window_width() / 2.0f * strl::PHYSICS_SCALE,
                                                           platform_->get_window_height() / 2.0f * strl::PHYSICS_SCALE},
                                                          player_controlled_entity_->top->get_rotation().euler.z);
}

void GameEntities::on_update()
{
    if (player_controlled_entity_)
    {
        float dx =
            mouse_position_x_ + main_camera_->get_position().x - player_controlled_entity_->top->get_position().x;
        float dy =
            mouse_position_y_ + main_camera_->get_position().y - player_controlled_entity_->top->get_position().y;
        float angle = atan2(dy, dx);
        player_controlled_entity_->top->set_rotation({0.0f, 0.0f, angle});

        b2Vec2 velocity{0.0f, 0.0f};
        if (is_pressing_up_)
        {
            velocity.y -= 1.0f;
        }
        if (is_pressing_down_)
        {
            velocity.y += 1.0f;
        }
        if (is_pressing_left_)
        {
            velocity.x -= 1.0f;
        }
        if (is_pressing_right_)
        {
            velocity.x += 1.0f;
        }
        velocity.Normalize();
        velocity *= player_controlled_entity_->current_speed * strl::PHYSICS_SCALE;
        player_controlled_entity_->physics_body->SetLinearVelocity(velocity);
        player_controlled_entity_->physics_body->SetTransform(player_controlled_entity_->physics_body->GetPosition(),
                                                              player_controlled_entity_->top->get_rotation().euler.z);
    }

    for (std::unique_ptr<Entity> &entity : entities_)
    {
        entity->top->set_position_x(entity->physics_body->GetPosition().x / strl::PHYSICS_SCALE);
        entity->top->set_position_y(entity->physics_body->GetPosition().y / strl::PHYSICS_SCALE);
        if (entity->middle)
        {
            entity->middle->set_position(
                {entity->top->get_position().x, entity->top->get_position().y, entity->middle->get_position().z});
            entity->middle->set_color(entity->top->get_color());
            entity->middle->set_rotation(entity->top->get_rotation().quaternion);
        }
        if (entity->bottom)
        {
            entity->bottom->set_position(
                {entity->top->get_position().x, entity->top->get_position().y, entity->bottom->get_position().z});
            entity->bottom->set_rotation(entity->top->get_rotation().quaternion);
            entity->bottom->set_color(entity->top->get_color());
        }
        if (abs(entity->physics_body->GetLinearVelocity().x) < 1.0f &&
            abs(entity->physics_body->GetLinearVelocity().y) < 1.0f)
        {
            entity->physics_body->SetLinearVelocity({0.0f, 0.0f});
            animation2D_->stop(entity->bottom, true);
            animation2D_->restart(entity->bottom);
        }
    }

    if (focused_entity_)
    {
        float new_x = focused_entity_->top->get_position().x - main_camera_->get_view_width() / 2.0f;
        float new_y = focused_entity_->top->get_position().y - main_camera_->get_view_height() / 2.0f;
        main_camera_->set_position({new_x, new_y, main_camera_->get_position().z});
    }
}

void GameEntities::on_destroy()
{
}
