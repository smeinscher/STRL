//
// Created by Sterling on 2/11/2024.
//

#ifndef RENDERCONVERSIONS_H
#define RENDERCONVERSIONS_H

#include <vector>
#include <glm/vec3.hpp>

namespace strl
{

class RenderConversions
{
public:
	// TODO: change return type?
	static std::vector<int> generate_polygon_indices(const std::vector<glm::vec3>& points);
	static std::vector<int> textured_cube_indices();
	static std::vector<int> cube_indices();
	static std::vector<int> sphere_indices(int latitude_point_count, int longitude_point_count);
	static std::vector<int> generate_convex_polygon_indices(const std::vector<glm::vec3>& points);
	static std::vector<float> triangulated_polygon(const std::vector<glm::vec3>& points);
	static std::vector<float> triangulate_convex_polygon(const std::vector<glm::vec3>& points);
	static std::vector<float> triangulate_concave_polygon(const std::vector<glm::vec3>& points);
	static std::vector<float> triangulate_cube(const std::vector<glm::vec3>& points);

	static std::vector<float> point_vec_to_float_vec(const std::vector<glm::vec3>& points);
	static std::vector<glm::vec3> points_for_textured_cube(const std::vector<glm::vec3>& points);
	static std::vector<glm::vec3> points_for_textured_sphere(const std::vector<glm::vec3>& points,
		int latitude_point_count,
		int longitude_point_count);

};

} // strl

#endif //RENDERCONVERSIONS_H
