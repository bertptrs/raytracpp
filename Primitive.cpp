#include "Primitive.h"

hitresult_t Primitive::doIntersect(const ray_t& ray, double& distance, vector3& hit, vector3& normal) {
	// Future compatible, possible translation of objects.
	return this->intersect(ray, distance, hit, normal);
}
