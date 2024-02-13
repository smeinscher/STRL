//
// Created by Sterling on 2/9/2024.
//

#include "STRLEngine.h"
#include "platform/glfw/GLFWPlatform.h"
#include "renderer/opengl/OpenGLRenderer.h"
#include "renderer/IShader.h"
#include "renderer/opengl/OpenGLShader.h"
#include "object/STRLObjectManager.h"

namespace strl
{

STRLEngine::STRLEngine(int window_width, int window_height, std::string window_name)
	: window_width_(window_width), window_height_(window_height), window_name_(std::move(window_name))
{
	platform_ =
		std::make_unique<GLFWPlatform>(window_width_, window_height_, window_name_);
	renderer_ = std::make_unique<OpenGLRenderer>();
	object_manager_ = std::make_unique<STRLObjectManager>(renderer_.get());
}

ISTRLManager<STRLObject, STRLObjectDefinition>& STRLEngine::get_object_manager()
{
	return *object_manager_;
}

void STRLEngine::run()
{
	// TODO: move this somewhere else
	std::unique_ptr<IShader> shader = std::make_unique<OpenGLShader>();
	shader->load();
	shader->bind();
	while (!platform_->window_should_close())
	{
		renderer_->clear();

		platform_->process_input();

		renderer_->render();

		platform_->update();
	}

}

} // strl