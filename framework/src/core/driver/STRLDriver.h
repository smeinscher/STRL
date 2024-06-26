//
// Created by Sterling on 2/9/2024.
//

#ifndef STRLDRIVER_H
#define STRLDRIVER_H

#include "../../platform/glfw/GLFWPlatform.h"
#include "../../renderer/STRLRenderer.h"
#include "../scene/STRLSceneManager.h"
#include <memory>
#include <string>

namespace strl
{

class STRLDriver
{
public:
	STRLDriver(int window_width, int window_height, bool fullscreen = false, std::string window_name = "STRL Application");

	// Returns the ID of the scene
	template<typename SCENE_TYPE, typename... ARGS>
	int create_scene(std::string name, std::vector<std::string> tags, ARGS... args)
	{
		STRLSceneBase* scene = scene_manager_->create<SCENE_TYPE>(
		    std::move(name), std::move(tags), args..., platform_.get(), renderer_.get());
		return scene->get_id();
	}
	void set_active_scene(int id);
	void set_active_scene(std::string_view name);
	STRLSceneManager& get_scene_manager();

	void run();

private:
	int window_width_, window_height_;
	bool fullscreen_;
	std::string window_name_;
	double previous_update_time_ = 0.0;

	double lag_ = 0.0;
	// TODO: make these not platform/render API specific
	std::unique_ptr<GLFWPlatform> platform_;

#ifdef STRL_RENDER_API_OPENGL
	std::unique_ptr<STRLRenderer<OpenGLRenderData>> renderer_;
#endif
	std::unique_ptr<STRLSceneManager> scene_manager_;

	float smoothing_ = 0.9f;
	float measurement_ = 0.0f;
	int current_frames_ = 0;
	double previous_fps_time_ = 0.0;
	double fps_ = 0.0;

	void setup_platform();
	void setup_renderer();
	void setup_scene_manager();
	void setup_imgui();

	double calculate_fps(int current_frames);
};

}// namespace strl

#endif//STRLDRIVER_H
