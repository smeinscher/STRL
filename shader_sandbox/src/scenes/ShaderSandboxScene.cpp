//
// Created by Sterling on 3/2/2024.
//

#include "ShaderSandboxScene.h"

bool ShaderSandboxScene::init()
{
	strl::Shader* shader = get_shader_manager().create("My Shader", std::vector<std::string>{});
	shader->load("resources/shaders/my_shader.vert",
		"resources/shaders/my_shader.frag", "");

	strl::Camera* camera = get_camera_manager().create("My Camera", std::vector<std::string>{},
		get_window_width(), get_window_height());
	camera->set_is_ortho(true);

	strl::RenderData* render_data = get_render_data_manager().create("My Render Data",
		std::vector<std::string>{}, shader, camera);
	render_data->create_texture();

	std::vector<glm::vec3> points = {
		{0.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f}
	};
	strl::ObjectDefinition rect_definition{points, 1};
	rect_definition.color = {0.5f, 0.3f, 0.8f, 1.0f};
	rect_definition.size = {get_window_width(), get_window_height(), 0.0f};
	strl::Object* rect = get_object_manager().create(rect_definition);
	get_object_manager().assign_render_data("My Render Data", rect);
	return true;
}
