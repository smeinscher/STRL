//
// Created by SterlingMeinscher on 3/1/2024.
//

#include "STRLSceneBase.h"

namespace strl
{
STRLSceneBase::STRLSceneBase(std::string name,
	std::vector<std::string> tags,
	IPlatform* platform,
#ifdef STRL_RENDER_API_OPENGL
	STRLRenderer<OpenGLRenderData>* renderer,
	std::unique_ptr<OpenGLShaderManager> shader_manager,
	std::unique_ptr<OpenGLRenderDataManager> render_data_manager,
#endif
	std::unique_ptr<STRLObjectManager> object_manager,
	std::unique_ptr<STRLCameraManager> camera_manager,
	std::unique_ptr<STRLScriptManager> script_manager,
	std::unique_ptr<Box2DPhysics> physics
	)
	: STRLManagedItemBase(std::move(name), std::move(tags)),
	  platform_(platform), renderer_(renderer),
	  object_manager_(std::move(object_manager)), camera_manager_(std::move(camera_manager)),
	  script_manager_(std::move(script_manager)), shader_manager_(std::move(shader_manager)),
	  render_data_manager_(std::move(render_data_manager)), physics_(std::move(physics))
{
	if (shader_manager_ == nullptr)
	{
#ifdef STRL_RENDER_API_OPENGL
		shader_manager_ = std::make_unique<OpenGLShaderManager>();
#endif
	}
	if (render_data_manager_ == nullptr)
	{
#ifdef STRL_RENDER_API_OPENGL
		render_data_manager_ = std::make_unique<OpenGLRenderDataManager>();
#endif
	}
	if (object_manager_ == nullptr)
	{
		object_manager_ = std::make_unique<STRLObjectManager>(*render_data_manager_);
	}
	if (camera_manager_ == nullptr)
	{
		camera_manager_ = std::make_unique<STRLCameraManager>();
	}
	if (script_manager_ == nullptr)
	{
		script_manager_ = std::make_unique<STRLScriptManager>();
	}
}

bool STRLSceneBase::init()
{
	create_default_shader();
	create_default_camera();
	create_default_render_data();
	enable_physics();
	return true;
}

void STRLSceneBase::update()
{
	script_update();
	physics_step();
}

void STRLSceneBase::render()
{
	render_clear();
	prep_debug_render();
	render_draw();
}

OpenGLShaderManager& STRLSceneBase::get_shader_manager()
{
	return *shader_manager_;
}

OpenGLRenderDataManager& STRLSceneBase::get_render_data_manager()
{
	return *render_data_manager_;
}

STRLObjectManager& STRLSceneBase::get_object_manager()
{
	return *object_manager_;
}

STRLCameraManager& STRLSceneBase::get_camera_manager()
{
	return *camera_manager_;
}

STRLScriptManager& STRLSceneBase::get_script_manager()
{
	return *script_manager_;
}

STRLEventManager& STRLSceneBase::get_event_manager()
{
	return platform_->get_event_manager();
}

Box2DPhysics& STRLSceneBase::get_physics()
{
	return *physics_;
}

void STRLSceneBase::create_default_shader()
{
	std::vector<std::string> shader_tags = {"Engine Generated Shader"};
#ifdef STRL_RENDER_API_OPENGL
	OpenGLShader* shader = shader_manager_->create("Engine Default", shader_tags);
#endif
	shader->load();
}

void STRLSceneBase::create_default_camera()
{
	std::vector<std::string> camera_tags = {"Engine Generated Camera"};
	camera_manager_->create("Engine Default", camera_tags,
		platform_->get_window_width(), platform_->get_window_height());
}

void STRLSceneBase::create_default_render_data()
{
	std::vector<std::string> rd_tags{"Engine Generated Render Data"};
#ifdef STRL_RENDER_API_OPENGL
	OpenGLShader* shader = shader_manager_->get_by_name("Engine Default")[0];
#endif
	if (!shader)
	{
		create_default_shader();
		shader = shader_manager_->get_by_name("Engine Default")[0];
	}
	STRLCamera* camera = camera_manager_->get_by_name("Engine Default")[0];
	if (!camera)
	{
		create_default_camera();
		camera = camera_manager_->get_by_name("Engine Default")[0];
	}
	OpenGLRenderData* render_data = render_data_manager_->create("Engine Default",
		rd_tags,
		shader,
		camera);
	render_data->create_texture();
}

void STRLSceneBase::enable_physics()
{
	if (physics_ == nullptr)
	{
#ifdef STRL_RENDER_API_OPENGL
		OpenGLRenderData* render_data_debug_draw = render_data_manager_->create(
			"Physics Debug Draw", std::vector<std::string>{ "Physics" },
			shader_manager_->get_by_name("Engine Default")[0],
			camera_manager_->get_by_name("Engine Default")[0]);
		OpenGLRenderer::setup_render_data(*render_data_debug_draw);
#endif
		physics_ = std::make_unique<Box2DPhysics>(0.0f, 0.0f, *render_data_debug_draw);
	}
}

void STRLSceneBase::script_update()
{
	for (auto& script : *script_manager_)
	{
		if (!script->get_instance())
		{
			script->call_create_script();
		}
		script->get_instance()->on_update();
	}
}

void STRLSceneBase::physics_step()
{
	if (physics_)
	{
		physics_->step();
	}
}

void STRLSceneBase::render_clear()
{
	renderer_->clear();
}

void STRLSceneBase::prep_debug_render()
{
	if (physics_)
	{
		physics_->prep_debug_render();
	}
}

void STRLSceneBase::render_draw()
{
	for (auto& render_data : *render_data_manager_)
	{
		render_data->shader_update();
		renderer_->render(*render_data);
	}
}

double STRLSceneBase::get_time()
{
	return platform_->get_time();
}

void STRLSceneBase::quit_application()
{
	platform_->set_window_should_close(true);
}

int STRLSceneBase::get_window_width()
{
	return platform_->get_window_width();
}

int STRLSceneBase::get_window_height()
{
	return platform_->get_window_height();
}

void STRLSceneBase::set_background_color(float r, float g, float b, float a)
{
	renderer_->set_clear_color(r, g, b, a);
}

void STRLSceneBase::set_background_color(glm::vec4 color)
{
	renderer_->set_clear_color(color.r, color.g, color.b, color.a);
}

} // strl