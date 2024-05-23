//
// Created by SterlingMeinscher on 2/21/2024.
//

#ifndef STRLCAMERA_H
#define STRLCAMERA_H

#include "../core/object/STRLObject.h"
#include <glm/gtc/constants.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace strl
{

struct STRLCameraDefinition : STRLObjectDefinition
{
    STRLCameraDefinition(float camera_view_width, float camera_view_height, float camera_view_depth = 100.0f)
        : STRLObjectDefinition({}, {}, STRLObjectType::CAMERA)
    {
        position = {0.0f, 0.0f, 2.0f};
        if (camera_view_depth < 0.1f)
        {
            // TODO: logging stuff
            std::cout << "Depth should not be under 0.1f. Defaulting to 100.0f" << std::endl;
            camera_view_depth = 100.0f;
        }
        size = {camera_view_width, camera_view_height, camera_view_depth};
    }
};

class STRLCamera : public STRLObject
{
  public:
    STRLCamera(STRLCameraDefinition &definition);
    [[nodiscard]] glm::mat4 get_projection() const;
    [[nodiscard]] glm::mat4 get_view() const;

    glm::vec3 &get_front();
    glm::vec3 &get_up();

    [[nodiscard]] float get_view_width() const;
    [[nodiscard]] float get_view_height() const;
    void set_view_width_and_height(float camera_view_width, float camera_view_height);
    void set_view_width_maintain_ratio(float width);
    void set_view_height_maintain_ratio(float height);

    float get_zoom() const;
    void set_zoom(float zoom);
    void increment_zoom(float amount);

    void set_is_ortho(bool is_ortho);

    void update_camera_vectors();

    void rotate_around_point(glm::vec3 point, glm::vec3 euler_angles);

  private:
    glm::vec3 front_{0.0f, 0.0f, -1.0f};
    glm::vec3 up_{0.0f, 1.0f, 0.0f};
    glm::vec3 right_{};

    float max_zoom_ = 90.0f;
    float min_zoom_ = 10.0f;
    float zoom_{45.0f};

    bool is_ortho_{false};
};

} // namespace strl

#endif // STRLCAMERA_H
