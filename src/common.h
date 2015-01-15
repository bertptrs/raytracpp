#ifndef COMMON_H
#define COMMON_H
#define EPSILON 1e-10
#define DOT(v1, v2) (v1.coords.x * v2.coords.x + v1.coords.y * v2.coords.y + v1.coords.z * v2.coords.z)
#include <iostream>

class vector3_t {
	public:
		static const int DIMENSION = 3;
		union{
			struct { double x,y,z; } coords;
			struct { double r,g,b;} channels;
			double cells[3];
		};

		vector3_t(double x=0, double y=0, double z=0);

		static vector3_t random(double len = 1);

		void set(double x, double y, double z);
		void normalize();
		double length() const;
		double squareLength() const;
		double dot(const vector3_t& other) const;
		vector3_t cross(const vector3_t& other) const;

		void operator += (const vector3_t& other);
		void operator += (vector3_t const * const other);
		void operator -= (const vector3_t& other);
		void operator -= (vector3_t const * const other);

		void operator *= (const vector3_t& other);
		void operator *= (vector3_t const * const);
		void operator *= (double factor);

		vector3_t operator - () const;
};

vector3_t operator + (const vector3_t& a, const vector3_t& b);
vector3_t operator - (const vector3_t& a, const vector3_t& b);
vector3_t operator - (const vector3_t& a, vector3_t const * const);
vector3_t operator * (const vector3_t& a, const vector3_t& b);
vector3_t operator * (double factor, const vector3_t& original);

std::ostream& operator << (std::ostream& out, const vector3_t& v);


typedef vector3_t color_t;

class Ray {
	public:
		vector3_t origin;
		vector3_t direction;

		Ray() = default;
		Ray(const vector3_t& origin);
		Ray(const vector3_t& origin, const vector3_t& direction);
};

typedef Ray ray_t;



#endif
