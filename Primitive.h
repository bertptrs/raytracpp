#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "common.h"

class Primitive {
	protected:
		virtual double intersect(const ray_t& ray, vector3& hit, vector3& normal) = 0;
	public:
		virtual ~Primitive() {};
		
		double doIntersect(const ray_t& ray, vector3& hit, vector3& normal);
};

#endif
