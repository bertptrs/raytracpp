#include "Material.h"


Material::Material(const color_t& color, const double& intensity) :
	color(color), light(true), render(true), luminance(intensity)
{
}

// Constructor for other materials
Material::Material(const color_t& color, const double& diffusion, const double& reflection, const double& refraction) :
	color(color), light(false), render(true)
{
	data.diffusion = diffusion;
	data.reflection = reflection;
	data.refraction = refraction;
}

color_t Material::colorAt(Primitive const * const, const vector3_t&) const {
	return color;
}

bool Material::isLight() const {
	return light;
}

bool Material::doesDiffuse() const {
	return data.diffusion > 0 && !light;
}

bool Material::doesReflect() const {
	return data.reflection > 0 && !light;
}

bool Material::doesRefract() const {
	return data.refraction > 0 && !light;
}
