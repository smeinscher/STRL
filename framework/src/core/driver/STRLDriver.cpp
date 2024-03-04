//
// Created by Sterling on 2/9/2024.
//

#include "STRLDriver.h"
#include "../../util/random/STRLRandom.h"
#include "strl-config.h"
#include <format>

namespace strl
{

const double TIME_PER_UPDATE = 1.0f / 60.0f;

STRLDriver::STRLDriver(int window_width, int window_height, std::string window_name)
	: window_width_(window_width), window_height_(window_height), window_name_(std::move(window_name))
{
	setup_platform();
	setup_renderer();
	setup_scene_manager();
	STRLRandom::seed(time(nullptr));
}

void STRLDriver::set_active_scene(int id)
{
	scene_manager_->set_active_scene(id);
}

void STRLDriver::set_active_scene(std::string_view name)
{
	scene_manager_->set_active_scene(name);
}

STRLSceneManager& STRLDriver::get_scene_manager()
{
	return *scene_manager_;
}

void STRLDriver::run()
{
	scene_manager_->get_active_scene()->init();
	while (!platform_->window_should_close())
	{
		platform_->process_input();

		double current_update_time = platform_->get_time();
		double elapsed_time = current_update_time - previous_update_time_;
		previous_update_time_ = current_update_time;
		lag_ += elapsed_time;
		while (lag_ >= TIME_PER_UPDATE)
		{
			scene_manager_->get_active_scene()->update();
			lag_ -= TIME_PER_UPDATE;
		}

		scene_manager_->get_active_scene()->render();

		platform_->update();
	}

}

void STRLDriver::setup_platform()
{
	platform_ = std::make_unique<GLFWPlatform>(window_width_,
			window_height_, window_name_);

	STRLEventListenerFunction escape_key_quit = [&](STRLEvent* event)
	{
		platform_->set_window_should_close(true);
	};
	platform_->get_event_manager().register_event_listener(STRLEventType::STRL_EVENT_KEY_PRESSED,
		STRL_KEY_ESCAPE, escape_key_quit, "Escape Key Press Exit App");
}

void STRLDriver::setup_renderer()
{
	renderer_ = std::make_unique<STRLRenderer<OpenGLRenderData>>(STRLRenderAPI::OpenGL,
		window_width_, window_height_);
}

void STRLDriver::setup_scene_manager()
{
	scene_manager_ = std::make_unique<STRLSceneManager>();
}

} // strl