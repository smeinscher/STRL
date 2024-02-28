//
// Created by SterlingMeinscher on 2/21/2024.
//

#ifndef STRLCAMERA_H
#define STRLCAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "../util/manager/STRLManagedItemBase.h"

namespace strl
{

class STRLCamera : public STRLManagedItemBase
{
public:
	STRLCamera(std::string name,
		std::vector<std::string> tags,
		float camera_view_width,
		float camera_view_height);

	[[nodiscard]] glm::mat4 get_projection() const;
	[[nodiscard]] glm::mat4 get_view() const;

	glm::vec3& get_position();
	glm::vec3& get_front();
	glm::vec3& get_up();

	glm::vec3& get_euler_angles();

	[[nodiscard]] float get_camera_view_width() const;
	[[nodiscard]] float get_camera_view_height() const;
	void set_camera_view_width_and_height(float camera_view_width, float camera_view_height);
	void set_view_width_maintain_ratio(float width);
	void set_view_height_maintain_ratio(float height);

	void set_zoom(float zoom);

	void set_is_ortho(bool is_ortho);

	void update_camera_vectors();

private:
	glm::vec3 position_{0.0f, 0.0f, 40.0f};
	glm::vec3 front_{0.0f, 0.0f, -1.0f};
	glm::vec3 up_{0.0f, 1.0f, 0.0f};
	glm::vec3 right_{};

	glm::vec3 euler_angles_{0.0f, 3 * glm::pi<float>() / 2, 0.0f};

	float camera_view_width_;
	float camera_view_height_;

	float zoom_{45.0f};

	bool is_ortho_{false};
};

} // strl

#endif //STRLCAMERA_H
