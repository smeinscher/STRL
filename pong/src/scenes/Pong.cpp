//
// Created by Sterling on 3/1/2024.
//

#include "Pong.h"
#include "../scripts/PongBall.h"
#include "../scripts/Player.h"
#include "../scripts/Opponent.h"

bool Pong::init()
{
	if (!STRLSceneBase::init())
	{
		return false;
	}

	strl::Camera* main_camera = (*get_camera_manager().begin()).get();
	main_camera->set_zoom(23.5f);

	set_background_color(0.7f, 0.3f, 0.8f, 1.0f);

	strl::ObjectManager& object_manager = get_object_manager();
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
	strl::ScriptHandler* pong_ball_move_script_handler = get_script_manager().create(
		"Move Script Pong Ball", tags);
	pong_ball_move_script_handler->bind<PongBall>(pong_ball, &get_physics());

	strl::ScriptHandler* script_handler12 = get_script_manager().create("Player Controller 1", tags);
	script_handler12->bind<Player>(paddle1, &get_event_manager(), &get_physics(),
		strl::STRL_KEY_W, strl::STRL_KEY_S,
		strl::STRL_KEY_IGNORE, strl::STRL_KEY_IGNORE);

	strl::ScriptHandler* script_handler2 = get_script_manager().create("Opponent AI", tags);
	script_handler2->bind<Opponent>(paddle2, pong_ball, &get_physics());
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
