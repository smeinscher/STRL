//
// Created by Sterling on 3/1/2024.
//

#include "Pong.h"
#include "../scripts/PongBall.h"
#include "../scripts/Player.h"
#include "../scripts/Opponent.h"

bool Pong::init()
{
	set_background_color(0.5f, 0.3f, 0.6f, 1.0f);

	strl::Shader* shader = get_shader_manager().create("Pong Shader", std::vector<std::string>{});
	shader->load("resources/shaders/pong_shader.vert",
		"resources/shaders/pong_shader.frag");

	strl::Camera* camera = get_camera_manager().create("Pong Camera", std::vector<std::string>{},
		get_window_width(), get_window_height());
	camera->set_is_ortho(true);

	strl::Camera& camera_ref = *camera;
	strl::Shader& shader_ref = *shader;
	std::function<void()> shader_update_function = [&]()
	{
		camera_ref.update_camera_vectors();
		strl::ShaderUtils::set_mat4(shader_ref.get_shader_program_id(), "view", camera_ref.get_view());
		strl::ShaderUtils::set_mat4(shader_ref.get_shader_program_id(), "projection", camera_ref.get_projection());
		strl::ShaderUtils::set_float(shader_ref.get_shader_program_id(), "u_time", get_time());
	};

	strl::RenderData* render_data = get_render_data_manager().create("Pong Render Data",
		std::vector<std::string>{}, shader, camera, shader_update_function);
	render_data->create_texture();

	create_default_shader();
	enable_physics(false, camera);

	strl::ObjectManager& object_manager = get_object_manager();
	// Create paddles
	strl::STRLObjectDefinition object_definition{strl::ShapeType2D::SQUARE};
	object_definition.position = {20.0f,
								  static_cast<float>(get_window_height()) / 2.0f,
								  0.0f};
	object_definition.size = {10.0f, 80.0f, 0.0f};
	strl::STRLObject* paddle1 = object_manager.create(object_definition);
	get_object_manager().assign_render_data("Pong Render Data", paddle1);
	object_definition.position = {static_cast<float>(get_window_width()) - 20.0f,
								  static_cast<float>(get_window_height()) / 2.0f,
								  0.0f};
	strl::STRLObject* paddle2 = object_manager.create(object_definition);
	get_object_manager().assign_render_data("Pong Render Data", paddle2);

	// Create ball
	object_definition.points = strl::STRL_SHAPE2D_CIRCLE32_VERTICES;
	object_definition.position = {static_cast<float>(get_window_width()) / 2.0f,
	                              static_cast<float>(get_window_height()) / 2.0f,
								  0.0f};
	object_definition.size = {5.0f, 5.0f, 0.0f};
	std::vector<std::string> tags = {"Tag"};
	strl::STRLObject* pong_ball = object_manager.create(object_definition);
	get_object_manager().assign_render_data("Pong Render Data", pong_ball);
	strl::ScriptHandler* pong_ball_move_script_handler = get_script_manager().create(
		"Move Script Pong Ball", tags);
	pong_ball_move_script_handler->bind<PongBall>(pong_ball, &get_physics());

	// Player controller script
	strl::ScriptHandler* script_handler12 = get_script_manager().create("Player Controller 1", tags);
	script_handler12->bind<Player>(paddle1, &get_event_manager(), &get_physics(),
		strl::STRL_KEY_W, strl::STRL_KEY_S,
		strl::STRL_KEY_IGNORE, strl::STRL_KEY_IGNORE);
	// AI script
	strl::ScriptHandler* script_handler2 = get_script_manager().create("Opponent AI", tags);
	strl::Box2DPhysicsDefinitions physics_definitions;
	physics_definitions.body_definition.type = b2_staticBody;
	physics_definitions.body_definition.position = {paddle2->get_position().x * strl::PHYSICS_SCALE,
													paddle2->get_position().y * strl::PHYSICS_SCALE};
	script_handler2->bind<Opponent>(paddle2, pong_ball, &get_physics(), physics_definitions);

	return true;
}

void Pong::update()
{
	STRLSceneBase::update();
}

void Pong::render()
{
	STRLSceneBase::render();
}
