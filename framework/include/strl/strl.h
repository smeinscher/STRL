//
// Created by Sterling on 2/7/2024.
//

#ifndef STRL_H
#define STRL_H

#include "../../src/config/STRLConfig.h"
#include "../../src/core/animation/2D/STRLAnimation2D.h"
#include "../../src/core/driver/STRLDriver.h"
#include "../../src/core/object/STRLObject.h"
#include "../../src/core/scene/STRLSceneBase.h"
#include "../../src/core/scripting/STRLNativeScriptHandler.h"
#include "../../src/core/scripting/premade/STRLBasicMovementPhysics2D.h"
#include "../../src/core/scripting/premade/STRLMoveScript.h"
#include "../../src/core/scripting/premade/STRLPhysics2DBase.h"
#include "../../src/core/scripting/premade/STRLPlayerController.h"
#include "../../src/physics/box2D/Box2DPhysics.h"
#include "../../src/renderer/opengl/OpenGLShaderUtils.h"
#include "../../src/util/algorithm/RenderConversions.h"
#include "../../src/util/random/STRLRandom.h"

namespace strl
{

using Driver = STRLDriver;

using Object = STRLObject;
using ObjectDefinition = STRLObjectDefinition;
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

#ifdef STRL_RENDER_API_OPENGL
using Shader = OpenGLShader;
using ShaderUtils = OpenGLShaderUtils;
using ShaderManager = OpenGLShaderManager;
using RenderData = OpenGLRenderData;
using RenderDataManager = OpenGLRenderDataManager;
#endif

using Platform = IPlatform;

using Camera = STRLCamera;
using CameraManager = STRLManagerBase<STRLCamera>;

using Scene = STRLSceneBase;

using Animation2D = STRLAnimation2D;
using Animation2DState = STRLAnimation2DState;

} // namespace strl
#endif // STRL_H
