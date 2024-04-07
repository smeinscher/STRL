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

	strl::RenderData* planet_render_data = get_render_data_manager().create("Planet",
		std::vector<std::string>(),
		(*get_shader_manager().begin()).get(),
		(*get_camera_manager().begin()).get());
	planet_render_data->create_texture("resources/textures/moon1024.bmp");

	strl::ObjectDefinition planet_definition{strl::generate_sphere(18, 36),
	                                          strl::generate_uv_for_sphere(18, 36),
											  strl::STRLObjectType::SPHERE1836};
	planet_definition.size = { 0.5f, 0.5f, 0.5f};
	planet_ = get_object_manager().create(planet_definition);
	get_object_manager().assign_render_data("Planet", planet_);

	strl::Shader* tank_shader = get_shader_manager().create("Tank Shader", std::vector<std::string>());
	tank_shader->load("resources/shaders/unit.vert", "resources/shaders/unit.frag");

	strl::RenderData* unit_render_data = get_render_data_manager().create("Tank",
		std::vector<std::string>(),
		tank_shader,
		(*get_camera_manager().begin()).get());
	unit_render_data->create_texture("resources/textures/tank.png");

	strl::ObjectDefinition tank_definition{};
	tank_definition.position = glm::vec3{0.0f, 0.0f, planet_->get_size().z} * 1.025f;
	tank_definition.size = { 0.025f, 0.025f, 0.0f};
	tank_definition.color = {0.2f, 0.7f, 0.2f, 1.0f};
	tank_definition.rotation.quaternion = glm::rotate(tank_definition.rotation.quaternion, glm::pi<float>() / 2.0f, {0.0f, 0.0f, 1.0f});
	tank_ = get_object_manager().create(tank_definition);
	get_object_manager().assign_render_data("Tank", tank_);

	strl::Shader* selection_shader = get_shader_manager().create("Selection Shader", std::vector<std::string>());
	selection_shader->load("resources/shaders/selection.vert", "resources/shaders/selection.frag");

	strl::RenderData* selection_rect_render_data = get_render_data_manager().create("Selection Rect",
		std::vector<std::string>(),
		selection_shader,
		(*get_camera_manager().begin()).get());
	selection_rect_render_data->create_texture("");
	selection_rect_render_data->set_mode(strl::STRLRenderMode::STRL_LINE_LOOP);

	strl::EventListenerFunction mouse_scroll = [this](strl::Event* event)
	{
		auto data = reinterpret_cast<strl::STRLMouseScrollEventData*>(event->get_event_data());
		(*get_camera_manager().begin())->increment_zoom(static_cast<float>(-data->y_offset * 2.0));
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_WHEEL, 0,
		mouse_scroll, "Camera Zoom");

	strl::EventListenerFunction left_mouse_button_pressed = [this](strl::Event* event)
	{
		move_planet_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_PRESSED,
		strl::STRL_MOUSE_BUTTON_LEFT, left_mouse_button_pressed, "Left Mouse Button Pressed");
	strl::EventListenerFunction left_mouse_button_released = [this](strl::Event* event)
	{
		move_planet_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_RELEASED,
		strl::STRL_MOUSE_BUTTON_LEFT, left_mouse_button_released, "Left Mouse Button Released");

	strl::EventListenerFunction right_mouse_button_pressed = [this](strl::Event* event)
	{
		move_unit_ = true;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_PRESSED,
		strl::STRL_MOUSE_BUTTON_RIGHT, right_mouse_button_pressed, "Right Mouse Button Pressed");
	strl::EventListenerFunction right_mouse_button_released = [this](strl::Event* event)
	{
		move_unit_ = false;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_MOUSE_BUTTON_RELEASED,
		strl::STRL_MOUSE_BUTTON_RIGHT, right_mouse_button_released, "Right Mouse Button Released");

	strl::EventListenerFunction left_ctrl_mouse_button_pressed = [this](strl::Event* event)
	{
		making_selection_ = true;
		strl::ObjectDefinition selection_rect_definition{};
		selection_rect_definition.size = {1.0f, 1.0f, 0.0f};
		selection_rect_definition.position = {0.0f, 0.0f, 0.5f};
		selection_rect_definition.points[0] = mouse_click_ray_cast_nds();
		selection_rect_definition.points[0].z = 1.0f;
		selection_rect_definition.points[1] = selection_rect_definition.points[0];
		selection_rect_definition.points[2] = selection_rect_definition.points[0];
		selection_rect_definition.points[3] = selection_rect_definition.points[0];

		selection_rect_ = get_object_manager().create(selection_rect_definition);
		get_object_manager().assign_render_data("Selection Rect", selection_rect_);
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_LEFT_CONTROL, left_ctrl_mouse_button_pressed, "Left Ctrl Key Pressed");
	strl::EventListenerFunction left_ctrl_mouse_button_released = [this](strl::Event* event)
	{
		making_selection_ = false;
		get_object_manager().remove(selection_rect_);
		selection_rect_ = nullptr;
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_RELEASED,
		strl::STRL_KEY_LEFT_CONTROL, left_ctrl_mouse_button_released, "Left Ctrl Key Released");


	strl::EventListenerFunction mouse_movement = [this](strl::Event* event)
	{
		auto data = reinterpret_cast<strl::STRLMouseMoveEventData*>(event->get_event_data());
		if (making_selection_ && !move_planet_)
		{
			if (selection_rect_)
			{
				std::vector<glm::vec3> points = selection_rect_->get_points();
				points[2] = mouse_click_ray_cast_nds();
				points[2].z = 1.0f;
				points[1].x = points[2].x;
				points[1].z = points[2].z;
				points[3].y = points[2].y;
				points[3].z = points[2].z;
				selection_rect_->set_points(points);
			}
		}
		if (move_planet_ && !making_selection_)
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
		tank_->set_position(glm::vec3{ 0.0f, 0.0f, 0.5f} * 1.025f);
		tank_->set_rotation({ 1.0f, 0.0f, 0.0f, 0.0f});
		goal_position_ = tank_->get_position();
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_R, r_pressed, "R Pressed");

	strl::EventListenerFunction z_pressed = [this](strl::Event* event)
	{
		(*get_camera_manager().begin())->rotate_around_point(planet_->get_position(), {0.0f, glm::pi<float>(), 0.0f});
	};
	get_event_manager().register_event_listener(strl::STRLEventType::STRL_EVENT_KEY_PRESSED,
		strl::STRL_KEY_Z, z_pressed, "Z Pressed");

	goal_position_ = tank_->get_position();
	start_position_ = goal_position_;

	return true;
}

void SphereSandboxScene::update()
{
	STRLSceneBase::update();

	if (making_selection_)
	{

	}
	if (move_unit_)
	{
		glm::vec3 ray_world = mouse_click_ray_cast();

		glm::vec3 origin_minus_center = (*get_camera_manager().begin())->get_position() - planet_->get_position();
		float b = glm::dot(ray_world, origin_minus_center);
		float c = glm::dot(origin_minus_center, origin_minus_center) - std::pow(planet_->get_size().x, 2.0f);

		if (std::pow(b, 2.0f) - c >= 0)
		{
			goal_position_ =
				(*get_camera_manager().begin())->get_position() + ray_world * (-b - std::sqrt(std::pow(b, 2.0f) - c));
			start_position_ = tank_->get_position();
			distance_to_goal_ = 0.0f;
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
		tank_->set_position(glm::normalize(position) * planet_->get_size() * 1.025f);
	}
	else
	{
		distance_to_goal_ = 1.0f;
	}

	glm::quat rotation = glm::toQuat(glm::inverse((*get_camera_manager().begin())->get_view()));
	tank_->set_rotation(rotation);
}

void SphereSandboxScene::render()
{
	STRLSceneBase::render();
	ImGui::Text("Tank Position: %2.2f, %2.2f, %2.2f", tank_->get_position().x,
		tank_->get_position().y, tank_->get_position().z);
	ImGui::Text("Goal Position: %2.2f, %2.2f, %2.2f", goal_position_.x, goal_position_.y, goal_position_.z);
	auto camera = (*get_camera_manager().begin()).get();
	ImGui::Text("Camera Position: %2.2f, %2.2f, %2.2f", camera->get_position().x, camera->get_position().y, camera->get_position().z);
	if (selection_rect_)
	{
		ImGui::Text("Selection Position: %2.2f, %2.2f, %2.2f", selection_rect_->get_position().x, selection_rect_->get_position().y, selection_rect_->get_position().z);
		ImGui::Text("Selection Point 0: %2.2f, %2.2f, %2.2f", selection_rect_->get_points()[0].x, selection_rect_->get_points()[0].y, selection_rect_->get_points()[0].z);
		ImGui::Text("Selection Point 1: %2.2f, %2.2f, %2.2f", selection_rect_->get_points()[1].x, selection_rect_->get_points()[1].y, selection_rect_->get_points()[1].z);
		ImGui::Text("Selection Point 2: %2.2f, %2.2f, %2.2f", selection_rect_->get_points()[2].x, selection_rect_->get_points()[2].y, selection_rect_->get_points()[2].z);
		ImGui::Text("Selection Point 3: %2.2f, %2.2f, %2.2f", selection_rect_->get_points()[3].x, selection_rect_->get_points()[3].y, selection_rect_->get_points()[3].z);
	}
	glm::vec3 ray_world = mouse_click_ray_cast();
	ImGui::Text("Ray World: %2.2f, %2.2f, %2.2f", ray_world.x, ray_world.y, ray_world.z);
	glm::vec3 ray_nds = mouse_click_ray_cast_nds();
	ImGui::Text("Ray NDS: %2.2f, %2.2f, %2.2f", ray_nds.x, ray_nds.y, ray_nds.z);
}

glm::vec3 SphereSandboxScene::mouse_click_ray_cast_nds()
{
	float x = (2.0f * mouse_position_x_) / get_window_width() - 1.0f;
	float y = 1.0f - (2.0f * mouse_position_y_) / get_window_height();
	float z = 1.0f;
	return {x, y, z};
}

glm::vec3 SphereSandboxScene::mouse_click_ray_cast()
{
	glm::vec3 ray_nds = mouse_click_ray_cast_nds();

	glm::vec4 ray_clip = {ray_nds.x, ray_nds.y, -1.0f, 1.0f};
	glm::vec4 ray_eye = glm::inverse((*get_camera_manager().begin())->get_projection()) * ray_clip;
	ray_eye = {ray_eye.x, ray_eye.y, -1.0f, 0.0f};

	glm::vec3 ray_world = glm::inverse((*get_camera_manager().begin())->get_view()) * ray_eye;
	ray_world = glm::normalize(ray_world);

	return ray_world;
}
