#include "common.h"
#include <cmath>

using namespace std;

vector3::vector3(double x, double y, double z) {
	coords.x = x;
	coords.y = y;
	coords.z = z;
}

void vector3::set(double x, double y, double z) {
	coords.x = x;
	coords.y = y;
	coords.z = z;
}

void vector3::normalize() {
	double l = 1 / length();
	for(int i = 0; i < DIMENSION; i++) {
		cells[i] *= l;
	}
}

double vector3::length() const {
	return sqrt(squareLength());
}

double vector3::squareLength() const {
	return dot(*this);
}

double vector3::dot(const vector3& other) const {
	double r = 0;
	for(int i = 0; i < DIMENSION; i++)
		r += cells[i] * other.cells[i];
	return r;
}

vector3 vector3::cross(const vector3& b) const {
	return vector3( coords.y * b.coords.z - coords.z * b.coords.y, coords.z * b.coords.x - coords.x * b.coords.z, coords.x * b.coords.y - coords.y * b.coords.x );
}

void vector3::operator += (const vector3& a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] += a.cells[i];
}

void vector3::operator += (vector3 const * const a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] += a->cells[i];
}

void vector3::operator -= (const vector3& a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] -= a.cells[i];
}

void vector3::operator -= (vector3 const * const a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] -= a->cells[i];
}
void vector3::operator *= (const vector3& a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] *= a.cells[i];
}

void vector3::operator *= (vector3 const * const a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] *= a->cells[i];
}

void vector3::operator *= (double factor) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] *= factor;
}

ostream& operator << (ostream& out, const vector3& v) {
	out << "( " << v.cells[0];
	for(int i = 1; i < v.DIMENSION; i++)
		out << ", " << v.cells[i];
	out << " )";
	return out;
}

vector3 operator + (const vector3& a, const vector3& b) {
	vector3 v(a.coords.x + b.coords.x,
			a.coords.y + b.coords.y,
			a.coords.z + b.coords.z);
	return v;
}

vector3 operator - (const vector3& a, const vector3& b) {
	vector3 v(a.coords.x - b.coords.x,
			a.coords.y - b.coords.y,
			a.coords.z - b.coords.z);
	return v;
}

vector3 operator * (const vector3& a, const vector3& b) {
	vector3 c = a;
	c *= b;
	return c;
}

vector3 operator * (double factor, const vector3& original) {
	vector3 b = original;
	b *= factor;
	return b;
}
