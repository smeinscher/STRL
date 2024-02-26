//
// Created by SterlingMeinscher on 2/19/2024.
//

#include <functional>
#include "Box2DContactListener.h"

namespace strl
{
Box2DContactListener::~Box2DContactListener()
= default;

void Box2DContactListener::BeginContact(b2Contact* contact)
{
	b2BodyUserData body_a_user_data = contact->GetFixtureA()->GetBody()->GetUserData();
	b2BodyUserData body_b_user_data = contact->GetFixtureB()->GetBody()->GetUserData();
	if (body_a_user_data.pointer)
	{
		(*reinterpret_cast<std::function<void()>*>(body_a_user_data.pointer))();
	}
	if (body_b_user_data.pointer)
	{
		(*reinterpret_cast<std::function<void()>*>(body_b_user_data.pointer))();
	}
}

void Box2DContactListener::EndContact(b2Contact* contact)
{
	b2BodyUserData body_a_user_data = contact->GetFixtureA()->GetBody()->GetUserData();
	b2BodyUserData body_b_user_data = contact->GetFixtureB()->GetBody()->GetUserData();
	if (body_a_user_data.pointer)
	{

	}
	if (body_b_user_data.pointer)
	{

	}
}

void Box2DContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void Box2DContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
} // strl