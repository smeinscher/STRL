//
// Created by Sterling on 2/11/2024.
//

#include "RenderConversions.h"
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/epsilon.hpp>
#include <glm/ext/scalar_constants.hpp>

namespace strl
{

std::vector<int> RenderConversions::generate_polygon_indices(const std::vector<glm::vec3>& points)
{
	for (int i = 0; i < points.size(); i++)
	{
		glm::vec3 a = glm::normalize(points[i != 0 ? i - 1 : points.size() - 1] - points[i]);
		glm::vec3 b = glm::normalize(points[i != points.size() - 1 ? i + 1 : 0] - points[i]);
		float dot = glm::dot(a, b);
		if (std::acos(dot) >= std::numbers::pi)
		{
			// TODO: logging stuff
			std::cout << "Shape is concave" << std::endl;
			return {};//triangulate_concave_polygon(points);
		}
	}
	return generate_convex_polygon_indices(points);
}

std::vector<int> RenderConversions::textured_cube_indices()
{
	return {0,  1,  2,
	        0,  2,  3,
	        4,  5,  6,
	        4,  6,  7,
	        8,  9,  10,
	        8,  10, 11,
	        12, 13, 14,
			12, 14, 15,
			16, 17, 18,
			16, 18, 19,
			20, 21, 22,
			20, 22, 23};
}

std::vector<int> RenderConversions::cube_indices()
{
	return {0, 1, 2, 3,
			4, 5, 6, 7,
			0, 1, 5, 4,
			2, 3, 7, 6,
			0, 3, 7, 4,
			1, 2, 6, 5};
}

std::vector<int> RenderConversions::sphere_indices(int latitude_point_count, int longitude_point_count)
{
	std::vector<int> indices;
	// http://www.songho.ca/opengl/gl_sphere.html
	for (int i = 0; i < latitude_point_count - 1; i++)
	{
		int k1 = i * (longitude_point_count + 1);
		int k2 = k1 + longitude_point_count + 1;
		for (int j = 0; j < longitude_point_count; j++, k1++, k2++)
		{
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != latitude_point_count - 2)
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
	return indices;
}

std::vector<int> RenderConversions::generate_convex_polygon_indices(const std::vector<glm::vec3>& points)
{
	std::vector<int> indices;
	for (int i = 2; i < points.size(); i++)
	{
		indices.insert(indices.end(), {0, i - 1, i});
	}
	return indices;
}

std::vector<float> RenderConversions::triangulated_polygon(const std::vector<glm::vec3>& points)
{
	// TODO better way of checking if 3D
	float z0 = points[0].z;
	for (int i = 0; i < points.size(); i++)
	{

		if (glm::epsilonNotEqual(points[i].z, z0, glm::epsilon<float>()))
		{
			return triangulate_cube(points);
		}
		glm::vec3 a = glm::normalize(points[i != 0 ? i - 1 : points.size() - 1] - points[i]);
		glm::vec3 b = glm::normalize(points[i != points.size() - 1 ? i + 1 : 0] - points[i]);
		float dot = glm::dot(a, b);
		if (std::acos(dot) >= std::numbers::pi)
		{
			// TODO: logging stuff
			std::cout << "Shape is concave" << std::endl;
			return triangulate_concave_polygon(points);
		}
	}
	return triangulate_convex_polygon(points);
}

std::vector<float> RenderConversions::triangulate_convex_polygon(const std::vector<glm::vec3>& points)
{
	std::vector<float> triangulated_points;
	std::vector<std::tuple<glm::vec3, glm::vec3, glm::vec3>> triangles;
	for (int i = 2; i < points.size(); i++)
	{
		triangles.emplace_back(points[0], points[i - 1], points[i]);
	}
	for (auto& triangle : triangles)
	{
		glm::vec3 a = std::get<0>(triangle);
		glm::vec3 b = std::get<1>(triangle);
		glm::vec3 c = std::get<2>(triangle);

		triangulated_points.emplace_back(a.x);
		triangulated_points.emplace_back(a.y);
		triangulated_points.emplace_back(a.z);

		triangulated_points.emplace_back(b.x);
		triangulated_points.emplace_back(b.y);
		triangulated_points.emplace_back(b.z);

		triangulated_points.emplace_back(c.x);
		triangulated_points.emplace_back(c.y);
		triangulated_points.emplace_back(c.z);
	}
	return triangulated_points;
}

std::vector<float> RenderConversions::triangulate_concave_polygon(const std::vector<glm::vec3>& points)
{
	return {};
}

std::vector<float> RenderConversions::triangulate_cube(const std::vector<glm::vec3>& points)
{
	std::vector<float> triangulated_points;
	std::vector<std::tuple<glm::vec3, glm::vec3, glm::vec3>> triangles;

	// Front face
	triangles.emplace_back(points[0], points[1], points[2]);
	triangles.emplace_back(points[0], points[2], points[3]);
	// Right face
	triangles.emplace_back(points[4], points[0], points[3]);
	triangles.emplace_back(points[4], points[3], points[7]);
	// Back face
	triangles.emplace_back(points[4], points[5], points[6]);
	triangles.emplace_back(points[4], points[6], points[7]);
	// Left face
	triangles.emplace_back(points[1], points[5], points[6]);
	triangles.emplace_back(points[1], points[6], points[2]);
	// Top face
	triangles.emplace_back(points[4], points[5], points[1]);
	triangles.emplace_back(points[4], points[1], points[0]);
	// Bottom face
	triangles.emplace_back(points[3], points[2], points[6]);
	triangles.emplace_back(points[3], points[6], points[7]);

	for (auto& triangle : triangles)
	{
		glm::vec3 a = std::get<0>(triangle);
		glm::vec3 b = std::get<1>(triangle);
		glm::vec3 c = std::get<2>(triangle);

		triangulated_points.emplace_back(a.x);
		triangulated_points.emplace_back(a.y);
		triangulated_points.emplace_back(a.z);

		triangulated_points.emplace_back(b.x);
		triangulated_points.emplace_back(b.y);
		triangulated_points.emplace_back(b.z);

		triangulated_points.emplace_back(c.x);
		triangulated_points.emplace_back(c.y);
		triangulated_points.emplace_back(c.z);
	}
	return triangulated_points;
}

std::vector<float> RenderConversions::point_vec_to_float_vec(const std::vector<glm::vec3>& points)
{
	std::vector<float> float_points;
	for (const auto& point : points)
	{
		float_points.emplace_back(point.x);
		float_points.emplace_back(point.y);
		float_points.emplace_back(point.z);
	}
	return float_points;
}

std::vector<glm::vec3> RenderConversions::points_for_textured_cube(const std::vector<glm::vec3>& points)
{
	std::vector<glm::vec3> adjusted_points;

	// TODO: don't hard code these
	adjusted_points.emplace_back(points[0]);
	adjusted_points.emplace_back(points[1]);
	adjusted_points.emplace_back(points[2]);
	adjusted_points.emplace_back(points[3]);

	adjusted_points.emplace_back(points[4]);
	adjusted_points.emplace_back(points[5]);
	adjusted_points.emplace_back(points[6]);
	adjusted_points.emplace_back(points[7]);

	adjusted_points.emplace_back(points[4]);
	adjusted_points.emplace_back(points[0]);
	adjusted_points.emplace_back(points[3]);
	adjusted_points.emplace_back(points[7]);

	adjusted_points.emplace_back(points[5]);
	adjusted_points.emplace_back(points[1]);
	adjusted_points.emplace_back(points[2]);
	adjusted_points.emplace_back(points[6]);

	adjusted_points.emplace_back(points[4]);
	adjusted_points.emplace_back(points[5]);
	adjusted_points.emplace_back(points[1]);
	adjusted_points.emplace_back(points[0]);

	adjusted_points.emplace_back(points[7]);
	adjusted_points.emplace_back(points[6]);
	adjusted_points.emplace_back(points[2]);
	adjusted_points.emplace_back(points[3]);

	return adjusted_points;
}

std::vector<glm::vec3> RenderConversions::points_for_textured_sphere(const std::vector<glm::vec3>& points,
	int latitude_point_count,
	int longitude_point_count)
{
	std::vector<glm::vec3> adjusted_points;
	// http://www.songho.ca/opengl/gl_sphere.html
	int k1, k2;
	for (int i = 0; i < latitude_point_count - 1; i++)
	{
		k1 = i * (longitude_point_count + 1);
		k2 = k1 + longitude_point_count + 1;
		for (int j = 0; j < longitude_point_count; j++, k1++, k2++)
		{
			if (i != 0)
			{
				adjusted_points.push_back(points[k1]);
				adjusted_points.push_back(points[k2]);
				adjusted_points.push_back(points[k1 + 1]);
			}

			if (i != latitude_point_count - 2)
			{
				adjusted_points.push_back(points[k1 + 1]);
				adjusted_points.push_back(points[k2]);
				adjusted_points.push_back(points[k2 + 1]);
			}
		}
	}
	return adjusted_points;
}

} // strl