//
// Created by Sterling on 2/11/2024.
//

#include "Triangulation.h"
#include <glm/glm.hpp>
#include <iostream>

namespace strl
{

std::vector<float> Triangulation::triangulated_polygon(const std::vector<glm::vec3>& points)
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
			return triangulate_concave_polygon(points);
		}
	}
	return triangulate_convex_polygon(points);
}

std::vector<float> Triangulation::triangulate_convex_polygon(const std::vector<glm::vec3>& points)
{
	std::vector<float> triangulated_points;
	std::vector<std::tuple<glm::vec3, glm::vec3, glm::vec3>> triangles;
	for (int i = 2; i < points.size(); i++)
	{
		triangles.emplace_back(points[0], points[i - 1], points[i]);
	}
	for (auto triangle : triangles)
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

std::vector<float> Triangulation::triangulate_concave_polygon(const std::vector<glm::vec3>& points)
{
	return {};
}

} // strl