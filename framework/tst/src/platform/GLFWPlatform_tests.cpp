//
// Created by Sterling on 3/6/2024.
//

#include <gtest/gtest.h>

#include "../../../src/platform/glfw/GLFWPlatform.h"

TEST(GLFWPlatform_tests, WindowSize)
{
	std::unique_ptr<strl::GLFWPlatform> platform =
		std::make_unique<strl::GLFWPlatform>(800, 600, "Test");
	ASSERT_EQ(platform->get_window_width(), 800);
	ASSERT_EQ(platform->get_window_height(), 600);
}

TEST(GLFWPlatform_tests, WindowShouldClose)
{
	std::unique_ptr<strl::GLFWPlatform> platform =
		std::make_unique<strl::GLFWPlatform>(800, 600, "Test");
	platform->set_window_should_close(true);
	ASSERT_EQ(platform->window_should_close(), true);
}
