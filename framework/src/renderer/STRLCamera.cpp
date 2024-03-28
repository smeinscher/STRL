//
// Created by SterlingMeinscher on 2/21/2024.
//

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <string>
#include <vector>
#include "STRLCamera.h"

namespace strl
{

STRLCamera::STRLCamera(std::__cxx11::basic_string<char> name,
	std::vector<std::string> tags,
	float camera_view_width,
	float camera_view_height)
	: STRLManagedItemBase(std::move(name), std::move(tags)),
	  camera_view_width_(camera_view_width), camera_view_height_(camera_view_height)
{

}

glm::mat4 STRLCamera::get_projection() const
{
	return !is_ortho_
		? glm::perspective(glm::radians(zoom_),
			camera_view_width_ / camera_view_height_,
			0.1f, 100.0f)
		: glm::ortho(0.0f, camera_view_width_, camera_view_height_, 0.0f, 0.1f, 100.0f);
}

glm::mat4 STRLCamera::get_view() const
{
	return glm::lookAt(position_, position_ + front_, up_);;
}

glm::vec3& STRLCamera::get_position()
{
	return position_;
}

void STRLCamera::set_position(glm::vec3 position)
{
	position_ = position;
}

void STRLCamera::move_position(glm::vec3 amount)
{
	position_ += amount;
}

glm::vec3& STRLCamera::get_front()
{
	return front_;
}

glm::vec3& STRLCamera::get_up()
{
	return up_;
}

glm::vec3& STRLCamera::get_euler_angles()
{
	return euler_angles_;
}

void STRLCamera::set_euler_angles(glm::vec3 angles)
{
	euler_angles_ = angles;
}

void STRLCamera::rotate(glm::vec3 amount)
{
	euler_angles_ += amount;
}

float STRLCamera::get_camera_view_width() const
{
	return camera_view_width_;
}

float STRLCamera::get_camera_view_height() const
{
	return camera_view_height_;
}

void STRLCamera::set_camera_view_width_and_height(float camera_view_width, float camera_view_height)
{
	camera_view_width_ = camera_view_width;
	camera_view_height_ = camera_view_height;
}

void STRLCamera::set_view_width_maintain_ratio(float width)
{
	float ratio = camera_view_width_ / camera_view_height_;
	camera_view_width_ = width;
	camera_view_height_ = width / ratio;
}

void STRLCamera::set_view_height_maintain_ratio(float height)
{
	float ratio = camera_view_width_ / camera_view_height_;
	camera_view_width_ = height * ratio;
	camera_view_height_ = height;
}

float STRLCamera::get_zoom() const
{
	return zoom_;
}

void STRLCamera::set_zoom(float zoom)
{
	zoom_ = zoom;
}

void STRLCamera::increment_zoom(float amount)
{
	zoom_ += amount;
	if (zoom_ > max_zoom_)
	{
		zoom_ = max_zoom_;
	}
	else if (zoom_ < min_zoom_)
	{
		zoom_ = min_zoom_;
	}
}

void STRLCamera::set_is_ortho(bool is_ortho)
{
	is_ortho_ = is_ortho;
}

void STRLCamera::update_camera_vectors()
{
	front_.x = std::cos(euler_angles_.y) * std::cos(euler_angles_.z);
	front_.y = -std::sin(euler_angles_.z);
	front_.z = std::sin(euler_angles_.y) * std::cos(euler_angles_.z);
	front_ = glm::normalize(front_);
	right_ = glm::normalize(glm::cross(front_, {0.0f, 1.0f, 0.0f}));
	up_ = glm::normalize(glm::cross(right_, front_));
}

void STRLCamera::rotate_around_point(glm::vec3 point, glm::vec3 euler_angles)
{
	glm::vec3 cam_focus_vector = position_ - point;

	auto up_yaw_matrix = glm::mat4(1.0f);
	up_yaw_matrix = glm::rotate(up_yaw_matrix, -euler_angles.y, {0.0f, 1.0f, 0.0f});

	auto right_pitch_matrix = glm::mat4(1.0f);
	right_pitch_matrix = glm::rotate(right_pitch_matrix, -euler_angles.z, right_);

	cam_focus_vector = up_yaw_matrix * right_pitch_matrix * glm::vec4(cam_focus_vector, 1.0f);
	position_ = point + cam_focus_vector;

	rotate(euler_angles);

}

} // strl