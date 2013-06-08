#include "Sphere.h"
#include <cmath>

using namespace std;

Sphere::Sphere(const vector3& pos, double radius) : pos(pos), radius(radius) 
{}

hitresult_t Sphere::intersect(const ray_t& ray, double& distance, vector3& hit, vector3& normal) {
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
