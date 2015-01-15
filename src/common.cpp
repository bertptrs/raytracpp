#include "common.h"
#include <cmath>

using namespace std;

vector3_t::vector3_t(double x, double y, double z) {
	coords.x = x;
	coords.y = y;
	coords.z = z;
}

void vector3_t::set(double x, double y, double z) {
	coords.x = x;
	coords.y = y;
	coords.z = z;
}

void vector3_t::normalize() {
	double l = 1 / length();
	for(int i = 0; i < DIMENSION; i++) {
		cells[i] *= l;
	}
}

double vector3_t::length() const {
	return sqrt(squareLength());
}

double vector3_t::squareLength() const {
	return dot(*this);
}

double vector3_t::dot(const vector3_t& other) const {
	double r = 0;
	for(int i = 0; i < DIMENSION; i++)
		r += cells[i] * other.cells[i];
	return r;
}

vector3_t vector3_t::cross(const vector3_t& b) const {
	return vector3_t( coords.y * b.coords.z - coords.z * b.coords.y, coords.z * b.coords.x - coords.x * b.coords.z, coords.x * b.coords.y - coords.y * b.coords.x );
}

vector3_t vector3_t::random(double len) {
	vector3_t v(rand() / 2 - RAND_MAX, 
			rand() / 2 - RAND_MAX,
			rand() / 2 - RAND_MAX);
	return v * (len / v.length());
}

void vector3_t::operator += (const vector3_t& a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] += a.cells[i];
}

void vector3_t::operator += (vector3_t const * const a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] += a->cells[i];
}

void vector3_t::operator -= (const vector3_t& a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] -= a.cells[i];
}

void vector3_t::operator -= (vector3_t const * const a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] -= a->cells[i];
}
void vector3_t::operator *= (const vector3_t& a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] *= a.cells[i];
}

void vector3_t::operator *= (vector3_t const * const a) {
	for(int i = 0; i < DIMENSION; i++)
		cells[i] *= a->cells[i];
}

void vector3_t::operator *= (double factor) {
	coords.x *= factor;
	coords.y *= factor;
	coords.z *= factor;
}

vector3_t vector3_t::operator - () const {
	return vector3_t(-coords.x, -coords.y, -coords.z);
}

ostream& operator << (ostream& out, const vector3_t& v) {
	out << "( " << v.cells[0];
	for(int i = 1; i < v.DIMENSION; i++)
		out << ", " << v.cells[i];
	out << " )";
	return out;
}

vector3_t operator + (const vector3_t& a, const vector3_t& b) {
	vector3_t v(a.coords.x + b.coords.x,
			a.coords.y + b.coords.y,
			a.coords.z + b.coords.z);
	return v;
}

vector3_t operator - (const vector3_t& a, const vector3_t& b) {
	vector3_t v(a.coords.x - b.coords.x,
			a.coords.y - b.coords.y,
			a.coords.z - b.coords.z);
	return v;
}

vector3_t operator * (const vector3_t& a, const vector3_t& b) {
	vector3_t c = a;
	c *= b;
	return c;
}

vector3_t operator * (double factor, const vector3_t& original) {
	vector3_t b = original;
	b *= factor;
	return b;
}

Ray::Ray(const vector3_t& origin) : origin(origin) {}
Ray::Ray(const vector3_t& origin, const vector3_t& direction) : origin(origin), direction(direction) {}
