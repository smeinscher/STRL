#include <iostream>
#include <strl/strl.h>
#include "scripts/PongBall.h"
#include "scripts/Opponent.h"
#include "scripts/Player.h"
#include "scripts/Misc.h"

void pong_setup(strl::STRLDriver& driver)
{
	strl::Camera* main_camera = (*driver.get_camera_manager().begin()).get();
	main_camera->set_zoom(23.5f);

	strl::ObjectManager& object_manager = driver.get_object_manager();
	strl::STRLObjectDefinition object_definition{strl::ShapeType2D::SQUARE};
	object_definition.position = {-10.0f, 0.0f, 0.0f};
	object_definition.size = {0.25f, 2.0f, 0.0f};
	strl::STRLObject* paddle1 = object_manager.create(object_definition);
	object_definition.position = {10.0f, 0.0f, 0.0f};
	strl::STRLObject* paddle2 = object_manager.create(object_definition);

	object_definition.points = strl::STRL_SHAPE2D_CIRCLE32_VERTICES;
	object_definition.position = {0.0f, 0.0f, 0.0f};
	object_definition.size = {0.125f, 0.125f, 0.0f};
	std::vector<std::string> tags = {"Tag"};
	strl::STRLObject* pong_ball = object_manager.create(object_definition);
	strl::ScriptHandler* pong_ball_move_script_handler = driver.get_script_manager().create(
		"Move Script Pong Ball", tags);
	pong_ball_move_script_handler->bind<PongBall>(pong_ball, &driver.get_physics());

	strl::ScriptHandler* script_handler12 = driver.get_script_manager().create("Player Controller 1", tags);
	strl::EventManager& event_manager = driver.get_event_manager();
	script_handler12->bind<Player>(paddle1, &event_manager, &driver.get_physics(),
		strl::STRL_KEY_W, strl::STRL_KEY_S,
		strl::STRL_KEY_IGNORE, strl::STRL_KEY_IGNORE);

	strl::ScriptHandler* script_handler2 = driver.get_script_manager().create("Opponent AI", tags);
	script_handler2->bind<Opponent>(paddle2, pong_ball, &driver.get_physics());
}

void simple_cube(strl::STRLDriver& driver)
{
	strl::ObjectManager& object_manager = driver.get_object_manager();
	strl::ShaderManager& shader_manager = driver.get_shader_manager();
	strl::CameraManager& camera_manager = driver.get_camera_manager();

	object_manager.add_texture("Wall Texture",
		std::vector<std::string>(),
		"resources/textures/wall.jpg",
		(*shader_manager.begin()).get(),
		(*camera_manager.begin()).get());

	strl::STRLObjectDefinition cube_definition{strl::STRL_SHAPE3D_CUBE_VERTICES, 6};
	cube_definition.size = {5.0f, 5.0f, 5.0f};
	cube_definition.rotation.euler = {glm::pi<float>() / 4, glm::pi<float>() / 4, glm::pi<float>() / 4};
	strl::STRLObject* cube = object_manager.create(cube_definition);
	strl::ScriptHandler* script_handler11 = driver.get_script_manager().create("Move Script 1");
	script_handler11->bind<strl::Movable>(cube);
	object_manager.assign_texture("Wall Texture", cube);
}

void simple_square(strl::STRLDriver& driver)
{
	strl::ObjectManager& object_manager = driver.get_object_manager();

	strl::STRLObjectDefinition square_definition{strl::ShapeType2D::SQUARE};
	square_definition.size = {5.0f, 5.0f, 0.0f};
	strl::STRLObject* square = object_manager.create(square_definition);
}

void background_color_changer(strl::STRLDriver& engine)
{
	strl::ScriptHandler* script_handler_bg_color = engine.get_script_manager().create("BG Color Changer",
		std::vector<std::string>());
	script_handler_bg_color->bind<Misc>(&engine);
}

int main()
{
	strl::STRLDriver driver{ 800, 600, "This is a test"};

	//pong_setup(engine);
	simple_cube(driver);
	driver.run();

	return 0;
}
