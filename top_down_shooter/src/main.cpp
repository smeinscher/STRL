#include <iostream>
#include <strl/strl.h>
#include "scenes/GameScene.h"

/*void simple_cube(strl::STRLDriver& driver)
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
}*/

/*void simple_square(strl::STRLDriver& driver)
{
	strl::ObjectManager& object_manager = driver.get_object_manager();

	strl::STRLObjectDefinition square_definition{strl::ShapeType2D::SQUARE};
	square_definition.size = {5.0f, 5.0f, 0.0f};
	strl::STRLObject* square = object_manager.create(square_definition);
}*/

int main()
{
	strl::STRLDriver driver{800, 600, "Top Down Shooter"};

	std::vector<std::string> tags = {"Main Game Scene"};
	int scene_id = driver.create_scene<Pong>("TDS Main Game Scene", tags);
	driver.set_active_scene(scene_id);
	driver.run();

	return 0;
}
