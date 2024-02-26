//
// Created by Sterling on 2/7/2024.
//

#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H


#include <string>
#include "../PlatformBase.h"
#include "../../core/event/STRLEventManager.h"

struct GLFWwindow;
namespace strl
{
class GLFWPlatform : public PlatformBase
{
public:
	GLFWPlatform(int window_width, int window_height, std::string window_name);
	~GLFWPlatform() override;

	void process_input() override;
	void update() override;

	bool window_should_close() override;
	void set_window_should_close(bool window_should_close) override;

	double get_time() override;

	STRLEventManager& get_event_manager();

private:
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
} // strl


#endif //GLFWPLATFORM_H
