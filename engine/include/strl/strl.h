//
// Created by Sterling on 2/7/2024.
//

#ifndef STRL_H
#define STRL_H

#include "../../src/object/STRLObject.h"
#include "../../src/STRLEngine.h"
#include "../../src/util/algorithm/RenderConversions.h"
#include "../../src/core/scripting/STRLNativeScriptHandler.h"
#include "../../src/core/scripting/premade/STRLMoveScript.h"
#include "../../src/config/STRLConfig.h"
#include "../../src/core/scripting/premade/STRLPlayerController.h"
#include "../../src/core/scripting/premade/STRLPhysics2DBase.h"
#include "../../src/core/scripting/premade/STRLBasicMovementPhysics2D.h"
#include "../../src/util/random/STRLRandom.h"

namespace strl
{
using ObjectManager = STRLObjectManager;

using ScriptHandler = STRLNativeScriptHandler;
using Script = ISTRLScript;
using Movable = STRLMoveScript;
using PlayerController = STRLPlayerController;
using PhysicsMovement = STRLBasicMovementPhysics2D;
using Physics2DBase = STRLPhysics2DBase;
using Physics2DMovementBase = STRLBasicMovementPhysics2D;

using PhysicsDefinitions = Box2DPhysicsDefinitions;

using Event = STRLEvent;
using EventListener = STRLEventListener;
using EventManager = STRLEventManager;
using EventListenerFunction = STRLEventListenerFunction;

using Random = STRLRandom;
}
#endif //STRL_H
