#ifndef COMMON_H
#define COMMON_H
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

		vector3_t operator - ();
};

vector3_t operator + (const vector3_t& a, const vector3_t& b);
vector3_t operator - (const vector3_t& a, const vector3_t& b);
vector3_t operator * (const vector3_t& a, const vector3_t& b);
vector3_t operator * (double factor, const vector3_t& original);

std::ostream& operator << (std::ostream& out, const vector3_t& v);


typedef vector3_t color_t;

typedef struct {
	vector3_t origin;
	vector3_t direction;
} ray_t;



#endif
