//
// Created by Sterling on 3/9/2024.
//

#include <imgui.h>
#include "SphereSandboxScene.h"

bool SphereSandboxScene::init()
{
	if (!STRLSceneBase::init())
	{
		return false;
	}

	get_object_manager().add_render_data("Earth",
		std::vector<std::string>(),
		"resources/textures/moon1024.bmp",
		(*get_shader_manager().begin()).get(),
		(*get_camera_manager().begin()).get());

	strl::ObjectDefinition planet_definition{strl::generate_sphere(18, 36),
	                                          strl::generate_uv_for_sphere(18, 36),
											  strl::STRLObjectType::SPHERE1836};
	planet_definition.size = { 1.0f, 1.0f, 1.0f};
	planet_ = get_object_manager().create(planet_definition);
	get_object_manager().assign_render_data("Earth", planet_);

	strl::Shader* person_shader = get_shader_manager().create("Person Shader", std::vector<std::string>());
	person_shader->load("resources/shaders/person.vert", "resources/shaders/person.frag");
	get_object_manager().add_render_data("Person",
		std::vector<std::string>(),
		"resources/textures/character.png",
		person_shader,
		(*get_camera_manager().begin()).get());

	strl::ObjectDefinition person_definition{};
	person_definition.position = {0.0f, 0.0f, 1.0f};
	person_definition.size = {0.05f, 0.05f, 0.0f};
	person_ = get_object_manager().create(person_definition);
	get_object_manager().assign_render_data("Person", person_);

	strl::EventListenerFunction a_pressed = [this](strl::Event* event)
	{
		glm::vec3 focus_vector = person_->get_position() - planet_->get_position();
		float rotation_speed = 0.04f;

		auto up_yaw_matrix = glm::mat4(1.0f);
		up_yaw_matrix = glm::rotate(up_yaw_matrix, -rotation_speed, {0.0f, 1.0f, 0.0f});

		/*auto right_pitch_matrix = glm::mat4(1.0f);
		right_pitch_matrix = glm::rotate(right_pitch_matrix, -rotation_speed, right_);*/

		focus_vector = up_yaw_matrix * /*right_pitch_matrix **/ glm::vec4(focus_vector, 1.0f);
		person_->set_position(planet_->get_position() + focus_vector);

		person_->rotate({0.0f, -rotation_speed, 0.0f});
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_A, a_pressed, "A Pressed");

	strl::EventListenerFunction d_pressed = [this](strl::Event* event)
	{
		glm::vec3 focus_vector = person_->get_position() - planet_->get_position();
		float rotation_speed = 0.04f;

		auto up_yaw_matrix = glm::mat4(1.0f);
		up_yaw_matrix = glm::rotate(up_yaw_matrix, rotation_speed, {0.0f, 1.0f, 0.0f});

		/*auto right_pitch_matrix = glm::mat4(1.0f);
		right_pitch_matrix = glm::rotate(right_pitch_matrix, -rotation_speed, right_);*/

		focus_vector = up_yaw_matrix * /*right_pitch_matrix **/ glm::vec4(focus_vector, 1.0f);
		person_->set_position(planet_->get_position() + focus_vector);

		person_->rotate({0.0f, rotation_speed, 0.0f});
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_D, d_pressed, "D Pressed");

	strl::EventListenerFunction mouse_scroll = [this](strl::Event* event)
	{
		auto data = reinterpret_cast<strl::STRLMouseScrollEventData*>(event->get_event_data());
		(*get_camera_manager().begin())->increment_zoom(static_cast<float>(-data->y_offset * 2.0));
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_WHEEL, 0,
		mouse_scroll, "Camera Zoom");

	strl::EventListenerFunction left_mouse_button_pressed = [this](strl::Event* event)
	{
		is_left_mouse_button_down_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_PRESSED,
		strl::STRL_MOUSE_BUTTON_LEFT, left_mouse_button_pressed, "Left Mouse Button Pressed");
	strl::EventListenerFunction left_mouse_button_released = [this](strl::Event* event)
	{
		is_left_mouse_button_down_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_RELEASED,
		strl::STRL_MOUSE_BUTTON_LEFT, left_mouse_button_released, "Left Mouse Button Released");


	strl::EventListenerFunction mouse_movement = [this](strl::Event* event)
	{
		auto data = reinterpret_cast<strl::STRLMouseMoveEventData*>(event->get_event_data());
		if (is_left_mouse_button_down_)
		{
			float rotation_speed = 0.004f;
			strl::Camera* my_camera = (*get_camera_manager().begin()).get();
			float y_angle_change = static_cast<float>(data->x_pos - mouse_position_x_) * rotation_speed;
			float z_angle_change = static_cast<float>(data->y_pos - mouse_position_y_) * rotation_speed;
			glm::vec3 angle = glm::vec3(0.0f, y_angle_change, z_angle_change);
			if (my_camera->get_euler_angles().y + angle.y >= 2.0f * glm::pi<float>())
			{
				angle.y = -2.0f * glm::pi<float>();
			}
			else if (my_camera->get_euler_angles().y + angle.y <= 0.0f)
			{
				angle.y = 2.0f * glm::pi<float>();
			}
			if (my_camera->get_euler_angles().z + z_angle_change >= glm::pi<float>() / 2.0f ||
			    my_camera->get_euler_angles().z + z_angle_change <= -glm::pi<float>() / 2.0f)
			{
				angle.z = 0.0f;
			}
			my_camera->rotate_around_point(planet_->get_position(), angle);
		}
		mouse_position_x_ = data->x_pos;
		mouse_position_y_ = data->y_pos;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_MOVED, 0,
		mouse_movement, "Mouse Moved");

	strl::EventListenerFunction r_pressed = [this](strl::Event* event)
	{
		(*get_camera_manager().begin())->set_position({0.0f, 0.0f, 2.0f});
		(*get_camera_manager().begin())->set_euler_angles({0.0f, 3 * glm::pi<float>() / 2, 0.0f});
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_R, r_pressed, "R Pressed");

	return true;
}

void SphereSandboxScene::render()
{
	STRLSceneBase::render();
	ImGui::Text("%2.2f, %2.2f, %2.2f", (*get_camera_manager().begin())->get_euler_angles().x,
		(*get_camera_manager().begin())->get_euler_angles().y, (*get_camera_manager().begin())->get_euler_angles().z);
	ImGui::Text("%2.2f, %2.2f, %2.2f", (*get_camera_manager().begin())->get_position().x,
		(*get_camera_manager().begin())->get_position().y,
		(*get_camera_manager().begin())->get_position().z);
	ImGui::Text("%2.2f", glm::length((*get_camera_manager().begin())->get_position()));
}
