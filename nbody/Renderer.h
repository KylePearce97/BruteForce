#pragma once
#include <glm/glm.hpp>
class Renderer
{
public:
	Renderer() {};
	virtual ~Renderer() {};
	virtual void renderCircle(glm::dvec3 pos, double radius, int numPoints, glm::vec3 color) = 0;
	virtual void swap() = 0;
	virtual void init() = 0;
	virtual void destroy() = 0;
private:

};
