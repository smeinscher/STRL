//
// Created by Sterling on 2/11/2024.
//

#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include <glm/vec3.hpp>

namespace strl
{

class Triangulation
{
public:
	static std::vector<float> triangulated_polygon(const std::vector<glm::vec3>& points);
	static std::vector<float> triangulate_convex_polygon(const std::vector<glm::vec3>& points);
	static std::vector<float> triangulate_concave_polygon(const std::vector<glm::vec3>& points);
};

} // strl

#endif //TRIANGULATION_H
