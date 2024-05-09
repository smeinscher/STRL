//
// Created by SterlingMeinscher on 2/19/2024.
//

#include "Box2DContactListener.h"
#include "Box2DPhysics.h"
#include <functional>

namespace strl
{
Box2DContactListener::~Box2DContactListener() = default;

void Box2DContactListener::BeginContact(b2Contact *contact)
{
    b2BodyUserData body_a_user_data = contact->GetFixtureA()->GetBody()->GetUserData();
    b2BodyUserData body_b_user_data = contact->GetFixtureB()->GetBody()->GetUserData();
    if (body_a_user_data.pointer)
    {
        reinterpret_cast<Box2DBodyData *>(body_a_user_data.pointer)->begin_contact();
    }
    if (body_b_user_data.pointer)
    {
        reinterpret_cast<Box2DBodyData *>(body_b_user_data.pointer)->begin_contact();
    }
}

void Box2DContactListener::EndContact(b2Contact *contact)
{
    b2BodyUserData body_a_user_data = contact->GetFixtureA()->GetBody()->GetUserData();
    b2BodyUserData body_b_user_data = contact->GetFixtureB()->GetBody()->GetUserData();
    if (body_a_user_data.pointer)
    {
        reinterpret_cast<Box2DBodyData *>(body_a_user_data.pointer)->end_contact();
    }
    if (body_b_user_data.pointer)
    {
        reinterpret_cast<Box2DBodyData *>(body_b_user_data.pointer)->end_contact();
    }
}

void Box2DContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
}

void Box2DContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
}
} // namespace strl
