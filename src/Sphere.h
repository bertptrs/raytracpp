#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"
#include <vector>

using namespace std;

class Sphere : public Primitive {
	private:
		static const int NUM_LIGHTPOINTS;
		const vector3_t pos;
		const double radius;
		vector<vector3_t> lightPoints;

		hitresult_t intersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal);
		void generateLightPoints();
		vector3_t randomPoint();

	public:
		Sphere(const vector3_t& pos, double radius);
		void getLightPoints(forward_list<vector3_t>& lightList) const;
};

#endif
