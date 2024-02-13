//
// Created by Sterling on 2/7/2024.
//

#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H


#include <string>
#include "../IPlatform.h"

struct GLFWwindow;
namespace strl
{
class GLFWPlatform : public IPlatform
{
public:
	GLFWPlatform(int window_width, int window_height, std::string window_name);
	~GLFWPlatform() override;

	bool window_should_close() override;

	void process_input() override;
	void update() const override;

private:
	GLFWwindow* window_;

	void swap_buffers() const;
	static void poll_events();
};
} // strl


#endif //GLFWPLATFORM_H
