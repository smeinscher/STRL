//
// Created by SterlingMeinscher on 2/19/2024.
//

#ifndef BOX2DPHYSICS_H
#define BOX2DPHYSICS_H

#include "../../core/object/STRLObject.h"
#include "Box2DContactListener.h"
#include "Box2DDebugDraw.h"
#include <box2d/box2d.h>
#include <functional>
#include <memory>

namespace strl
{

struct Box2DPhysicsDefinitions
{
    b2BodyDef body_definition;
    b2FixtureDef fixture_definition;
};

struct Box2DBodyData
{
    std::function<void()> begin_contact = []() {};
    std::function<void()> end_contact = []() {};
};

class Box2DPhysics
{
  public:
    Box2DPhysics(float gravity_x, float gravity_y, OpenGLRenderData *debug_draw_render_data);

    void step(float time_step = 1.0f / 60.0f, int velocity_iterations = 6, int position_iterations = 2);

    b2Body *generate_default_body(STRLObject *object, Box2DBodyData *data = nullptr);
    static b2BodyDef generate_b2BodyDef(STRLObject *object, Box2DBodyData *data = nullptr);
    b2Body *create_body(b2BodyDef body_definition);
    static std::unique_ptr<b2Shape> generate_b2Shape(STRLObject *object);
    static b2FixtureDef generate_b2FixtureDef(b2Shape *shape);
    static void create_fixture(b2Body *body, b2FixtureDef fixture_definition);

    std::unique_ptr<b2World> &get_world();

    void prep_debug_render();

  private:
    std::unique_ptr<b2World> world_ = nullptr;
    std::unique_ptr<Box2DDebugDraw> debug_draw_ = nullptr;
    std::unique_ptr<Box2DContactListener> contact_listener_ = nullptr;
};

} // namespace strl

#endif // BOX2DPHYSICS_H
