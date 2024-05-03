//
// Created by Sterling on 3/1/2024.
//

#include "GameScene.h"
#include "../scripts/Player.h"
#include "strl/strl.h"

bool GameScene::init()
{
    if (!STRLSceneBase::init())
    {
        return false;
    }

    strl::RenderData *character_render_data = get_render_data_manager().create(
        "Character", {"Character"}, (*get_shader_manager().begin()).get(), (*get_camera_manager().begin()).get());
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
    strl::ObjectDefinition player_definition{strl::STRL_SHAPE2D_SQUARE_VERTICES, uvs, strl::STRLObjectType::SHAPE2D};
    player_definition.size = {0.1f, 0.1f, 0.0f};
    strl::Object *player_object = get_object_manager().create(player_definition);
    get_object_manager().assign_render_data("Character", player_object);

    player_script_handler_ = get_script_manager().create("Player", std::vector<std::string>());
    player_script_handler_->bind<Player>(player_object, &get_event_manager(), &get_physics(), &get_platform(),
                                         (*get_camera_manager().begin()).get());

    return true;
}

void GameScene::update()
{
    STRLSceneBase::update();
}

void GameScene::render()
{
    STRLSceneBase::render();
}
