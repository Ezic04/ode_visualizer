#include "graphics/Vec3.hpp"

#include <cmath>

using namespace graphics;

Vec3 Vec3::operator+=(const Vec3& vector) {
	*this = *this + vector;
	return *this;
}

Vec3 Vec3::operator-=(const Vec3& vector) {
	*this = *this - vector;
	return *this;
}

Vec3 Vec3::operator*=(const float& scalar) {
	*this = *this * scalar;
	return *this;
}

Vec3 Vec3::operator/=(const float& scalar) {
	*this = *this / scalar;
	return *this;
}

float Vec3::lengthSquared(const Vec3& vector) {
	return (
		vector.x() * vector.x() +
		vector.y() * vector.y() +
		vector.z() * vector.z()
	);
}

float Vec3::length(const Vec3& vector) {
	return sqrtf(lengthSquared(vector));
}

Vec3 Vec3::normalize(const Vec3& vector) {
	return vector / length(vector);
}

float Vec3::dotProduct(const Vec3& v1, const Vec3& v2) {
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

Vec3 operator+(const Vec3& v1, const Vec3& v2) { return Vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z()); }
Vec3 operator-(const Vec3& v1, const Vec3& v2) { return Vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z()); }
Vec3 operator*(const Vec3& v, const float& scalar) { return Vec3(v.x() * scalar, v.y() * scalar, v.z() * scalar); }
Vec3 operator/(const Vec3& v, const float& scalar) { return Vec3(v.x() / scalar, v.y() / scalar, v.z() / scalar); }
bool operator==(const Vec3& v1, const Vec3& v2) { return (fabsf(v1.x() - v1.x()) < 0.0001 && fabsf(v1.y() - v2.y()) < 0.0001 && fabsf(v1.z() - v2.z()) < 0.0001); }
bool operator!=(const Vec3& v1, const Vec3& v2) { return (fabsf(v1.x() - v1.x()) > 0.0001 || fabsf(v1.y() - v2.y()) > 0.0001 || fabsf(v1.z() - v2.z()) > 0.0001); }

