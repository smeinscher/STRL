//
// Created by Sterling on 2/7/2024.
//

#ifndef STRLRENDERER_H
#define STRLRENDERER_H

#include <glm/glm.hpp>
#include <vector>
#include <array>

#include "opengl/OpenGLRenderer.h"

namespace strl
{

enum class STRLRenderAPI
{
	OpenGL,
	// Below APIs may or may not be implemented
	// Adding just in case
	Vulkan,
	Direct3D11,
	Direct3D12
};

using Color = std::array<float, 4>;

// Higher level rendering stuff
template <typename RENDER_DATA_TYPE>
class STRLRenderer
{
public:
	STRLRenderer(STRLRenderAPI render_api, int viewport_width, int viewport_height)
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

	~STRLRenderer() = default;

	void clear()
	{
		switch (active_render_api_)
		{
		case STRLRenderAPI::OpenGL:
			OpenGLRenderer::clear(clear_color_[0], clear_color_[1], clear_color_[2], clear_color_[3]);
			break;
		default:
			// TODO: logging stuff
			std::cout << "Invalid Render API" << std::endl;
			break;
		}
	}

	void set_clear_color(float r, float g, float b, float a)
	{
		clear_color_[0] = r;
		clear_color_[1] = g;
		clear_color_[2] = b;
		clear_color_[3] = a;
	}

	void render(RENDER_DATA_TYPE& render_data)
	{
		switch (active_render_api_)
		{
		case STRLRenderAPI::OpenGL:
			OpenGLRenderer::render(render_data);
			break;
		default:
			// TODO: logging stuff
			std::cout << "Invalid Render API" << std::endl;
			break;
		}
	}

	// TODO: implement these
	/*void quick_draw(std::vector<float> position, Color color = {1.0f, 1.0f, 1.0f, 1.0f});
	void quick_draw_line(float x1, float y1, float x2, float y2, Color color = {1.0f, 1.0f, 1.0f, 1.0f});
	void quick_draw_clear();*/


private:
	STRLRenderAPI active_render_api_;
	Color clear_color_{0.0f, 0.0f, 0.0f, 1.0f};
};

} // strl

#endif //STRLRENDERER_H
