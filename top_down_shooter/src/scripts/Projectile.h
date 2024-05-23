#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "strl/strl.h"

class Projectile : public strl::Script
{
  public:
    Projectile(strl::Object *object, strl::Object *parent, strl::ObjectManager *object_manager,
               strl::Box2DPhysics *phyiscs, strl::Camera *main_camera, double *mouse_position_x,
               double *mouse_position_y, strl::STRLScriptManager *script_manager, int script_id);
    void on_create() override;
    void on_update() override;
    void on_destroy() override;

  private:
    strl::Object *object_;
    strl::Object *parent_;
    b2Body *physics_body_ = nullptr;
    strl::ObjectManager *object_manager_;
    strl::Box2DPhysics *physics_;
    strl::Camera *main_camera_;
    strl::STRLScriptManager *script_manager_;

    double *mouse_position_x_;
    double *mouse_position_y_;

    std::unique_ptr<strl::Box2DBodyData> physics_body_data_;

    int script_id_;

    bool should_destroy_ = false;
};

#endif // PROJECTILE_H
