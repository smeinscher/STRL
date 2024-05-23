//
// Created by Sterling on 3/1/2024.
//

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "strl/strl.h"

class GameScene : public strl::Scene
{
  public:
    using strl::Scene::STRLSceneBase;
    bool init() override;
    void update() override;
    void render() override;

  private:
    strl::ScriptHandler *player_script_handler_;

    strl::Animation2D animation2D_;

    double mouse_position_x_;
    double mouse_position_y_;
};

#endif // GAMESCENE_H
