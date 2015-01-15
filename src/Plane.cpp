#include "Plane.h"

Plane::Plane(const vector3_t& anchor, const vector3_t& normal)
	: anchor(anchor), normal(normal)
{}

hitresult_t Plane::intersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal_a) {
	double ldotn = ray.direction.dot(normal);
	if(ldotn == 0)
		return MISS;

	distance = normal.dot(anchor - ray.origin) / ldotn;
	hit = ray.origin + distance * ray.direction;
	normal_a = normal;

	if(distance < 0) {
		return MISS;
	} else {
		return ldotn < 0 ? HIT : INSIDE;
	}
}

void Plane::getLightPoints(forward_list<vector3_t>& lightList) const {
	lightList.clear();
	lightList.push_front(anchor);
}
