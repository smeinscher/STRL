//
// Created by Sterling on 2/9/2024.
//

#ifndef STRLENGINE_H
#define STRLENGINE_H

#include <string>
#include <memory>
#include "platform/PlatformBase.h"
#include "renderer/IRenderer.h"
#include "object/STRLObject.h"
#include "object/STRLObjectManager.h"
#include "renderer/opengl/OpenGLRenderDataManager.h"
#include "renderer/opengl/OpenGLRenderer.h"
#include "core/event/STRLEventManager.h"
#include "core/scripting/STRLScriptManager.h"
#include "platform/glfw/GLFWPlatform.h"
#include "physics/box2D/Box2DPhysics.h"
#include "renderer/opengl/OpenGLShaderManager.h"
#include "renderer/STRLCamera.h"

namespace strl
{

class STRLEngine
{
public:
	STRLEngine();
	STRLEngine(int window_width, int window_height, std::string window_name = "STRL Application");

	void run();

	STRLObjectManager& get_object_manager();
	STRLScriptManager& get_script_manager();
	STRLEventManager& get_event_manager();
	Box2DPhysics& get_physics();
	OpenGLShaderManager& get_shader_manager();
	STRLManagerBase<STRLCamera>& get_camera_manager();

	// TODO: do this elsewhere
	void set_background_color(float r, float g, float b, float a);
	void set_background_color(glm::vec4 color);

private:
	int window_width_, window_height_;
	std::string window_name_;

	double previous_update_time_ = 0.0;
	double lag_ = 0.0;

	// TODO: make these not platform/render API specific
	std::unique_ptr<GLFWPlatform> platform_;
	std::unique_ptr<OpenGLRenderer> renderer_;
	std::unique_ptr<OpenGLRenderDataManager> render_data_manager_;
	std::unique_ptr<STRLObjectManager> object_manager_;
	std::unique_ptr<STRLEventManager> event_manager_;

	std::unique_ptr<STRLScriptManager> script_manager_;

	// TODO: put this elsewhere
	std::unique_ptr<Box2DPhysics> physics_;

	std::unique_ptr<OpenGLShaderManager> shader_manager_;

	// TODO: consider making class instead of using STRLManagerBase directly
	std::unique_ptr<STRLManagerBase<STRLCamera>> camera_manager_;

	void setup_platform();
	void setup_renderer();
	void setup_managers();
	void setup_physics();
};

} // strl

#endif //STRLENGINE_H
