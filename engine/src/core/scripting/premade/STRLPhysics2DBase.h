//
// Created by SterlingMeinscher on 2/19/2024.
//

#ifndef STRLPHYSICS2DBASE_H
#define STRLPHYSICS2DBASE_H

#include "../ISTRLScript.h"
#include "../../../object/STRLObject.h"
#include "../../../physics/box2D/Box2DPhysics.h"

namespace strl
{

class STRLPhysics2DBase : public ISTRLScript
{
public:
	STRLPhysics2DBase(STRLObject* object, Box2DPhysics* physics, Box2DPhysicsDefinitions physics_definitions = {});
	~STRLPhysics2DBase() override = default;
	void on_create() override;
	void on_update() override;
	void on_destroy() override;

protected:
	STRLObject* object_;
	Box2DPhysics* physics_;
	Box2DPhysicsDefinitions physics_definitions_;
	b2Body* body_ = nullptr;
};

} // strl

#endif //STRLPHYSICS2DBASE_H
