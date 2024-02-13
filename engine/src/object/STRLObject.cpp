//
// Created by Sterling on 2/8/2024.
//

#include "STRLObject.h"
#include "STRLObjectManager.h"
#include <algorithm>
#include <iostream>
//#include <glm/gtx/euler_angles.hpp>
//#include <glm/gtx/rotate_vector.hpp>

namespace strl
{

int STRLObject::id_accumulator_{0};

STRLObject::STRLObject(STRLObjectDefinition& definition, int& render_data_index)
	: points_(definition.points), position_(definition.position), size_(definition.size), color_(definition.color),
	rotation_(/*glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 0.0f))*/), name_(definition.name),
	render_data_index_(render_data_index)
{
	id_ = id_accumulator_++;
}

STRLObject::~STRLObject() = default;

const std::string& STRLObject::get_name() const
{
	return name_;
}

void STRLObject::set_name(std::string name)
{
	name_ = std::move(name);
}

const std::vector<std::string>& STRLObject::get_tags() const
{
	return tags_;
}

void STRLObject::add_tag(std::string tag)
{
	auto it = std::find(tags_.begin(), tags_.end(), tag);
	if (it == tags_.end())
	{
		tags_.emplace_back(std::move(tag));
		return;
	}
	// TODO: logging stuff
	std::cout << "Tag already present" << std::endl;
}

void STRLObject::remove_tag(const std::string& tag)
{
	auto it = tags_.begin();
	while (it != tags_.end())
	{
		if (*it == tag)
		{
			tags_.erase(it);
			return;
		}
	}
	// TODO: logging stuff
	std::cout << "Tag not found" << std::endl;
}

int STRLObject::get_id() const
{
	return id_;
}

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

void STRLObject::set_position_y(float y)
{
	position_.y = y;
	update_position();
}

void STRLObject::set_position_z(float z)
{
	position_.z = z;
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

void STRLObject::set_size_y(float y)
{
	size_.y = y;
	update_size();
}

void STRLObject::set_size_z(float z)
{
	size_.z = z;
	update_size();
}

const std::vector<glm::vec3>& STRLObject::get_points() const
{
	return points_;
}

void STRLObject::set_points(std::vector<glm::vec3> points)
{
	points_ = std::move(points);
	update_points();
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
		/*glm::vec3 angles = glm::eulerAngles(rotation_);
		point = glm::rotate(point, angles.x, glm::vec3(1.0f, 0.0f, 0.0f));
		point = glm::rotate(point, angles.y, glm::vec3(0.0f, 1.0f, 0.0f));
		point = glm::rotate(point, angles.z, glm::vec3(0.0f, 0.0f, 1.0f));*/
		point += position_;
	}
	return tmp_points;
}

glm::quat STRLObject::get_rotation() const
{
	return rotation_;
}

void STRLObject::set_rotation(float rotation)
{
	//rotation_ = glm::angleAxis(rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	update_rotation();
}

void STRLObject::set_rotation(glm::quat rotation)
{
	rotation_ = rotation;
	update_rotation();
}

void STRLObject::attach(ISTRLObserver<STRLObjectMessage>* observer)
{
	observers_.emplace_back(observer);
}

void STRLObject::detach(ISTRLObserver<STRLObjectMessage>* observer)
{
	auto it = std::find(observers_.begin(), observers_.end(), observer);
	if (it != observers_.end())
	{
		observers_.erase(it);
	}
}

void STRLObject::notify(STRLObjectMessage& message)
{
	for (auto observer : observers_)
	{
		observer->update(message);
	}
}

void STRLObject::update_position()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::POSITION};
	notify(message);
}

void STRLObject::update_size()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::SIZE};
	notify(message);
}

void STRLObject::update_rotation()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::ROTATION};
	notify(message);
}

void STRLObject::update_points()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::POINTS};
	notify(message);
}

void STRLObject::update_color()
{
	STRLObjectMessage message = {STRLObjectMessage::STRLObjectUpdateType::COLOR};
	notify(message);
}

const int& STRLObject::get_render_data_index() const
{
	return render_data_index_;
}

} // strl