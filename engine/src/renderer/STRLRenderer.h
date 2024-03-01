//
// Created by Sterling on 2/7/2024.
//

#ifndef STRLRENDERER_H
#define STRLRENDERER_H

#include <glm/glm.hpp>
#include <vector>
#include "opengl/OpenGLRenderData.h"

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

// Higher level rendering stuff
class STRLRenderer
{
public:
	STRLRenderer(STRLRenderAPI render_api, int viewport_width, int viewport_height);
	~STRLRenderer();

	void clear(float r, float g, float b, float a);

	void render();

	void quick_draw(std::vector<float> position, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});
	void quick_draw_line(float x1, float y1, float x2, float y2, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});
	void quick_draw_clear();


private:
	STRLRenderAPI active_render_api_;
};

} // strl

#endif //STRLRENDERER_H
