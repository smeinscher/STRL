//
// Created by Sterling on 3/1/2024.
//

#include "GameScene.h"
#include "../scripts/GameEntities.h"
#include "strl/strl.h"

bool GameScene::init()
{
    if (!STRLSceneBase::init())
    {
        return false;
    }
    (*get_camera_manager().begin())->set_is_ortho(true);
    set_background_color(0.6f, 0.1f, 0.2f, 1.0f);

    strl::ScriptHandler *game_entities_script_handler =
        get_script_manager().create("Game Entities Script", std::vector<std::string>{"Game Entities"});
    game_entities_script_handler->bind<GameEntities>(
        &get_object_manager(), &get_render_data_manager(), &get_event_manager(), &get_physics(), &get_platform(),
        (*get_shader_manager().begin()).get(), (*get_camera_manager().begin()).get(), &animation2D_,
        &get_script_manager());
    return true;
}

void GameScene::update()
{
    STRLSceneBase::update();
    animation2D_.update(0.016);
}

void GameScene::render()
{
    STRLSceneBase::render();
}
