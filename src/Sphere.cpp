#include "Sphere.h"
#include <cmath>
#include <cstdlib>
#include <limits>

using namespace std;

const int Sphere::NUM_LIGHTPOINTS = 64;

Sphere::Sphere(const vector3_t& pos, double radius) : pos(pos), radius(radius) 
{
	generateLightPoints();
}

void Sphere::generateLightPoints() {
	lightPoints.push_back(randomPoint());
	vector<vector3_t> candidates(NUM_LIGHTPOINTS);

	while (lightPoints.size() < NUM_LIGHTPOINTS) {
		double bestDist = numeric_limits<double>::infinity();
		double best = -1;

		for (int i = 0; i < NUM_LIGHTPOINTS; i++) {
			candidates[i] = randomPoint();
			double maxDist = 0;

			for (const auto& point : lightPoints) {
				maxDist = max(maxDist, (point - candidates[i]).squareLength());
			}

			if (maxDist > bestDist) {
				best = i;
				bestDist = maxDist;
			}
		}

		lightPoints.push_back(candidates[best]);
	}
}

vector3_t Sphere::randomPoint() {
	double phi = acos(rand() / double(RAND_MAX) - 0.5);
	double theta = rand() / double(RAND_MAX) * M_PI - M_PI / 2;

	double x = radius * sin(phi) * cos(theta);
	double y = radius * sin(phi) * sin(theta);
	double z = radius * cos(phi);
	vector3_t lightPos = pos + vector3_t(x, y, z);

	return lightPos;
}

hitresult_t Sphere::intersect(const ray_t& ray, double& distance, vector3_t& hit, vector3_t& normal) {
	hitresult_t hitresult;
	double a,b,c,d;
	a = ray.direction.squareLength();
	b = 2 * (ray.origin - pos).dot(ray.direction);
	c = (ray.origin - pos).squareLength() - radius * radius;

	d = b*b - 4 * a * c;

	if(d < 0)
		return MISS;

	d = sqrt(d);
	if(-b - d > 0) {
		distance = (-b - d ) / (2 * a);
		hitresult = HIT;
	} else if ( -b + d > 0 ) {
		distance = (-b + d ) / (2 * a);
		hitresult = INSIDE;
	} else {
		// Both hitpoints behind us.
		return MISS;
	}
	hit = ray.origin + distance * ray.direction;
	normal = hit - pos;

	return hitresult;
}

void Sphere::getLightPoints(forward_list<vector3_t>& lightList) const {
	lightList.clear();
	for (const auto& point : lightPoints) {
		lightList.push_front(point);
	}
}
