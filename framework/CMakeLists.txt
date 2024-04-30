cmake_minimum_required(VERSION 3.27)
project(STRLFramework)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
  set(OPENGL_LIB_NAME "opengl32")
endif (WIN32)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_library(STRLFramework
        external/glad/glad.c
        src/platform/glfw/GLFWPlatform.cpp
        src/platform/glfw/GLFWPlatform.h
        src/platform/IPlatform.h
        src/platform/IPlatform.cpp
        src/renderer/opengl/OpenGLRenderer.cpp
        src/renderer/opengl/OpenGLRenderer.h
        src/renderer/STRLRenderer.h
        src/renderer/STRLRenderer.cpp
        src/renderer/opengl/OpenGLTexture.cpp
        src/renderer/opengl/OpenGLTexture.h
        src/renderer/opengl/OpenGLShader.cpp
        src/renderer/opengl/OpenGLShader.h
        src/core/object/STRLObject.cpp
        src/core/object/STRLObject.h
        src/core/object/STRLObjectManager.cpp
        src/core/object/STRLObjectManager.h
        src/renderer/opengl/OpenGLRenderData.cpp
        src/renderer/opengl/OpenGLRenderData.h
        src/core/driver/STRLDriver.cpp
        src/core/driver/STRLDriver.h
        src/renderer/opengl/OpenGLShaderUtils.cpp
        src/renderer/opengl/OpenGLShaderUtils.h
        src/util/algorithm/RenderConversions.cpp
        src/util/algorithm/RenderConversions.h
        src/util/manager/STRLManagerBase.h
        src/util/observer/ISTRLObserver.h
        src/util/observer/STRLSubjectBase.h
        src/core/scripting/STRLNativeScriptHandler.cpp
        src/core/scripting/STRLNativeScriptHandler.h
        src/core/scripting/ISTRLScript.cpp
        src/core/scripting/ISTRLScript.h
        src/core/scripting/premade/STRLMoveScript.cpp
        src/core/scripting/premade/STRLMoveScript.h
        src/core/event/STRLEvent.h
        src/core/event/STRLEventManager.cpp
        src/core/event/STRLEventManager.h
        src/util/manager/STRLManagedItemBase.cpp
        src/util/manager/STRLManagedItemBase.h
        src/core/scripting/STRLScriptManager.cpp
        src/core/scripting/STRLScriptManager.h
        src/renderer/opengl/OpenGLRenderDataManager.cpp
        src/renderer/opengl/OpenGLRenderDataManager.h
        src/util/manager/STRLManagerBase.cpp
        src/util/observer/STRLSubjectBase.cpp
        src/core/event/STRLEventListenerManager.cpp
        src/core/event/STRLEventListenerManager.h
        src/core/event/STRLEventListener.cpp
        src/core/event/STRLEventListener.h
        src/core/event/STRLEvent.cpp
        src/core/scripting/premade/STRLPlayerController.cpp
        src/core/scripting/premade/STRLPlayerController.h
        src/config/STRLConfig.h
        src/physics/box2D/Box2DPhysics.cpp
        src/physics/box2D/Box2DPhysics.h
        src/core/scripting/premade/STRLPhysics2DBase.cpp
        src/core/scripting/premade/STRLPhysics2DBase.h
        src/core/scripting/premade/STRLBasicMovementPhysics2D.cpp
        src/core/scripting/premade/STRLBasicMovementPhysics2D.h
        src/physics/box2D/Box2DDebugDraw.cpp
        src/physics/box2D/Box2DDebugDraw.h
        src/util/random/STRLRandom.cpp
        src/util/random/STRLRandom.h
        src/physics/box2D/Box2DContactListener.cpp
        src/physics/box2D/Box2DContactListener.h
        external/stb/stb_image.c
        src/renderer/opengl/OpenGLShaderManager.cpp
        src/renderer/opengl/OpenGLShaderManager.h
        src/renderer/STRLCamera.cpp
        src/renderer/STRLCamera.h
        src/core/scene/STRLSceneBase.cpp
        src/core/scene/STRLSceneBase.h
        src/renderer/STRLCameraManager.cpp
        src/renderer/STRLCameraManager.h
        src/core/scene/STRLSceneManager.cpp
        src/core/scene/STRLSceneManager.h
)

target_include_directories(STRLFramework
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(STRLFramework
        PUBLIC
        glm::glm
        imgui::imgui
        PRIVATE
        glfw
        GL
        box2d::box2d
)

set(ENGINE_DIRECTORY_LOCATION ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(strl-config.h.cmake strl-config.h)

add_subdirectory(tst)
