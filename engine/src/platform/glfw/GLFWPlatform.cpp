//
// Created by Sterling on 2/7/2024.
//

#include "GLFWPlatform.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <format>
#include <utility>
#include <map>
#include "../../config/STRLConfig.h"

namespace strl
{
#define KEY_MAP_ITEM(name) {GLFW_KEY_##name, STRL_KEY_##name}

std::map<int, unsigned int> glfw_key_to_strl_key = {
	KEY_MAP_ITEM(LEFT_CONTROL),
	KEY_MAP_ITEM(RIGHT_CONTROL),
	KEY_MAP_ITEM(LEFT_SHIFT),
	KEY_MAP_ITEM(RIGHT_SHIFT),

	KEY_MAP_ITEM(TAB),

	KEY_MAP_ITEM(ESCAPE),

	KEY_MAP_ITEM(A),
	KEY_MAP_ITEM(B),
	KEY_MAP_ITEM(C),
	KEY_MAP_ITEM(D),
	KEY_MAP_ITEM(E),
	KEY_MAP_ITEM(F),
	KEY_MAP_ITEM(G),
	KEY_MAP_ITEM(H),
	KEY_MAP_ITEM(I),
	KEY_MAP_ITEM(J),
	KEY_MAP_ITEM(K),
	KEY_MAP_ITEM(L),
	KEY_MAP_ITEM(M),
	KEY_MAP_ITEM(N),
	KEY_MAP_ITEM(O),
	KEY_MAP_ITEM(P),
	KEY_MAP_ITEM(Q),
	KEY_MAP_ITEM(R),
	KEY_MAP_ITEM(S),
	KEY_MAP_ITEM(T),
	KEY_MAP_ITEM(U),
	KEY_MAP_ITEM(V),
	KEY_MAP_ITEM(W),
	KEY_MAP_ITEM(X),
	KEY_MAP_ITEM(Y),
	KEY_MAP_ITEM(Z)
};

const std::string FAILED_WINDOW_CREATION_MSG = "Failed to create GLFW window";
const std::string FAILED_GLAD_INIT_MSG = "Failed to initialize GLAD";

GLFWPlatform::GLFWPlatform(int window_width, int window_height, std::string window_name)
	: PlatformBase(window_width, window_height, std::move(window_name))
{
	init_and_setup_window();
}

GLFWPlatform::~GLFWPlatform()
{
	if (window_ != nullptr)
	{
		glfwDestroyWindow(window_);
	}
	glfwTerminate();
}

void GLFWPlatform::process_input()
{
	poll_glfw_events();
}

void GLFWPlatform::update()
{
	swap_glfw_buffers();
}

bool GLFWPlatform::window_should_close()
{
	return glfwWindowShouldClose(window_);
}

void GLFWPlatform::set_window_should_close(bool window_should_close)
{
	glfwSetWindowShouldClose(window_, window_should_close);
}

double GLFWPlatform::get_time()
{
	return glfwGetTime();
}

STRLEventManager& GLFWPlatform::get_event_manager()
{
	return event_manager_;
}

void GLFWPlatform::init_and_setup_window()
{
	init_glfw_library();
	create_glfw_window();
	init_glad_library();
	glfwSetWindowUserPointer(window_, this);
	setup_glfw_callbacks();

}

void GLFWPlatform::init_glfw_library()
{
	glfwInit();
	// TODO: in the future, we may want to support Vulkan. Support Vulkan setup option in future.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GLFWPlatform::create_glfw_window()
{
	window_ = glfwCreateWindow(window_width_, window_height_, window_name_.c_str(), nullptr, nullptr);
	if (window_ == nullptr)
	{
		throw std::runtime_error(FAILED_WINDOW_CREATION_MSG);
	}
	glfwMakeContextCurrent(window_);
}

void GLFWPlatform::init_glad_library()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error(FAILED_GLAD_INIT_MSG);
	}
}

void GLFWPlatform::setup_glfw_callbacks()
{
	glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height)
	{
		// TODO: anything OpenGL related needs to be in renderer
		//glViewport(0, 0, width, height);
	});
	glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		STRLEventType event_type;
		switch (action)
		{
		case GLFW_PRESS:
			event_type = STRLEventType::STRL_EVENT_KEY_PRESSED;
			break;
		case GLFW_RELEASE:
			event_type = STRLEventType::STRL_EVENT_KEY_RELEASED;
			break;
		case GLFW_REPEAT:
			event_type = STRLEventType::STRL_EVENT_KEY_REPEATED;
			break;
		default:
			event_type = STRLEventType::STRL_EVENT_UNKNOWN;
			//TODO: log unknown event type?
			break;
		}
		// TODO: check if an event not existing causes this to be a performance issue
		STRLEvent* event = reinterpret_cast<GLFWPlatform*>(
			glfwGetWindowUserPointer(window))->get_event_manager().get_by_event_code(event_type,
				glfw_key_to_strl_key[key]);
		if (event)
		{
			event->fire_event();
		}
	});
}

void GLFWPlatform::swap_glfw_buffers() const
{
	glfwSwapBuffers(window_);
}

void GLFWPlatform::poll_glfw_events()
{
	glfwPollEvents();
}

} // strl