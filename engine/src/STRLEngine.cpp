//
// Created by Sterling on 2/9/2024.
//

#include "STRLEngine.h"
#include "platform/glfw/GLFWPlatform.h"
#include "renderer/opengl/OpenGLRenderer.h"
#include "renderer/opengl/OpenGLShader.h"
#include "object/STRLObjectManager.h"
#include "config/STRLConfig.h"
#include "renderer/opengl/OpenGLShaderUtils.h"
#include "physics/box2D/Box2DContactListener.h"
#include "util/random/STRLRandom.h"
#include "strl-config.h"
#include "renderer/STRLCamera.h"
#include <glm/glm.hpp>
#include <format>

namespace strl
{

const double TIME_PER_UPDATE = 1.0f / 60.0f;

STRLEngine::STRLEngine()
	: window_width_(800), window_height_(600), window_name_("STRL Application")
{
	setup_platform();
	setup_renderer();
	setup_managers();
	setup_physics();
	STRLRandom::seed(time(nullptr));
}

STRLEngine::STRLEngine(int window_width, int window_height, std::string window_name)
	: window_width_(window_width), window_height_(window_height), window_name_(std::move(window_name))
{
	setup_platform();
	setup_renderer();
	setup_managers();
	setup_physics();
	STRLRandom::seed(time(nullptr));
}

void STRLEngine::run()
{
	// TODO: move this somewhere else
	std::vector<std::string> tags;
	OpenGLShader* shader = shader_manager_->create("Default", tags);
	shader->load();
	shader->bind();

	while (!platform_->window_should_close())
	{
		renderer_->clear();

		platform_->process_input();

		double current_update_time = platform_->get_time();
		double elapsed_time = current_update_time - previous_update_time_;
		previous_update_time_ = current_update_time;
		lag_ += elapsed_time;
		while (lag_ >= TIME_PER_UPDATE)
		{
			for (auto& script : *script_manager_)
			{
				if (!script->get_instance())
				{
					script->call_create_script();
				}
				script->get_instance()->on_update();
			}
			physics_->step();
			camera_.update_camera_vectors();
			lag_ -= TIME_PER_UPDATE;
		}


		OpenGLShaderUtils::set_mat4(shader->get_shader_program_id(), "view", camera_.get_view());
		OpenGLShaderUtils::set_mat4(shader->get_shader_program_id(), "projection", camera_.get_projection());


		physics_->reset_debug_draw();
		physics_->get_world()->DebugDraw();
		for (auto& render_data : *render_data_manager_)
		{
			renderer_->render(*render_data);
		}

		platform_->update();
	}

}

STRLObjectManager& STRLEngine::get_object_manager()
{
	return *object_manager_;
}

STRLScriptManager& STRLEngine::get_script_manager()
{
	return *script_manager_;
}

STRLEventManager& STRLEngine::get_event_manager()
{
	// TODO: don't do this the lazy way
	return platform_->get_event_manager();
}

Box2DPhysics& STRLEngine::get_physics()
{
	return *physics_;
}

void STRLEngine::set_background_color(float r, float g, float b, float a)
{
	renderer_->set_clear_color({r, g, b, a});
}

void STRLEngine::set_background_color(glm::vec4 color)
{
	renderer_->set_clear_color(color);
}

void STRLEngine::setup_platform()
{
	platform_ = std::make_unique<GLFWPlatform>(window_width_,
			window_height_, window_name_);

	STRLEventListenerFunction escape_key_quit = [&](STRLEvent* event)
	{
		platform_->set_window_should_close(true);
	};
	platform_->get_event_manager().register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED,
		STRL_KEY_ESCAPE, escape_key_quit, "Escape Key Press Exit App");

	STRLEventListenerFunction print_when_p_pressed = [&](STRLEvent* event)
	{
		std::cout << "P Pressed!" << std::endl;
	};
	platform_->get_event_manager().register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED,
		STRL_KEY_P, print_when_p_pressed, "P Key Press Print Stuff");

	// TODO: not here
	STRLEventListenerFunction rotate_left = [&](STRLEvent* event)
	{
		camera_.get_position() = {0.0f, 0.0f, 40.0f};
		camera_.get_euler_angles().z = 0.0f;
		camera_.get_euler_angles().y = 3 * glm::pi<float>() / 2.0f;
	};
	platform_->get_event_manager().register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED,
		STRL_KEY_Q, rotate_left, "Rotate Left");
	STRLEventListenerFunction rotate_right = [&](STRLEvent* event)
	{
		camera_.get_position() = glm::normalize(glm::vec3{1.0f, 1.0f, 1.0f}) * 40.0f;
		camera_.get_euler_angles().z = -glm::pi<float>() / 4.0f;
		camera_.get_euler_angles().y = 5 * glm::pi<float>() / 4.0f;
	};
	platform_->get_event_manager().register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED,
		STRL_KEY_E, rotate_right, "Rotate Right");
}

void STRLEngine::setup_renderer()
{
	renderer_ = std::make_unique<OpenGLRenderer>();
	render_data_manager_ = std::make_unique<OpenGLRenderDataManager>();
	std::vector<std::string> tags{"Engine Generated Render Data"};
	auto render_data = render_data_manager_->create("Engine Default", tags);
	renderer_->setup_render_data(*render_data);
}

void STRLEngine::setup_managers()
{
	object_manager_ = std::make_unique<STRLObjectManager>(*render_data_manager_, *renderer_);
	event_manager_ = std::make_unique<STRLEventManager>();
	script_manager_ = std::make_unique<STRLScriptManager>();
	shader_manager_ = std::make_unique<OpenGLShaderManager>();
}

void STRLEngine::setup_physics()
{
	auto render_data_debug_draw = render_data_manager_->create("Physics Debug Draw",
		std::vector<std::string>{"Physics"});
	renderer_->setup_render_data(*render_data_debug_draw);
	std::unique_ptr<Box2DDebugDraw> debug_draw = std::make_unique<Box2DDebugDraw>(*render_data_debug_draw);
	debug_draw->SetFlags(b2Draw::e_shapeBit);
	std::unique_ptr<Box2DContactListener> contact_listener = std::make_unique<Box2DContactListener>();
	physics_ = std::make_unique<Box2DPhysics>(0.0f, 0.0f, debug_draw, contact_listener);
}

} // strl