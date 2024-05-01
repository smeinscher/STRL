//
// Created by Sterling on 3/6/2024.
//

#include <gtest/gtest.h>
#include "../../../src/renderer/opengl/OpenGLRenderer.h"

TEST(OpenGLRenderer_tests, OpenGLRendererInitNoPlatform)
{
	strl::OpenGLRenderer::init(800, 600);
}