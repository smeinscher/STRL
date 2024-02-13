//
// Created by Sterling on 2/8/2024.
//

#ifndef STRLOBJECT_H
#define STRLOBJECT_H


#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/detail/type_quat.hpp>
#include "../util/observer/ISTRLSubject.h"

namespace strl
{

class STRLObject;

struct STRLObjectMessage
{
	enum STRLObjectUpdateType
	{
		POSITION,
		SIZE,
		ROTATION,
		POINTS,
		COLOR
	} update_type;

	STRLObject* object;
};

struct STRLObjectDefinition
{
	enum ShapeType2D {TRIANGLE, SQUARE, HEXAGON, OCTAGON};
	std::vector<glm::vec3> points;
	glm::vec3 position = {
		0.0f,
		0.0f,
		0.0f
	};
	glm::vec3 size = {
		1.0f,
		1.0f,
		1.0f
	};
	glm::vec4 color = {
		1.0f,
		1.0f,
		1.0f,
		1.0f
	};
	std::string name = "My Object";

	STRLObjectDefinition()
		: points({
		{
			1.0f,
			1.0f,
			0.0f
		},
		{
			1.0f,
			0.0f,
			0.0f
		},
		{
			0.0f,
			0.0f,
			0.0f
		},
		{
			0.0f,
			1.0f,
			0.0f
		}
	}) {}
	explicit STRLObjectDefinition(ShapeType2D type)
	{
		switch (type)
		{
		case TRIANGLE:
			points.emplace_back(0.0f, 0.0f, 0.0f);
			points.emplace_back(0.5f, 1.0f, 0.0f);
			points.emplace_back(1.0f, 0.0f, 0.0f);
			break;
		case SQUARE:
			points.emplace_back(0.0f, 0.0f, 0.0f);
			points.emplace_back(0.0f, 1.0f, 0.0f);
			points.emplace_back(1.0f, 1.0f, 0.0f);
			points.emplace_back(1.0f, 0.0f, 0.0f);
			break;
		case HEXAGON:
		{
			points.emplace_back(0.0f, 0.75f, 0.0f);
			points.emplace_back(0.5, 1.0f, 0.0f);
			points.emplace_back(1.0f, 0.75f, 0.0f);
			points.emplace_back(1.0f, 0.25f, 0.0f);
			points.emplace_back(0.5, 0.0f, 0.0f);
			points.emplace_back(0.0f, 0.25f, 0.0f);
			break;
		}
		case OCTAGON:
			// a - side length (w/ assumed diameter of 1)
			float a = 1.0f / (1.0f + std::sqrt(2.0f));
			float asqrt2 = a / std::sqrt(2.0f);
			points.emplace_back(0.0f, asqrt2 + a, 0.0f);
			points.emplace_back(asqrt2, 1.0f, 0.0f);
			points.emplace_back(asqrt2 + a, 1.0f, 0.0f);
			points.emplace_back(1.0f, asqrt2 + a, 0.0f);
			points.emplace_back(1.0f, asqrt2, 0.0f);
			points.emplace_back(asqrt2 + a, 0.0f, 0.0f);
			points.emplace_back(asqrt2, 0.0f, 0.0f);
			points.emplace_back(0.0f, asqrt2, 0.0f);
			break;
		}
	}
};

class STRLObject  : public ISTRLSubject<STRLObjectMessage>
{

public:

	STRLObject(STRLObjectDefinition& definition, int& render_data_index);
	~STRLObject() override;

	void attach(ISTRLObserver<STRLObjectMessage>* observer) override;
	void detach(ISTRLObserver<STRLObjectMessage>* observer) override;
	void notify(STRLObjectMessage& message) override;

	[[nodiscard]] const std::string& get_name() const;
	void set_name(std::string name);

	[[nodiscard]] const std::vector<std::string>& get_tags() const;
	void add_tag(std::string tag);
	void remove_tag(const std::string& tag);

	[[nodiscard]] int get_id() const;

	[[nodiscard]] const glm::vec3& get_position() const;
	void set_position(glm::vec3 position);
	void set_position_x(float x);
	void set_position_y(float y);
	void set_position_z(float z);
	[[nodiscard]] const glm::vec3& get_size() const;
	void set_size(glm::vec3 size);
	void set_size_x(float x);
	void set_size_y(float y);
	void set_size_z(float z);
	[[nodiscard]] glm::quat get_rotation() const;
	void set_rotation(float rotation);
	void set_rotation(glm::quat rotation);
	[[nodiscard]] const std::vector<glm::vec3>& get_points() const;
	[[nodiscard]] std::vector<glm::vec3> get_adjusted_points() const;
	void set_points(std::vector<glm::vec3> points);
	[[nodiscard]] const glm::vec4& get_color() const;
	void set_color(glm::vec4 color);
	void set_color_red(float red);
	void set_color_green(float green);
	void set_color_blue(float blue);
	void set_color_alpha(float alpha);

	[[nodiscard]] const int& get_render_data_index() const;

protected:
	std::string name_;
	std::vector<std::string> tags_;
	int id_;

	glm::vec3 position_;
	glm::vec3 size_;
	glm::quat rotation_;
	std::vector<glm::vec3> points_;
	glm::vec4 color_;

	void update_position();
	void update_size();
	void update_rotation();
	void update_points();
	void update_color();

	std::vector<ISTRLObserver<STRLObjectMessage>*> observers_;

	int& render_data_index_;

private:
	// TODO: find a thread-safe method of assigning IDs to objects
	static int id_accumulator_;

};

} // strl
#endif //STRLOBJECT_H
