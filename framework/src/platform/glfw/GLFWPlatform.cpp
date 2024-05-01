//
// Created by Sterling on 2/7/2024.
//

#include "GLFWPlatform.h"
#include "../../renderer/opengl/OpenGLRenderer.h"
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <map>
#include <utility>

namespace strl
{

#define KEY_MAP_ITEM(name)               \
	{                                    \
		GLFW_KEY_##name, STRL_KEY_##name \
	}

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
    KEY_MAP_ITEM(Z)};

std::map<int, int> glfw_mouse_button_to_strl_mouse_button = {
    {GLFW_MOUSE_BUTTON_1, STRL_MOUSE_BUTTON_0},
    {GLFW_MOUSE_BUTTON_2, STRL_MOUSE_BUTTON_1},
    {GLFW_MOUSE_BUTTON_3, STRL_MOUSE_BUTTON_2},
    {GLFW_MOUSE_BUTTON_4, STRL_MOUSE_BUTTON_3},
    {GLFW_MOUSE_BUTTON_5, STRL_MOUSE_BUTTON_4},
    {GLFW_MOUSE_BUTTON_6, STRL_MOUSE_BUTTON_5},
    {GLFW_MOUSE_BUTTON_7, STRL_MOUSE_BUTTON_6},
    {GLFW_MOUSE_BUTTON_8, STRL_MOUSE_BUTTON_7},
    {GLFW_MOUSE_BUTTON_LEFT, STRL_MOUSE_BUTTON_LEFT},
    {GLFW_MOUSE_BUTTON_RIGHT, STRL_MOUSE_BUTTON_RIGHT},
    {GLFW_MOUSE_BUTTON_MIDDLE, STRL_MOUSE_BUTTON_MIDDLE}};

const std::string FAILED_WINDOW_CREATION_MSG = "Failed to create GLFW window";
const std::string FAILED_GLAD_INIT_MSG = "Failed to initialize GLAD";

GLFWPlatform::GLFWPlatform(int window_width, int window_height, bool fullscreen, std::string window_name)
    : window_width_(window_width), window_height_(window_height), fullscreen_(fullscreen), window_name_(std::move(window_name))
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
	OpenGLRenderer::set_platform_exists_flag(false);
}

void GLFWPlatform::process_input()
{
	poll_glfw_events();
}

void GLFWPlatform::update()
{
	swap_glfw_buffers();
}

int GLFWPlatform::get_window_width()
{
	return window_width_;
}

void GLFWPlatform::set_window_width(int width)
{
	window_width_ = width;
}

int GLFWPlatform::get_window_height()
{
	return window_height_;
}

void GLFWPlatform::set_window_height(int height)
{
	window_height_ = height;
}

void GLFWPlatform::set_window_width_and_height(int width, int height)
{
	window_width_ = width;
	window_height_ = height;
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

GLFWwindow* GLFWPlatform::get_window()
{
	return window_;
}

void GLFWPlatform::toggle_fullscreen()
{
	GLFWmonitor* monitor = glfwGetWindowMonitor(window_);
	if (monitor)
	{
		glfwSetWindowMonitor(window_, NULL, window_width_ / 2.0f, window_height_ / 2.0f, window_width_, window_height_, 0);
	}
	else
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowMonitor(window_, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
	}
}

void GLFWPlatform::init_and_setup_window()
{
	init_glfw_library();
	create_glfw_window();
	glfwSwapInterval(1);
	init_glad_library();
	glfwSetWindowUserPointer(window_, this);
	setup_glfw_callbacks();
	OpenGLRenderer::set_platform_exists_flag(true);
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
	window_ = glfwCreateWindow(window_width_, window_height_, window_name_.c_str(), fullscreen_ ? glfwGetPrimaryMonitor() : nullptr, nullptr);
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
	glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
		reinterpret_cast<GLFWPlatform*>(glfwGetWindowUserPointer(window))->set_window_width_and_height(width, height);
	});
	glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
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
		                       glfwGetWindowUserPointer(window))
		                       ->get_event_manager()
		                       .get_by_event_code(event_type,
		                                          glfw_key_to_strl_key[key]);
		if (event)
		{
			event->fire_event(&mods);
		}
	});
	glfwSetScrollCallback(window_, [](GLFWwindow* window, double xoffset, double yoffset) {
		STRLEvent* event = reinterpret_cast<GLFWPlatform*>(
		                       glfwGetWindowUserPointer(window))
		                       ->get_event_manager()
		                       .get_by_event_code(
		                           STRLEventType::STRL_EVENT_MOUSE_WHEEL, 0);
		if (event)
		{
			STRLMouseScrollEventData data{};
			data.x_offset = xoffset;
			data.y_offset = yoffset;
			event->fire_event(&data);
		}
	});
	glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
		STRLEventType event_type;
		switch (action)
		{
		case GLFW_PRESS:
			event_type = STRLEventType::STRL_EVENT_MOUSE_BUTTON_PRESSED;
			break;
		case GLFW_RELEASE:
			event_type = STRLEventType::STRL_EVENT_MOUSE_BUTTON_RELEASED;
			break;
		case GLFW_REPEAT:
			event_type = STRLEventType::STRL_EVENT_MOUSE_BUTTON_REPEATED;
			break;
		default:
			event_type = STRLEventType::STRL_EVENT_UNKNOWN;
			//TODO: log unknown event type?
			break;
		}
		STRLEvent* event = reinterpret_cast<GLFWPlatform*>(
		                       glfwGetWindowUserPointer(window))
		                       ->get_event_manager()
		                       .get_by_event_code(
		                           event_type, glfw_mouse_button_to_strl_mouse_button[button]);
		if (event)
		{
			event->fire_event(&mods);
		}
	});
	glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xpos, double ypos) {
		STRLEvent* event = reinterpret_cast<GLFWPlatform*>(
		                       glfwGetWindowUserPointer(window))
		                       ->get_event_manager()
		                       .get_by_event_code(
		                           STRLEventType::STRL_EVENT_MOUSE_MOVED, 0);
		if (event)
		{
			STRLMouseMoveEventData data{};
			data.x_pos = xpos;
			data.y_pos = ypos;
			event->fire_event(&data);
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

}// namespace strl
