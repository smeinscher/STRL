#include "Projectile.h"

Projectile::Projectile(strl::Object *object, strl::Object *parent, strl::ObjectManager *object_manager,
                       strl::Box2DPhysics *phyiscs, strl::Camera *main_camera, double *mouse_position_x,
                       double *mouse_position_y, strl::STRLScriptManager *script_manager, int script_id)
    : object_(object), parent_(parent), object_manager_(object_manager), physics_(phyiscs), main_camera_(main_camera),
      script_manager_(script_manager), mouse_position_x_(mouse_position_x), mouse_position_y_(mouse_position_y),
      script_id_(script_id)
{
}

void Projectile::on_create()
{
    physics_body_data_ = std::make_unique<strl::Box2DBodyData>();
    physics_body_data_->name = "Projectile";
    physics_body_data_->begin_contact = [this]() { script_manager_->remove(script_manager_->get_by_id(script_id_)); };
    b2BodyDef body_definition = strl::Box2DPhysics::generate_b2BodyDef(object_, physics_body_data_.get());
    body_definition.linearDamping = 0.0f;
    body_definition.angularDamping = 0.0f;
    physics_body_ = physics_->create_body(body_definition);
    std::unique_ptr<b2Shape> shape = strl::Box2DPhysics::generate_b2Shape(object_);
    b2FixtureDef fixture_definition = strl::Box2DPhysics::generate_b2FixtureDef(shape.get());
    fixture_definition.density = 4.0f;
    strl::Box2DPhysics::create_fixture(physics_body_, fixture_definition);
    float dx = *mouse_position_x_ + main_camera_->get_position().x - parent_->get_position().x;
    float dy = *mouse_position_y_ + main_camera_->get_position().y - parent_->get_position().y;
    float angle = atan2(dy, dx);
    object_->set_rotation({0.0f, 0.0f, angle});
    b2Vec2 start_position = {
        (object_->get_position().x + std::cos(angle) * (object_->get_size().x + parent_->get_size().x)) *
            strl::PHYSICS_SCALE,
        (object_->get_position().y + std::sin(angle) * (object_->get_size().y + parent_->get_size().y)) *
            strl::PHYSICS_SCALE};
    physics_body_->SetTransform(start_position, angle);
    physics_body_->SetLinearVelocity({std::cos(angle) * 200.0f, std::sin(angle) * 200.0f});
    object_->set_position_x(physics_body_->GetPosition().x / strl::PHYSICS_SCALE);
    object_->set_position_y(physics_body_->GetPosition().y / strl::PHYSICS_SCALE);
}

void Projectile::on_update()
{
    object_->set_position_x(physics_body_->GetPosition().x / strl::PHYSICS_SCALE);
    object_->set_position_y(physics_body_->GetPosition().y / strl::PHYSICS_SCALE);
}

void Projectile::on_destroy()
{
    physics_->mark_for_deletion(physics_body_);
    physics_body_ = nullptr;
    object_manager_->remove(object_);
    object_ = nullptr;
}
