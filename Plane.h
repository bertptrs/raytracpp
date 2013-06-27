#ifndef PLANE_H
#define PLANE_H

#include "Primitive.h"

using namespace std;

class Plane : public Primitive {
	private:
		const vector3_t anchor;
		const vector3_t normal;
		hitresult_t intersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal);

	public:
		Plane(const vector3_t& anchor, const vector3_t& normal);
		void getLightPoints(forward_list<const vector3_t*>& lightList) const;
};

#endif
