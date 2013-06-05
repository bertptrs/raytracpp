#ifndef COMMON_H
#define COMMON_H
#include <iostream>

class vector3 {
	public:
		static const int DIMENSION = 3;
		union{
			struct { double x,y,z; } coords;
			struct { double r,g,b;} channels;
			double cells[3];
		};

		vector3(double x=0, double y=0, double z=0);

		void set(double x, double y, double z);
		void normalize();
		double length() const;
		double squareLength() const;
		double dot(const vector3& other) const;
		vector3 cross(const vector3& other) const;

		void operator += (const vector3& other);
		void operator += (vector3 const * const other);
		void operator -= (const vector3& other);
		void operator -= (vector3 const * const other);

		void operator *= (const vector3& other);
		void operator *= (vector3 const * const);
		void operator *= (double factor);

		vector3 operator - ();
};

vector3 operator + (const vector3& a, const vector3& b);
vector3 operator - (const vector3& a, const vector3& b);
vector3 operator * (const vector3& a, const vector3& b);
vector3 operator * (double factor, const vector3& original);

std::ostream& operator << (std::ostream& out, const vector3& v);


typedef vector3 color;


#endif
