//
// Created by SterlingMeinscher on 2/21/2024.
//

#ifndef STRLCAMERA_H
#define STRLCAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace strl
{

class STRLCamera
{
public:
	STRLCamera(float camera_view_width, float camera_view_height);
	[[nodiscard]] glm::mat4 get_projection() const;
	[[nodiscard]] glm::mat4 get_view() const;

	glm::vec3& get_position();
	glm::vec3& get_front();
	glm::vec3& get_up();

	glm::vec3& get_euler_angles();

	[[nodiscard]] float get_camera_view_width() const;
	[[nodiscard]] float get_camera_view_height() const;

	void update_camera_vectors();

private:
	glm::vec3 position_ = {0.0f, 0.0f, 40.0f};
	glm::vec3 front_ = {0.0f, 0.0f, -1.0f};
	glm::vec3 up_ = {0.0f, 1.0f, 0.0f};
	glm::vec3 right_;

	glm::vec3 euler_angles_ = {0.0f, 3 * glm::pi<float>() / 2, 0.0f};

	float camera_view_width_;
	float camera_view_height_;
};

} // strl

#endif //STRLCAMERA_H
