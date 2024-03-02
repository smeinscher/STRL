//
// Created by SterlingMeinscher on 2/15/2024.
//

#include "OpenGLRenderDataManager.h"
#include "OpenGLRenderer.h"

namespace strl
{

OpenGLRenderDataManager::OpenGLRenderDataManager() = default;

OpenGLRenderDataManager::~OpenGLRenderDataManager()
{
	for (auto& item : items_)
	{
		OpenGLRenderer::remove_render_data_objects(*item);
	}
}

OpenGLRenderData* OpenGLRenderDataManager::create(std::string name,
	std::vector<std::string> tags,
	OpenGLShader* shader,
	STRLCamera* camera)
{
	OpenGLRenderData* render_data = STRLManagerBase<OpenGLRenderData>::create(
		std::move(name),std::move(tags), shader, camera);
	OpenGLRenderer::setup_render_data(*render_data);
	return render_data;
}

void OpenGLRenderDataManager::remove(OpenGLRenderData* render_data)
{
	OpenGLRenderer::remove_render_data_objects(*render_data);
	STRLManagerBase<OpenGLRenderData>::remove(render_data);
}

} // strl