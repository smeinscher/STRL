//
// Created by SterlingMeinscher on 2/21/2024.
//

#ifndef STRLCAMERA_H
#define STRLCAMERA_H

#include "../util/manager/STRLManagedItemBase.h"
#include <glm/gtc/constants.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace strl
{

class STRLCamera : public STRLManagedItemBase
{
  public:
    STRLCamera(std::string name, std::vector<std::string> tags, float camera_view_width, float camera_view_height);

    [[nodiscard]] glm::mat4 get_projection() const;
    [[nodiscard]] glm::mat4 get_view() const;

    glm::vec3 &get_position();
    void set_position(glm::vec3 position);
    void move_position(glm::vec3 amount);
    glm::vec3 &get_front();
    glm::vec3 &get_up();

    glm::vec3 &get_euler_angles();
    void set_euler_angles(glm::vec3 angles);
    void rotate(glm::vec3 amount);

    [[nodiscard]] float get_camera_view_width() const;
    [[nodiscard]] float get_camera_view_height() const;
    void set_camera_view_width_and_height(float camera_view_width, float camera_view_height);
    void set_view_width_maintain_ratio(float width);
    void set_view_height_maintain_ratio(float height);

    float get_zoom() const;
    void set_zoom(float zoom);
    void increment_zoom(float amount);

    void set_is_ortho(bool is_ortho);

    void update_camera_vectors();

    void rotate_around_point(glm::vec3 point, glm::vec3 euler_angles);

  private:
    glm::vec3 position_{0.0f, 0.0f, 2.0f};
    glm::vec3 front_{0.0f, 0.0f, -1.0f};
    glm::vec3 up_{0.0f, 1.0f, 0.0f};
    glm::vec3 right_{};

    glm::vec3 euler_angles_{0.0f, 3 * glm::pi<float>() / 2, 0.0f};

    float camera_view_width_;
    float camera_view_height_;

    float max_zoom_ = 90.0f;
    float min_zoom_ = 10.0f;
    float zoom_{45.0f};

    bool is_ortho_{false};
};

} // namespace strl

#endif // STRLCAMERA_H
