//
// Created by SterlingMeinscher on 3/1/2024.
//

#include "STRLRenderer.h"
#include "opengl/OpenGLRenderer.h"

namespace strl
{

STRLRenderer::STRLRenderer(STRLRenderAPI render_api, int viewport_width, int viewport_height)
	: active_render_api_(render_api)
{
	switch (active_render_api_)
	{
	case STRLRenderAPI::OpenGL:
		OpenGLRenderer::init(viewport_width, viewport_height);
		break;
	default:
		// TODO: logging stuff
		std::cout << "Invalid Render API" << std::endl;
		break;
	}
}

STRLRenderer::~STRLRenderer()
{

}

void STRLRenderer::clear(float r, float g, float b, float a)
{
	switch (active_render_api_)
	{
	case STRLRenderAPI::OpenGL:
		OpenGLRenderer::clear(r, g, b, a);
		break;
	default:
		// TODO: logging stuff
		std::cout << "Invalid Render API" << std::endl;
		break;
	}
}

} // strl