//
// Created by Sterling on 2/9/2024.
//

#include "STRLDriver.h"
#include "../../util/random/STRLRandom.h"
#include "strl-config.h"
#include <imgui.h>
#ifdef STRL_RENDER_API_OPENGL
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif

namespace strl
{

const double TIME_PER_UPDATE = 1.0f / 60.0f;

STRLDriver::STRLDriver(int window_width, int window_height, bool fullscreen, std::string window_name)
    : window_width_(window_width), window_height_(window_height), fullscreen_(fullscreen), window_name_(std::move(window_name))
{
	setup_platform();
	setup_renderer();
	setup_scene_manager();
	setup_imgui();
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
	previous_fps_time_ = platform_->get_time();
	while (!platform_->window_should_close())
	{
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug");

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

		double current_fps_time = platform_->get_time();
		double elapsed_fps_time = current_fps_time - previous_fps_time_;
		if (elapsed_fps_time > 1.0)
		{
			fps_ = calculate_fps(current_frames_);
			current_frames_ = 0;
			previous_fps_time_ = current_fps_time;
		}
		ImGui::Text("%lf", fps_);
		ImGui::Text("%d", current_frames_);

		scene_manager_->get_active_scene()->render();

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		platform_->update();

		current_frames_++;
	}
}

void STRLDriver::setup_platform()
{
	platform_ = std::make_unique<GLFWPlatform>(window_width_,
	                                           window_height_, fullscreen_, window_name_);

	STRLEventListenerFunction escape_key_quit = [&](STRLEvent* event) {
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

void STRLDriver::setup_imgui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
#ifdef STRL_RENDER_API_OPENGL
	ImGui_ImplGlfw_InitForOpenGL(platform_->get_window(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
#endif
}

double STRLDriver::calculate_fps(int current_frames)
{
	measurement_ = (measurement_ * smoothing_) + (static_cast<float>(current_frames) * (1.0f - smoothing_));
	return measurement_;
}

}// namespace strl
