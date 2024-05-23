//
// Created by SterlingMeinscher on 2/21/2024.
//

#include "STRLCamera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace strl
{

STRLCamera::STRLCamera(STRLCameraDefinition &definition) : STRLObject(definition)
{
}

glm::mat4 STRLCamera::get_projection() const
{
    return !is_ortho_ ? glm::perspective(glm::radians(zoom_), size_.x / size_.y, 0.1f, size_.z)
                      : glm::ortho(0.0f, size_.x, size_.y, 0.0f, 0.1f, size_.z);
}

glm::mat4 STRLCamera::get_view() const
{
    return glm::lookAt(position_, position_ + front_, up_);
    ;
}

glm::vec3 &STRLCamera::get_front()
{
    return front_;
}

glm::vec3 &STRLCamera::get_up()
{
    return up_;
}

float STRLCamera::get_view_width() const
{
    return size_.x;
}

float STRLCamera::get_view_height() const
{
    return size_.y;
}

void STRLCamera::set_view_width_and_height(float camera_view_width, float camera_view_height)
{
    size_.x = camera_view_width;
    size_.y = camera_view_height;
}

void STRLCamera::set_view_width_maintain_ratio(float width)
{
    float ratio = size_.x / size_.y;
    size_.x = width;
    size_.y = width / ratio;
}

void STRLCamera::set_view_height_maintain_ratio(float height)
{
    float ratio = size_.x / size_.y;
    size_.x = height * ratio;
    size_.y = height;
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
    front_.x = std::cos(rotation_.euler.y) * std::cos(rotation_.euler.z);
    front_.y = -std::sin(rotation_.euler.z);
    front_.z = std::sin(rotation_.euler.y) * std::cos(rotation_.euler.z);
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

} // namespace strl
