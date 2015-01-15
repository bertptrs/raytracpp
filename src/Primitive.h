#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "common.h"
#include <list>
#include <forward_list>
#include "Material.h"
#include <memory>

using namespace std;

class Material;

typedef enum {
	HIT,
	MISS,
	INSIDE
} hitresult_t;

class Primitive {
	protected:
		shared_ptr<Material> material;
		virtual hitresult_t intersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal) = 0;
	public:
		virtual ~Primitive() {};
		virtual color_t colorAt(const vector3_t& pos);
		
		hitresult_t doIntersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal);

		void setMaterial(shared_ptr<Material> material);
		shared_ptr<const Material> getMaterial();
		virtual void getLightPoints(std::forward_list<const vector3_t*>& lightList) const = 0;

};

// Primitive list
typedef std::list<shared_ptr<Primitive>> plist_t;

#endif
