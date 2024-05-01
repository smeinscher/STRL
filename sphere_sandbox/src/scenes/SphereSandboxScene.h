//
// Created by Sterling on 3/9/2024.
//

#ifndef SPHERESANDBOXSCENE_H
#define SPHERESANDBOXSCENE_H

#include "../states/States.h"
#include "strl/strl.h"

class SphereSandboxScene : public strl::Scene
{
  public:
    using strl::Scene::STRLSceneBase;
    bool init() override;
    void update() override;
    void render() override;

  private:
    strl::Object *planet_ = nullptr;
    std::vector<strl::ScriptHandler *> units_;
    strl::Object *selection_rect_ = nullptr;
    States states_;

    strl::ScriptHandler *current_formation_ = nullptr;

    glm::vec3 planet_up_ = {0.0f, 1.0f, 0.0f};
    glm::vec3 direction_;
    glm::vec3 right_ = {1.0f, 0.0f, 0.0f};
    glm::vec3 up_ = {0.0f, 1.0f, 0.0f};

    glm::vec3 mouse_click_ray_cast_nds();
    glm::vec3 mouse_click_ray_cast();
    glm::vec3 ray_cast_nds_to_world(glm::vec3 ray_nds);
};

#endif // SPHERESANDBOXSCENE_H
