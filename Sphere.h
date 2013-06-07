#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

class Sphere : public Primitive {
	private:
		const vector3 pos;
		const double radius;
		double intersect(const ray_t& ray, vector3& hit, vector3& normal);

	public:
		Sphere(const vector3& pos, double radius);
};

#endif
