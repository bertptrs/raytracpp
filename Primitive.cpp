#include "Primitive.h"

hitresult_t Primitive::doIntersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal) {
	// Future compatible, possible translation of objects.
	return this->intersect(ray, distance, hit, normal);
}
