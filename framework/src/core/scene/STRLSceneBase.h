//
// Created by SterlingMeinscher on 3/1/2024.
//

#ifndef STRLSCENEBASE_H
#define STRLSCENEBASE_H

#include "../../config/STRLConfig.h"
#include "../../physics/box2D/Box2DPhysics.h"
#include "../../platform/IPlatform.h"
#include "../../renderer/STRLCameraManager.h"
#include "../../renderer/STRLRenderer.h"
#include "../../renderer/opengl/OpenGLRenderDataManager.h"
#include "../../renderer/opengl/OpenGLShaderManager.h"
#include "../event/STRLEventManager.h"
#include "../object/STRLObjectManager.h"
#include "../scripting/STRLScriptManager.h"
#include <memory>

namespace strl
{

class STRLSceneBase : public STRLManagedItemBase
{
  public:
    // Some stuff may carry over from other scenes
    STRLSceneBase(std::string name, std::vector<std::string> tags, IPlatform *platform,
#ifdef STRL_RENDER_API_OPENGL
                  STRLRenderer<OpenGLRenderData> *renderer,
                  std::unique_ptr<OpenGLShaderManager> shader_manager = nullptr,
                  std::unique_ptr<OpenGLRenderDataManager> render_data_manager = nullptr,
#endif
                  std::unique_ptr<STRLObjectManager> object_manager = nullptr,
                  std::unique_ptr<STRLCameraManager> camera_manager = nullptr,
                  std::unique_ptr<STRLScriptManager> script_manager = nullptr,
                  std::unique_ptr<Box2DPhysics> physics = nullptr);
    ~STRLSceneBase();

    virtual bool init();
    virtual void update();
    virtual void render();

#ifdef STRL_RENDER_API_OPENGL
    OpenGLShaderManager &get_shader_manager();
    OpenGLRenderDataManager &get_render_data_manager();
#endif
    STRLObjectManager &get_object_manager();
    STRLCameraManager &get_camera_manager();
    STRLScriptManager &get_script_manager();
    STRLEventManager &get_event_manager();
    Box2DPhysics &get_physics();
    IPlatform &get_platform();

  protected:
    void create_default_shader();
    void create_default_camera();
    void create_default_render_data();
    void enable_physics(bool debug_draw_enabled = false, STRLCamera *camera = nullptr);

    void script_update();
    void physics_step();
    void render_clear();
    void prep_debug_render();
    void render_draw();

    // Platform functionality we want to give user
    // TODO: remove these
    double get_time();
    void quit_application();
    int get_window_width();
    int get_window_height();

    // Render functionality we want to give to user
    void set_background_color(float r, float g, float b, float a);
    void set_background_color(glm::vec4 color);

  private:
    std::unique_ptr<OpenGLShaderManager> shader_manager_;
    std::unique_ptr<OpenGLRenderDataManager> render_data_manager_;
    std::unique_ptr<STRLObjectManager> object_manager_;
    std::unique_ptr<STRLCameraManager> camera_manager_;
    std::unique_ptr<STRLScriptManager> script_manager_;
    std::unique_ptr<Box2DPhysics> physics_;

    IPlatform *platform_;
    STRLRenderer<OpenGLRenderData> *renderer_;
};

} // namespace strl

#endif // STRLSCENEBASE_H
