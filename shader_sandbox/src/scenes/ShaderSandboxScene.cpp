//
// Created by Sterling on 3/2/2024.
//

#include "ShaderSandboxScene.h"

bool ShaderSandboxScene::init()
{
	strl::Shader* shader = get_shader_manager().create("My Shader", std::vector<std::string>{});
	shader->load("resources/shaders/my_shader.vert",
	             "resources/shaders/my_shader.frag");

	strl::Camera* camera = get_camera_manager().create("My Camera", std::vector<std::string>{},
	                                                   get_window_width(), get_window_height());
	camera->set_is_ortho(true);

	strl::Camera& camera_ref = *camera;
	strl::Shader& shader_ref = *shader;
	std::function<void()> shader_update_function = [&]() {
		camera_ref.update_camera_vectors();
		strl::ShaderUtils::set_mat4(shader_ref.get_shader_program_id(), "view", camera_ref.get_view());
		strl::ShaderUtils::set_mat4(shader_ref.get_shader_program_id(), "projection", camera_ref.get_projection());
		strl::ShaderUtils::set_float(shader_ref.get_shader_program_id(), "u_time", get_time());
	};

	strl::RenderData* render_data = get_render_data_manager().create("My Render Data",
	                                                                 std::vector<std::string>{}, shader, camera, shader_update_function);
	render_data->create_texture();

	std::vector<glm::vec3> points = {
	    {0.0f, 0.0f, 0.0f},
	    {1.0f, 0.0f, 0.0f},
	    {1.0f, 1.0f, 0.0f},
	    {0.0f, 1.0f, 0.0f}};
	strl::ObjectDefinition rect_definition{points};
	rect_definition.color = {0.5f, 0.3f, 0.8f, 1.0f};
	rect_definition.size = {get_window_width(), get_window_height(), 0.0f};
	strl::Object* rect = get_object_manager().create(rect_definition);
	get_object_manager().assign_render_data("My Render Data", rect);
	return true;
}
