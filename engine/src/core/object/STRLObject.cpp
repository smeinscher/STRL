//
// Created by Sterling on 2/8/2024.
//

#include "STRLObject.h"
#include <algorithm>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "../../util/algorithm/RenderConversions.h"

namespace strl
{

STRLObject::STRLObject(STRLObjectDefinition& definition)
	: STRLManagedItemBase(definition.name.empty() ? "My Object" : definition.name, definition.tags),
	  points_(definition.points), face_count_(definition.face_count), position_(definition.position),
	  size_(definition.size), uv_(definition.uv), color_(definition.color), rotation_(definition.rotation)
{
}

STRLObject::~STRLObject() = default;

const glm::vec3& STRLObject::get_position() const
{
	return position_;
}

void STRLObject::set_position(glm::vec3 position)
{
	position_ = position;
	update_position();
}

void STRLObject::set_position_x(float x)
{
	position_.x = x;
	update_position();
}

void STRLObject::move_position_x(float x)
{
	position_.x += x;
	update_position();
}

void STRLObject::set_position_y(float y)
{
	position_.y = y;
	update_position();
}

void STRLObject::move_position_y(float y)
{
	position_.y += y;
	update_position();
}

void STRLObject::set_position_z(float z)
{
	position_.z = z;
	update_position();
}

void STRLObject::move_position_z(float z)
{
	position_.z += z;
	update_position();
}

const glm::vec3& STRLObject::get_size() const
{
	return size_;
}

void STRLObject::set_size(glm::vec3 size)
{
	size_ = size;
	update_size();
}

void STRLObject::set_size_x(float x)
{
	size_.x = x;
	update_size();
}

void STRLObject::move_size_x(float x)
{
	size_.x += x;
	update_size();
}

void STRLObject::set_size_y(float y)
{
	size_.y = y;
	update_size();
}

void STRLObject::move_size_y(float y)
{
	size_.y += y;
	update_size();
}

void STRLObject::set_size_z(float z)
{
	size_.z = z;
	update_size();
}

void STRLObject::move_size_z(float z)
{
	size_.z = z;
	update_size();
}

Rotation STRLObject::get_rotation() const
{
	return rotation_;
}

void STRLObject::set_rotation(glm::vec3 rotation)
{
	rotation_.euler = rotation;
	float x = using_radians_ ? rotation_.euler.x : glm::radians(rotation_.euler.x);
	float y = using_radians_ ? rotation_.euler.y : glm::radians(rotation_.euler.y);
	float z = using_radians_ ? rotation_.euler.z : glm::radians(rotation_.euler.z);
	rotation_.quaternion = glm::angleAxis(x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotation_.quaternion *= glm::angleAxis(y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation_.quaternion *= glm::angleAxis(z, glm::vec3(0.0f, 0.0f, 1.0f));
	update_rotation();
}

void STRLObject::set_rotation(glm::quat rotation)
{
	rotation_.quaternion = rotation;
	rotation_.euler = glm::eulerAngles(rotation_.quaternion);
	if (!using_radians_)
	{
		rotation_.euler = glm::degrees(rotation_.euler);
	}
	update_rotation();
}

const std::vector<glm::vec3>& STRLObject::get_points() const
{
	return points_;
}

void STRLObject::set_points(std::vector<glm::vec3> points, int face_count)
{
	size_t old_triangulated_point_size = points_.size();
	size_t new_triangulated_point_size = points.size();
	points_ = std::move(points);
	face_count_ = face_count;
	update_points(new_triangulated_point_size - old_triangulated_point_size);
}

int STRLObject::get_face_count() const
{
	return face_count_;
}

int STRLObject::get_edge_count() const
{
	return face_count_ > 1
		? points_.size() + face_count_ - 2
		: points_.size();
}

const std::vector<glm::vec2>& STRLObject::get_uv() const
{
	return uv_;
}

void STRLObject::set_uv(std::vector<glm::vec2> uv)
{
	uv_ = std::move(uv);
	update_uv();
}

const glm::vec4& STRLObject::get_color() const
{
	return color_;
}

void STRLObject::set_color(glm::vec4 color)
{
	color_ = color;
	update_color();
}

void STRLObject::set_color_red(float red)
{
	color_.r = red;
	update_color();
}

void STRLObject::set_color_green(float green)
{
	color_.g = green;
	update_color();
}

void STRLObject::set_color_blue(float blue)
{
	color_.b = blue;
	update_color();
}

void STRLObject::set_color_alpha(float alpha)
{
	color_.a = alpha;
	update_color();
}

std::vector<glm::vec3> STRLObject::get_adjusted_points() const
{
	std::vector<glm::vec3> tmp_points = points_;
	for (auto& point : tmp_points)
	{
		point *= size_;
		if (using_euler_rotation_)
		{
			point = glm::rotateX(point, rotation_.euler.x);
			point = glm::rotateY(point, rotation_.euler.y);
			point = glm::rotateZ(point, rotation_.euler.z);
			/*float old_x = point.x;
			float old_y = point.y;
			float old_z = point.z;
			point.y = std::cos(rotation_.euler.x) * old_y - std::sin(rotation_.euler.x) * old_z;
			point.z = std::sin(rotation_.euler.x) * old_y + std::cos(rotation_.euler.x) * old_z;
			point.x = std::cos(rotation_.euler.y) * old_x + std::sin(rotation_.euler.y) * old_z;
			point.z = -std::sin(rotation_.euler.y) * old_x + std::cos(rotation_.euler.y) * old_z;
			point.x = std::cos(rotation_.euler.z) * old_x - std::sin(rotation_.euler.z) * old_y;
			point.y = std::sin(rotation_.euler.z) * old_x + std::cos(rotation_.euler.z) * old_y;*/
		}
		else
		{
			// TODO: quaternion rotation
		}
		point += position_;
	}
	return tmp_points;
}

int STRLObject::get_render_data_object_id() const
{
	return render_data_object_id_;
}

void STRLObject::set_render_data_object_id(int id)
{
	render_data_object_id_ = id;
}

int STRLObject::get_render_data_index() const
{
	return render_data_index_;
}

void STRLObject::set_render_data_index(int index)
{
	render_data_index_ = index;
}

void STRLObject::force_update_all()
{
	update_position();
	update_size();
	update_rotation();
	update_points();
	update_color();
}

void STRLObject::update_position()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::POSITION, this};
	observer_subject_.notify(message);
}

void STRLObject::update_size()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::SIZE, this};
	observer_subject_.notify(message);
}

void STRLObject::update_rotation()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::ROTATION, this};
	observer_subject_.notify(message);
}

void STRLObject::update_points(int point_change_count)
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::POINTS, this,
								 point_change_count};
	observer_subject_.notify(message);
}

void STRLObject::update_uv()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::UV, this};
	observer_subject_.notify(message);
}

void STRLObject::update_color()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::COLOR, this};
	observer_subject_.notify(message);
}

int STRLObject::get_render_data_positions_location() const
{
	return render_data_positions_location_;
}

void STRLObject::set_render_data_position_location(int render_data_position_location)
{
	render_data_positions_location_ = render_data_position_location;
}

void STRLObject::move_render_data_position_location(int amount)
{
	render_data_indices_location_ += amount;
}

int STRLObject::get_render_data_indices_location() const
{
	return render_data_indices_location_;
}

void STRLObject::set_render_data_indices_location(int render_data_indices_location)
{
	render_data_indices_location_ = render_data_indices_location;
}

void STRLObject::move_render_data_indices_location(int amount)
{
	render_data_indices_location_ += amount;
}

STRLSubjectBase<STRLObjectMessage>& STRLObject::get_observer_subject()
{
	return observer_subject_;
}

} // strl