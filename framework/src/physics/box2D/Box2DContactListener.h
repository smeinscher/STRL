//
// Created by SterlingMeinscher on 2/19/2024.
//

#ifndef BOX2DCONTACTLISTENER_H
#define BOX2DCONTACTLISTENER_H

#include <box2d/box2d.h>

namespace strl
{

class Box2DContactListener : public b2ContactListener
{
public:
	~Box2DContactListener() override;
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};

} // strl

#endif //BOX2DCONTACTLISTENER_H
