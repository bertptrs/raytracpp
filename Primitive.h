#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "common.h"
#include <list>
#include "Material.h"

class Material;

typedef enum {
	HIT,
	MISS,
	INSIDE
} hitresult_t;

class Primitive {
	protected:
		Material* material;
		virtual hitresult_t intersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal) = 0;
	public:
		virtual ~Primitive() {};
		virtual color_t colorAt(const vector3_t& pos);
		
		hitresult_t doIntersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal);

		void setMaterial(Material* m);
		Material* getMaterial();
};

typedef std::list<Primitive*> plist_t;

#endif
