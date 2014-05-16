#ifndef MATERIAL_H
#define MATERIAL_H
#include "common.h"
#include "Primitive.h"

class Primitive;

// 
// Basic class for material.
//
// This material supports plain color, and haz properties such as reflection
// rate and such.
//
//
class Material {
	protected:
		color_t color;
		bool light;
		bool render;
		
	public:
		union {
			double luminance;
			struct {
				double diffusion;
				double reflection;
				double refraction;
			} data;
		};
		// Constructor for light-materials
		Material(const color_t& color, const double& intensity);

		// Constructor for other materials
		Material(const color_t& color, const double& diffusion, const double& reflection, const double& refraction);
		virtual color_t colorAt(Primitive const * const parent, const vector3_t& pos) const;

		virtual bool isLight();
		virtual bool doesDiffuse();
		virtual bool doesReflect();
		virtual bool doesRefract();
};

#endif
