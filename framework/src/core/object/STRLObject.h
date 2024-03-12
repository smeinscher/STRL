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
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "../../util/observer/STRLSubjectBase.h"
#include "../scripting/STRLNativeScriptHandler.h"
#include "../../util/manager/STRLManagedItemBase.h"

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
		UV,
		COLOR
	} update_type = STRLObjectUpdateType::POSITION;

	STRLObject* object = nullptr;

	// TODO: make this more generic
	int points_change_count = 0;
};

struct Rotation
{
	glm::vec3 euler = {0.0f, 0.0f, 0.0f};
	glm::quat quaternion = {1.0f, 0.0f, 0.0f, 0.0f};
};

enum class STRLShapeType2D {TRIANGLE, SQUARE, PENTAGON, HEXAGON, OCTAGON, CIRCLE32, CIRCLE64, MAX_SHAPE};
enum class STRLObjectType {SHAPE2D, CUBE, SPHERE1836, MAX_TYPE};

inline constexpr std::vector<glm::vec3> generate_convex_polygon(int point_count, float rotation = glm::pi<float>() / 4)
{
	std::vector<glm::vec3> polygon;
	float angle = 0.0f;
	float angle_increment = 2.0f * glm::pi<float>() / static_cast<float>(point_count);
	for (int i = 0; i < point_count; i++)
	{
		float x = std::cos(angle);
		float y = std::sin(angle);
		float old_x = x;
		float old_y = y;
		x = std::cos(rotation) * old_x - std::sin(rotation) * old_y;
		y = std::sin(rotation) * old_x + std::cos(rotation) * old_y;
		polygon.emplace_back(x, y, 0.0f);
		angle += angle_increment;
	}
	return polygon;
}

inline constexpr std::vector<glm::vec2> generate_convex_polygon_vec2(int point_count, float rotation = glm::pi<float>() / 4)
{
	std::vector<glm::vec2> polygon;
	float angle = 0.0f;
	float angle_increment = 2.0f * glm::pi<float>() / static_cast<float>(point_count);
	for (int i = 0; i < point_count; i++)
	{
		float x = std::cos(angle);
		float y = std::sin(angle);
		float old_x = x;
		float old_y = y;
		x = std::cos(rotation) * old_x - std::sin(rotation) * old_y;
		y = std::sin(rotation) * old_x + std::cos(rotation) * old_y;
		polygon.emplace_back(x, y);
		angle += angle_increment;
	}
	return polygon;
}

inline constexpr std::vector<glm::vec3> generate_cube()
{
	std::vector<glm::vec3> cube;
	std::vector<glm::vec3> front_side = generate_convex_polygon(4);
	float sqrt2d2 = std::sqrt(2.0f) / 2.0f;
	for (auto& point : front_side)
	{
		point.z += sqrt2d2;
	}
	cube.insert(cube.end(), front_side.begin(), front_side.end());
	std::vector<glm::vec3> back_side = generate_convex_polygon(4);
	for (auto& point : back_side)
	{
		point.z -= sqrt2d2;
	}
	cube.insert(cube.end(), back_side.begin(), back_side.end());
	return cube;
}

inline constexpr std::vector<glm::vec3> generate_sphere(int latitude_point_count, int longitude_point_count)
{
	std::vector<glm::vec3> sphere;
	float latitude_step = glm::pi<float>() / static_cast<float>(latitude_point_count - 1);
	float longitude_step = 2.0f * glm::pi<float>() / static_cast<float>(longitude_point_count);
	for (int i = 0; i < latitude_point_count; i++)
	{
		float latitude_angle = glm::pi<float>() / 2.0f - static_cast<float>(i) * latitude_step;
		float xz = std::cos(latitude_angle);
		float y = std::sin(latitude_angle);
		for (int j = 0; j <= longitude_point_count; j++)
		{
			float longitude_angle = static_cast<float>(j) * longitude_step;
			float x = xz * std::cos(longitude_angle);
			float z = xz * std::sin(longitude_angle);
			sphere.emplace_back(x, y, z);
		}
	}
	return sphere;
}

inline constexpr std::vector<glm::vec2> generate_uv_for_sphere(int latitude_point_count, int longitude_point_count)
{
	std::vector<glm::vec2> sphere_uv;
	for (int i = 0; i < latitude_point_count; i++)
	{
		for (int j = longitude_point_count; j >= 0; j--)
		{
			float u = static_cast<float>(j) / static_cast<float>(longitude_point_count);
			float v = static_cast<float>(i) / static_cast<float>(latitude_point_count - 1);
			sphere_uv.emplace_back(u, v);
		}
	}
	return sphere_uv;
}

inline constexpr glm::vec2 convert_point_to_uv(glm::vec2 point)
{
	if (point.x > 0.0f)
	{
		point.x = 1.0f;
	}
	else
	{
		point.x = 0.0f;
	}
	if (point.y > 0.0f)
	{
		point.y = 1.0f;
	}
	else
	{
		point.y = 0.0f;
	}
	return point;
}

inline constexpr std::vector<glm::vec2> generate_uv_for_cube()
{
	std::vector<glm::vec2> uvs;
	// Front face
	std::vector<glm::vec2> part = generate_convex_polygon_vec2(4);
	for (auto& point : part)
	{
		point = convert_point_to_uv(point);
	}
	uvs.insert(uvs.end(), part.begin(), part.end());

	// Back face
	part = generate_convex_polygon_vec2(4);
	for (auto& point : part)
	{
		point = convert_point_to_uv(point);
	}
	uvs.insert(uvs.end(), part.begin(), part.end());

	// Right face
	part = generate_convex_polygon_vec2(4);
	for (auto& point : part)
	{
		point = convert_point_to_uv(point);
	}
	uvs.insert(uvs.end(), part.begin(), part.end());

	// Left face
	part = generate_convex_polygon_vec2(4);
	for (auto& point : part)
	{
		point = convert_point_to_uv(point);
		point.x = std::abs(point.x - 1.0f);
	}
	uvs.insert(uvs.end(), part.begin(), part.end());

	// Up face
	part = generate_convex_polygon_vec2(4);
	for (auto& point : part)
	{
		point = convert_point_to_uv(point);
	}
	uvs.insert(uvs.end(), part.begin(), part.end());

	// Down face
	part = generate_convex_polygon_vec2(4);
	for (auto& point : part)
	{
		point = convert_point_to_uv(point);
		point.y = std::abs(point.y - 1.0f);
	}
	uvs.insert(uvs.end(), part.begin(), part.end());


	return uvs;
}

inline constexpr std::vector<glm::vec3> generate_cube_for_textures(std::vector<glm::vec3> cube_points)
{
	std::vector<glm::vec3> cube;
	std::vector<glm::vec3> part = std::move(cube_points);
	cube.insert(cube.end(), part.begin(), part.end());
	part = generate_cube();
	for (auto& point : part)
	{
		point = glm::rotateY(point, glm::pi<float>() / 2);
	}
	cube.insert(cube.end(), part.begin(), part.end());
	part = generate_cube();
	for (auto& point : part)
	{
		point = glm::rotateX(point, -glm::pi<float>() / 2);
	}
	cube.insert(cube.end(), part.begin(), part.end());

	return cube;
}

inline constexpr std::vector<glm::vec3> generate_cube_for_textures()
{
	return generate_cube_for_textures(generate_cube());
}

const std::vector<glm::vec3> STRL_SHAPE2D_TRIANGLE_VERTICES = generate_convex_polygon(3);

const std::vector<glm::vec3> STRL_SHAPE2D_SQUARE_VERTICES = generate_convex_polygon(4);

const std::vector<glm::vec3> STRL_SHAPE2D_PENTAGON_VERTICES = generate_convex_polygon(5);

const std::vector<glm::vec3> STRL_SHAPE2D_HEXAGON_VERTICES = generate_convex_polygon(6);

const std::vector<glm::vec3> STRL_SHAPE2D_OCTAGON_VERTICES = generate_convex_polygon(8);

const std::vector<glm::vec3> STRL_SHAPE2D_CIRCLE32_VERTICES = generate_convex_polygon(32);

const std::vector<glm::vec3> STRL_SHAPE2D_CIRCLE64_VERTICES = generate_convex_polygon(64);

const std::vector<glm::vec3> STRL_SHAPE3D_CUBE_VERTICES = generate_cube();

const std::vector<glm::vec3> STRL_SHAPE3D_CUBE_TRIANGULATED{
	// Back face
	{-0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f},
	{-0.5f, 0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},

	// Front face
	{-0.5f, -0.5f, 0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, 0.5f},
	{-0.5f, -0.5f, 0.5f},

	{-0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, 0.5f},
	{-0.5f, 0.5f, 0.5f},

	{0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},

	{-0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, -0.5f, 0.5f},
	{-0.5f, -0.5f, 0.5f},
	{-0.5f, -0.5f, -0.5f},

	{-0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, -0.5f}
};

const std::vector<glm::vec3> STRL_SHAPE3D_CUBE_NORMALS{
	// Back face
	{0.0f, 0.0f, -1.0f},
	{0.0f, 0.0f, -1.0f},
	{0.0f, 0.0f, -1.0f},
	{0.0f, 0.0f, -1.0f},
	{0.0f, 0.0f, -1.0f},
	{0.0f, 0.0f, -1.0f},

	// Front face
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},

	// Left face
	{-1.0f, 0.0f, 0.0f},
	{-1.0f, 0.0f, 0.0f},
	{-1.0f, 0.0f, 0.0f},
	{-1.0f, 0.0f, 0.0f},
	{-1.0f, 0.0f, 0.0f},
	{-1.0f, 0.0f, 0.0f},

	// Right face
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},

	{0.0f, -1.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},

	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f}
};

const std::vector<glm::vec2> STRL_SHAPE2D_DEFAULT_UV{
	// top right
	{1.0f, 1.0f},
	// top left
	{0.0f, 1.0f},
	// bottom left
	{0.0f, 0.0f},
	// bottom right
	{1.0f, 0.0f},
};

const std::vector<glm::vec2> STRL_SHAPE2D_TRIANGULATED_UV{
	// top right
	{1.0f, 1.0f},
	// top left
	{0.0f, 1.0f},
	// bottom left
	{0.0f, 0.0f},
	// top right
	{1.0f, 1.0f},
	// bottom left
	{0.0f, 0.0f},
	// bottom right
	{1.0f, 0.0f},

};

struct STRLObjectDefinition : STRLManagedItemDefinitionBase
{
	std::vector<glm::vec3> points;
	STRLObjectType object_type;
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
	std::vector<glm::vec2> uv;
	glm::vec4 color = {
		1.0f,
		1.0f,
		1.0f,
		1.0f
	};
	Rotation rotation{{0.0f, 0.0f, 0.0f}};

	STRLObjectDefinition()
		: points(STRL_SHAPE2D_SQUARE_VERTICES), uv(STRL_SHAPE2D_DEFAULT_UV), object_type(STRLObjectType::SHAPE2D)
	{}

	STRLObjectDefinition(std::vector<glm::vec3> points, std::vector<glm::vec2> uv, STRLObjectType object_type)
		: points(std::move(points)), uv(std::move(uv)), object_type(object_type)
	{}

	explicit STRLObjectDefinition(STRLShapeType2D type)
		: object_type(STRLObjectType::SHAPE2D)
	{
		switch (type)
		{
		case STRLShapeType2D::TRIANGLE:
			points = STRL_SHAPE2D_TRIANGLE_VERTICES;
			break;
		case STRLShapeType2D::SQUARE:
			points = STRL_SHAPE2D_SQUARE_VERTICES;
			uv = STRL_SHAPE2D_DEFAULT_UV;
			break;
		case STRLShapeType2D::PENTAGON:
			points = STRL_SHAPE2D_PENTAGON_VERTICES;
			break;
		case STRLShapeType2D::HEXAGON:
			points = STRL_SHAPE2D_HEXAGON_VERTICES;
			break;
		case STRLShapeType2D::OCTAGON:
			points = STRL_SHAPE2D_OCTAGON_VERTICES;
			break;
		case STRLShapeType2D::CIRCLE32:
			points = STRL_SHAPE2D_CIRCLE32_VERTICES;
			break;
		case STRLShapeType2D::CIRCLE64:
			points = STRL_SHAPE2D_CIRCLE64_VERTICES;
			break;
		default:
			points = STRL_SHAPE2D_SQUARE_VERTICES;
			uv = STRL_SHAPE2D_DEFAULT_UV;
			break;
		}
	}
};

class STRLObject  : public STRLManagedItemBase
{

public:

	explicit STRLObject(STRLObjectDefinition& definition);
	~STRLObject();

	[[nodiscard]] const glm::vec3& get_position() const;
	void set_position(glm::vec3 position);
	void set_position_x(float x);
	void move_position_x(float x);
	void set_position_y(float y);
	void move_position_y(float y);
	void set_position_z(float z);
	void move_position_z(float z);
	[[nodiscard]] const glm::vec3& get_size() const;
	void set_size(glm::vec3 size);
	void set_size_x(float x);
	void move_size_x(float x);
	void set_size_y(float y);
	void move_size_y(float y);
	void set_size_z(float z);
	void move_size_z(float z);
	[[nodiscard]] Rotation get_rotation() const;
	void set_rotation(glm::vec3 rotation);
	void set_rotation(glm::quat rotation);
	void rotate(glm::vec3 amount);
	void rotate(glm::quat rotation);
	[[nodiscard]] const std::vector<glm::vec3>& get_points() const;
	[[nodiscard]] std::vector<glm::vec3> get_adjusted_points() const;
	void set_points(std::vector<glm::vec3> points, STRLObjectType object_type = STRLObjectType::SHAPE2D);
	[[nodiscard]] STRLObjectType get_object_type() const;
	[[nodiscard]] const std::vector<glm::vec2>& get_uv() const;
	void set_uv(std::vector<glm::vec2> uv);
	[[nodiscard]] const glm::vec4& get_color() const;
	void set_color(glm::vec4 color);
	void set_color_red(float red);
	void set_color_green(float green);
	void set_color_blue(float blue);
	void set_color_alpha(float alpha);

	[[nodiscard]] int get_render_data_object_id() const;
	void set_render_data_object_id(int id);

	[[nodiscard]] int get_render_data_index() const;
	void set_render_data_index(int index);

	[[nodiscard]] int get_render_data_positions_location() const;
	void set_render_data_position_location(int render_data_position_location);
	void move_render_data_position_location(int amount);
	[[nodiscard]] int get_render_data_indices_location() const;
	void set_render_data_indices_location(int render_data_indices_location);
	void move_render_data_indices_location(int amount);

	STRLSubjectBase<STRLObjectMessage>& get_observer_subject();

	void force_update_all();

protected:
	glm::vec3 position_;
	glm::vec3 size_;
	Rotation rotation_;
	bool using_euler_rotation_{true};
	bool using_radians_{true};
	std::vector<glm::vec3> points_;
	STRLObjectType object_type_;
	std::vector<glm::vec2> uv_;
	glm::vec4 color_;

	int render_data_object_id_{-1};
	int render_data_index_{-1};
	int render_data_positions_location_{-1};
	int render_data_indices_location_{-1};

	STRLSubjectBase<STRLObjectMessage> observer_subject_;

	void update_position();
	void update_size();
	void update_rotation();
	void update_points(int point_change_count = 0);
	void update_uv();
	void update_color();

};

} // strl
#endif //STRLOBJECT_H
