#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "common.h"

typedef enum {
	HIT,
	MISS,
	INSIDE
} hitresult_t;

class Primitive {
	protected:
		virtual hitresult_t intersect(const ray_t& ray, double& distance, vector3& hit, vector3& normal) = 0;
	public:
		virtual ~Primitive() {};
		
		hitresult_t doIntersect(const ray_t& ray, double& distance, vector3& hit, vector3& normal);
};

#endif