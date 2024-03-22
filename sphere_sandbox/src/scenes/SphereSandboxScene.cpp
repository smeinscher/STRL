//
// Created by Sterling on 3/9/2024.
//

#include <imgui.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/norm.hpp>
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
	planet_definition.size = { 0.5f, 0.5f, 0.5f};
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
	person_definition.position = {0.0f, 0.0f, planet_->get_size().z};
	person_definition.size = {0.05f, 0.05f, 0.0f};
	person_ = get_object_manager().create(person_definition);
	get_object_manager().assign_render_data("Person", person_);

	strl::EventListenerFunction w_pressed = [this](strl::Event* event)
	{
		is_moving_up_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_W, w_pressed, "W Pressed");
	strl::EventListenerFunction w_released = [this](strl::Event* event)
	{
		is_moving_up_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED,
		strl::STRL_KEY_W, w_released, "W Released");

	strl::EventListenerFunction s_pressed = [this](strl::Event* event)
	{
		is_moving_down_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_S, s_pressed, "S Pressed");
	strl::EventListenerFunction s_released = [this](strl::Event* event)
	{
		is_moving_down_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED,
		strl::STRL_KEY_S, s_released, "S Released");

	strl::EventListenerFunction a_pressed = [this](strl::Event* event)
	{
		is_moving_left_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_A, a_pressed, "A Pressed");
	strl::EventListenerFunction a_released = [this](strl::Event* event)
	{
		is_moving_left_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED,
		strl::STRL_KEY_A, a_released, "A Released");

	strl::EventListenerFunction d_pressed = [this](strl::Event* event)
	{
		is_moving_right_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_D, d_pressed, "D Pressed");
	strl::EventListenerFunction d_released = [this](strl::Event* event)
	{
		is_moving_right_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED,
		strl::STRL_KEY_D, d_released, "D Released");

	strl::EventListenerFunction q_pressed = [this](strl::Event* event)
	{
		is_rotating_counter_clockwise_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_Q, q_pressed, "Q Pressed");
	strl::EventListenerFunction q_released = [this](strl::Event* event)
	{
		is_rotating_counter_clockwise_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED,
		strl::STRL_KEY_Q, q_released, "Q Released");

	strl::EventListenerFunction e_pressed = [this](strl::Event* event)
	{
		is_rotating_clockwise_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_E, e_pressed, "E Pressed");
	strl::EventListenerFunction e_released = [this](strl::Event* event)
	{
		is_rotating_clockwise_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED,
		strl::STRL_KEY_E, e_released, "E Released");

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

	strl::EventListenerFunction right_mouse_button_pressed = [this](strl::Event* event)
	{
		is_right_mouse_button_down_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_PRESSED,
		strl::STRL_MOUSE_BUTTON_RIGHT, right_mouse_button_pressed, "Right Mouse Button Pressed");
	strl::EventListenerFunction right_mouse_button_released = [this](strl::Event* event)
	{
		is_right_mouse_button_down_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_RELEASED,
		strl::STRL_MOUSE_BUTTON_RIGHT, right_mouse_button_released, "Right Mouse Button Released");

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
		(*get_camera_manager().begin())->set_position({0.0f, 0.0f, 1.0f});
		(*get_camera_manager().begin())->set_euler_angles({0.0f, 3 * glm::pi<float>() / 2, 0.0f});
		(*get_camera_manager().begin())->set_zoom(45.0f);
		person_->set_position({0.0f, 0.0f, 0.5f});
		person_->set_rotation({1.0f, 0.0f, 0.0f, 0.0f});
		goal_position_ = person_->get_position();
		front_ = {1.0f, 0.0f, 0.0f};
		up_ = {0.0f, 0.0f, 1.0f};
		right_ = {0.0f, -1.0f, 0.0f};
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_R, r_pressed, "R Pressed");

	strl::EventListenerFunction z_pressed = [this](strl::Event* event)
	{
		(*get_camera_manager().begin())->rotate_around_point(planet_->get_position(), {0.0f, glm::pi<float>(), 0.0f});
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_Z, z_pressed, "Z Pressed");

	goal_position_ = person_->get_position();
	start_position_ = goal_position_;

	return true;
}

void SphereSandboxScene::update()
{
	STRLSceneBase::update();

	if (is_right_mouse_button_down_)
	{
		float x = (2.0f * mouse_position_x_) / get_window_width() - 1.0f;
		float y = 1.0f - (2.0f * mouse_position_y_) / get_window_height();
		float z = 1.0f;
		glm::vec3 ray_nds = {x, y, z};

		glm::vec4 ray_clip = {ray_nds.x, ray_nds.y, -1.0f, 1.0f};
		glm::vec4 ray_eye = glm::inverse((*get_camera_manager().begin())->get_projection()) * ray_clip;
		ray_eye = {ray_eye.x, ray_eye.y, -1.0f, 0.0f};

		glm::vec3 ray_world = glm::inverse((*get_camera_manager().begin())->get_view()) * ray_eye;
		ray_world = glm::normalize(ray_world);

		glm::vec3 origin_minus_center = (*get_camera_manager().begin())->get_position() - planet_->get_position();
		float b = glm::dot(ray_world, origin_minus_center);
		float c = glm::dot(origin_minus_center, origin_minus_center) - std::pow(planet_->get_size().x, 2.0f);

		if (std::pow(b, 2.0f) - c >= 0)
		{
			goal_position_ =
				(*get_camera_manager().begin())->get_position() + ray_world * (-b - std::sqrt(std::pow(b, 2.0f) - c));
			start_position_ = person_->get_position();
			distance_to_goal_ = 0.0f;
			/*person_->set_rotation(glm::quatLookAt(glm::normalize(ray_world - person_->get_position()),
				person_->get_position().z >= 0.0f ? glm::vec3{0.0f, 0.0f, 1.0f} : glm::vec3{0.0f, 0.0f, -1.0f}));
			person_->set_rotation(glm::rotate(person_->get_rotation().quaternion, glm::pi<float>() / 2.0f, {0.0f, 0.0f, 1.0f}));
			person_->set_rotation(glm::pow(person_->get_rotation().quaternion, 0.5f));*/
		}
	}

	if (distance_to_goal_ < 1.0f)
	{
		float rotation_speed = 0.01f;
		distance_to_goal_ += rotation_speed / glm::length(goal_position_ - start_position_);
		glm::vec3 current = glm::normalize(start_position_ - planet_->get_position());
		glm::vec3 desired = glm::normalize(goal_position_ - planet_->get_position());
		auto current_quat = glm::quat(0.0f, current);
		float rotation_angle = acos(glm::dot(current, desired));
		glm::vec3 rotation_axis = glm::normalize(glm::cross(current, desired));

		glm::quat rotation = glm::angleAxis(rotation_angle * distance_to_goal_, rotation_axis);

		glm::vec3 position = glm::rotate(rotation, current) * glm::length(
			goal_position_ - planet_->get_position()) + planet_->get_position();
		person_->set_position(glm::normalize(position) * planet_->get_size() * 1.01f);

		glm::quat rotation1 = glm::normalize(glm::pow(glm::cross(glm::quat(0.0f, person_->get_position() - planet_->get_position()), glm::quat(0.0f, rotation_axis)), 0.5f));
		glm::quat rotation2 = glm::rotate(rotation, current) * person_->get_rotation().quaternion;
		glm::quat rotation3 = glm::rotate(person_->get_rotation().quaternion, glm::pi<float>() / 2.0f, glm::normalize(current));

		glm::quat final_rotation = rotation1;

		//person_->set_rotation(final_rotation);
	}
	else
	{
		distance_to_goal_ = 1.0f;
	}
}

void SphereSandboxScene::render()
{
	STRLSceneBase::render();
	ImGui::Text("Person Position: %2.2f, %2.2f, %2.2f", person_->get_position().x,
		person_->get_position().y, person_->get_position().z);
	ImGui::Text("Person Quaternion: %2.2f, %2.2f, %2.2f, %2.2f", person_->get_rotation().quaternion.w, person_->get_rotation().quaternion.x,
		person_->get_rotation().quaternion.y, person_->get_rotation().quaternion.z);
	ImGui::Text("Person Euler: %2.2f, %2.2f, %2.2f", person_->get_rotation().euler.x,
		person_->get_rotation().euler.y, person_->get_rotation().euler.z);
	ImGui::Text("Goal Position: %2.2f, %2.2f, %2.2f", goal_position_.x, goal_position_.y, goal_position_.z);
}
