#include "Raytracer.h"
#include <algorithm>
#include <cmath>

using namespace std;

const vector3_t Raytracer::UP = vector3_t(0,0,1);

Raytracer::Raytracer(shared_ptr<OutputBitmap> bm) :
	bitmap(bm), BACKGROUND(color_t()), depth(DEFAULT_DEPTH)
{
	camera.origin = vector3_t(0,0,0);
	camera.direction = vector3_t(1,0,0);
}

void Raytracer::addObject(Primitive* object) {
	scene.push_back(shared_ptr<Primitive>(object));
}

void Raytracer::addObject(shared_ptr<Primitive> object) {
	scene.push_back(object);
}

renderresult_t Raytracer::render() {
	int width = bitmap->getWidth(), height = bitmap->getHeight();
	initScreen();
	initLights();

	if(xDir.squareLength() == 0 || yDir.squareLength() == 0)
		return INVALID_CAMERA;

	int x,y;
	double sX, sY;
	for(x = 0; x < width; x++) {
		sX = (double) (x - (width / 2)) / width;
		for(y = 0; y < height; y++) {
			sY = (double) (y - (height / 2)) / height / scale;
			color_t pixel = getPixel(sX, sY);
			bitmap->setPixel(x, y, pixel);
		}
	}
	return OK;
}

void Raytracer::initLights() {
	for(auto p : scene) {
		if(p->getMaterial()->isLight())
			lights.push_back(p);
	}
}

void Raytracer::initScreen() {
	xDir = camera.direction.cross(UP);
	yDir = camera.direction.cross(xDir);
	scale = (double) bitmap->getWidth();
	scale /= bitmap->getHeight();
}

color_t Raytracer::getPixel(double sX, double sY) {
	ray_t ray = camera;
	ray.direction += sX * xDir;
	ray.direction += sY * yDir;
	ray.direction.normalize();

	color_t retColor;
	vector3_t hit, normal;

	trace(ray, hit, normal, retColor);

	return retColor;
}

shared_ptr<Primitive> Raytracer::getNearest(const ray_t& ray) const {
	shared_ptr<Primitive> nearest;
	double minD = INFINITY;
	double tmpD;
	vector3_t tmpHit, tmpNormal;
	hitresult_t res;
	for(auto current : scene) {
		res = current->doIntersect(ray, tmpD, tmpHit, tmpNormal);
		if(res == MISS || tmpD > minD) {
			// Miss or already hidden
			continue;
		} else {
			minD = tmpD;
			nearest = current;
		}
	}

	return nearest;
}

color_t Raytracer::getDiffusion(const vector3_t& pos, const vector3_t& normal, const color_t& color) {
	color_t diffuse;
	forward_list<vector3_t> lightPoints;
	for(auto light : lights) {
		double strength = 0;
		int points = 0;
		light->getLightPoints(lightPoints);
		for(vector3_t lightOrigin : lightPoints) {
			points++;
			ray_t shadowRay;
			lightOrigin += vector3_t::random(0.2);
			shadowRay.origin = pos + EPSILON * normal;
			shadowRay.direction = -pos;
			shadowRay.direction += lightOrigin;
			shadowRay.direction.normalize();
			double lightAngle = normal.dot(shadowRay.direction);
			if(lightAngle > 0 && getNearest(shadowRay) == light) {
				strength += lightAngle / (pos - lightOrigin).squareLength();
			}
		}
		strength *= light->getMaterial()->luminance / points;
		diffuse += strength * color;
	}

	return diffuse;
}

color_t Raytracer::getReflection(const vector3_t& pos, const vector3_t& normal, const vector3_t& inAngle, const color_t& color) {
	depth--;
	ray_t reflectionRay;
	reflectionRay.origin = pos + EPSILON * normal;
	reflectionRay.direction = inAngle - 2 * inAngle.dot(normal) * normal;
	color_t reflectionColor;
	vector3_t hit, tmpNormal;
	trace(reflectionRay, hit, tmpNormal, reflectionColor);
	depth++;

	return reflectionColor * color;
}


shared_ptr<Primitive> Raytracer::trace(const ray_t& ray, vector3_t& hit, vector3_t& normal, color_t& color) {
	if(depth < 0) {
		color = BACKGROUND;
		return nullptr;
	}

	auto nearest = getNearest(ray);
	hitresult_t res;
	color_t ERROR(1,0,1);
	double hitDistance;

	color = color_t();

	if(nearest != nullptr) {
		res = nearest->doIntersect(ray, hitDistance, hit, normal);
		if(res == INSIDE)
			normal = -normal;
		normal.normalize();
		auto mat = nearest->getMaterial();
		if(mat == nullptr) {
			color = ERROR;
			return nearest;
		}
		if(mat->isLight()) {
			color = mat->colorAt(nearest.get(), hit);
		} else {
			color_t objectColor = mat->colorAt(nearest.get(), hit);

			if(mat->doesDiffuse())
				color += mat->data.diffusion * getDiffusion(hit, normal, objectColor);

			if(mat->doesReflect()) {
				color += mat->data.reflection * getReflection(hit, normal, ray.direction, objectColor);
			}
		}

	} else {
		color = BACKGROUND;
	}
	return nearest;
}

ray_t Raytracer::getCamera() {
	return camera;
}

color_t Raytracer::getRefraction(const vector3_t& pos, const vector3_t& normal, const vector3_t& inAngle, const color_t& color) {
	const double rindex = 1.33;
	double n = 1 / rindex;
	double cosI = -DOT(normal, inAngle);
	double cosT2 = 1 - n * n * (1 - cosI * cosI);
	color_t refractionColor;
	if(cosT2 > 0) {
		depth--;
		ray_t refractionRay(pos + EPSILON * normal, n * inAngle);
		refractionRay.direction += (n * cosI - sqrt(cosT2)) * normal;
		vector3_t hit, tmpNormal;
		trace(refractionRay, hit, tmpNormal, refractionColor);
		depth++;
	} else {
		refractionColor = BACKGROUND;
	}

	return refractionColor;
}
