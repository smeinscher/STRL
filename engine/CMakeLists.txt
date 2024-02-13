cmake_minimum_required(VERSION 3.27)
project(STRLEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
add_library(STRLEngine
        external/glad/glad.c
        src/platform/glfw/GLFWPlatform.cpp
        src/platform/glfw/GLFWPlatform.h
        src/platform/IPlatform.h
        src/platform/IPlatform.cpp
        src/renderer/opengl/OpenGLRenderer.cpp
        src/renderer/opengl/OpenGLRenderer.h
        src/renderer/IRenderer.h
        src/renderer/IRenderer.cpp
        src/renderer/opengl/OpenGLTexture.cpp
        src/renderer/opengl/OpenGLTexture.h
        src/renderer/opengl/OpenGLShader.cpp
        src/renderer/opengl/OpenGLShader.h
        src/renderer/ITexture.cpp
        src/renderer/ITexture.h
        src/renderer/IShader.cpp
        src/renderer/IShader.h
        src/object/STRLObject.cpp
        src/object/STRLObject.h
        src/object/STRLObjectManager.cpp
        src/object/STRLObjectManager.h
        src/object/STRLObjectRenderData.cpp
        src/object/STRLObjectRenderData.h
        src/STRLEngine.cpp
        src/STRLEngine.h
        src/renderer/opengl/OpenGLShaderUtils.cpp
        src/renderer/opengl/OpenGLShaderUtils.h
        src/util/algorithm/Triangulation.cpp
        src/util/algorithm/Triangulation.h
        src/util/manager/ISTRLManager.h
        src/util/observer/ISTRLObserver.h
        src/util/observer/ISTRLSubject.h
)

target_include_directories(STRLEngine
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_link_libraries(STRLEngine
        PUBLIC
        glm::glm
        PRIVATE
        glfw
        opengl32
)

set(ENGINE_DIRECTORY_LOCATION ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(strl-config.h.cmake strl-config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})