#ifndef GAMEENTIEIS_H
#define GAMEENTIEIS_H

#include <memory>
#include <strl/strl.h>

struct Entity
{
    strl::Object *top = nullptr;
    strl::Object *middle = nullptr;
    strl::Object *bottom = nullptr;

    b2Body *physics_body = nullptr;

    std::unique_ptr<strl::Box2DBodyData> physics_body_data;

    float current_speed = 100.0f;

    int selected_weapon = 0;
};

class GameEntities : public strl::Script
{
  public:
    GameEntities(strl::ObjectManager *object_manager, strl::RenderDataManager *render_data_manager,
                 strl::EventManager *event_manager, strl::Box2DPhysics *physics, strl::Platform *platform,
                 strl::Shader *shader, strl::Camera *main_camera, strl::Animation2D *animation2D,
                 strl::STRLScriptManager *script_manager);
    void on_create() override;
    void on_update() override;
    void on_destroy() override;

  private:
    std::vector<std::unique_ptr<Entity>> entities_;
    Entity *player_controlled_entity_ = nullptr;
    Entity *focused_entity_ = nullptr;
    strl::ObjectManager *object_manager_;
    strl::RenderDataManager *render_data_manager_;
    strl::EventManager *event_manager_;
    strl::Box2DPhysics *physics_;
    strl::Platform *platform_;

    strl::Shader *shader_;
    strl::Camera *main_camera_;

    strl::Animation2D *animation2D_;

    strl::STRLScriptManager *script_manager_;

    bool is_pressing_up_ = false;
    bool is_pressing_down_ = false;
    bool is_pressing_left_ = false;
    bool is_pressing_right_ = false;

    double mouse_position_x_ = 0.0;
    double mouse_position_y_ = 0.0;
};

#endif // GAMEENTIEIS_H
