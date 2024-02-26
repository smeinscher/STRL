//
// Created by SterlingMeinscher on 2/21/2024.
//

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "STRLCamera.h"

namespace strl
{

STRLCamera::STRLCamera(float camera_view_width, float camera_view_height)
	: camera_view_width_(camera_view_width), camera_view_height_(camera_view_height)
{

}

glm::mat4 STRLCamera::get_projection() const
{
	return glm::perspective(glm::radians(45.0f),
		static_cast<float>(camera_view_width_) / static_cast<float>(camera_view_height_),
		0.1f, 100.0f);
}

glm::mat4 STRLCamera::get_view() const
{
	return glm::lookAt(position_, position_ + front_, up_);;
}

glm::vec3& STRLCamera::get_position()
{
	return position_;
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

float STRLCamera::get_camera_view_width() const
{
	return camera_view_width_;
}

float STRLCamera::get_camera_view_height() const
{
	return camera_view_height_;
}

void STRLCamera::update_camera_vectors()
{
	front_.x = std::cos(euler_angles_.y) * std::cos(euler_angles_.z);
	front_.y = std::sin(euler_angles_.z);
	front_.z = std::sin(euler_angles_.y) * std::cos(euler_angles_.z);
	front_ = glm::normalize(front_);
	right_ = glm::normalize(glm::cross(front_, {0.0f, 1.0f, 0.0f}));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up_ = glm::normalize(glm::cross(right_, front_));
}

} // strl