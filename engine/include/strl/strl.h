//
// Created by Sterling on 2/7/2024.
//

#ifndef STRL_H
#define STRL_H

#include "../../src/core/object/STRLObject.h"
#include "../../src/core/driver/STRLDriver.h"
#include "../../src/util/algorithm/RenderConversions.h"
#include "../../src/core/scripting/STRLNativeScriptHandler.h"
#include "../../src/core/scripting/premade/STRLMoveScript.h"
#include "../../src/config/STRLConfig.h"
#include "../../src/core/scripting/premade/STRLPlayerController.h"
#include "../../src/core/scripting/premade/STRLPhysics2DBase.h"
#include "../../src/core/scripting/premade/STRLBasicMovementPhysics2D.h"
#include "../../src/util/random/STRLRandom.h"
#include "../../src/core/scene/STRLSceneBase.h"

namespace strl
{
using Driver = STRLDriver;

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

using Shader = OpenGLShader;
using ShaderManager = OpenGLShaderManager;

using Camera = STRLCamera;
using CameraManager = STRLManagerBase<STRLCamera>;

using Scene = STRLSceneBase;
}
#endif //STRL_H
