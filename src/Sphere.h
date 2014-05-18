#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

using namespace std;

class Sphere : public Primitive {
	private:
		const vector3_t pos;
		const double radius;
		hitresult_t intersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal);

	public:
		Sphere(const vector3_t& pos, double radius);
		void getLightPoints(forward_list<const vector3_t*>& lightList) const;
};

#endif