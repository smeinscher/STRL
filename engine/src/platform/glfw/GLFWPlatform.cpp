//
// Created by Sterling on 2/7/2024.
//

#include "GLFWPlatform.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace strl
{
GLFWPlatform::GLFWPlatform(int window_width, int window_height, std::string window_name)
	: IPlatform(window_width, window_height, std::move(window_name))
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(window_width, window_height, window_name_.c_str(), nullptr, nullptr);
	if (window_ == nullptr)
	{
		// TODO: logging stuff
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// TODO: logging stuff
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwDestroyWindow(window_);
		glfwTerminate();
		return;
	}

	glViewport(0, 0, window_width, window_height);
	glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	});

}

GLFWPlatform::~GLFWPlatform()
{
	glfwDestroyWindow(window_);
	glfwTerminate();
}

bool GLFWPlatform::window_should_close()
{
	return glfwWindowShouldClose(window_);
}

void GLFWPlatform::process_input()
{
	if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window_, true);
	}
}

void GLFWPlatform::update() const
{
	swap_buffers();
	poll_events();
}

void GLFWPlatform::swap_buffers() const
{
	glfwSwapBuffers(window_);
}

void GLFWPlatform::poll_events()
{
	glfwPollEvents();
}

} // strl