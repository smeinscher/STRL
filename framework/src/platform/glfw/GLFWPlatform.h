//
// Created by Sterling on 2/7/2024.
//

#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H


#include "../../core/event/STRLEventManager.h"
#include "../IPlatform.h"
#include <string>

struct GLFWwindow;
namespace strl
{
class GLFWPlatform : public IPlatform
{
public:
	GLFWPlatform(int window_width, int window_height, bool fullscreen, std::string window_name);
	~GLFWPlatform() override;

	void process_input() override;
	void update() override;

	int get_window_width() override;
	void set_window_width(int width) override;
	int get_window_height() override;
	void set_window_height(int height) override;
	void set_window_width_and_height(int width, int height) override;

	bool window_should_close() override;
	void set_window_should_close(bool window_should_close) override;

	double get_time() override;

	STRLEventManager& get_event_manager() override;

	GLFWwindow* get_window();

	void toggle_fullscreen();

private:
	int window_width_, window_height_;
	bool fullscreen_;
	std::string window_name_;

	GLFWwindow* window_ = nullptr;
	STRLEventManager event_manager_;

	void init_and_setup_window();
	static void init_glfw_library();
	void create_glfw_window();
	static void init_glad_library();
	void setup_glfw_callbacks();

	void swap_glfw_buffers() const;
	static void poll_glfw_events();
};
}// namespace strl


#endif//GLFWPLATFORM_H
