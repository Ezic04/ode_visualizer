#pragma once

#include <iostream>

namespace graphics {

class Vec3 {
public:
	Vec3(void) : mX(0.0f), mY(0.0f), mZ(0.0f) {}
	Vec3(float x, float y, float z) : mX(x), mY(y), mZ(z) {}
	Vec3(const Vec3& v) : mX(v.mX), mY(v.mY), mZ(v.mZ) {}

	float x(void) const { return mX; }
	float y(void) const { return mY; }
	float z(void) const { return mZ; }

	Vec3 operator +=(const Vec3& vector);
	Vec3 operator -=(const Vec3& vector);
	Vec3 operator *=(const float& scalar);
	Vec3 operator /=(const float& scalar);

	friend std::ostream& operator<<(std::ostream& os, const Vec3& v) { return os << v.x() << " " << v.y() << " " << v.z() << "\n"; };

	static float lengthSquared(const Vec3& vector);
	static float length(const Vec3& vector);
	static Vec3 normalize(const Vec3& vector);

	static float dotProduct(const Vec3& v1, const Vec3& v2);

private:
	float mX, mY, mZ;
};

Vec3 operator+(const Vec3& v1, const Vec3& v2);
Vec3 operator-(const Vec3& v1, const Vec3& v2);
Vec3 operator*(const Vec3& v, const float& scalar);
Vec3 operator/(const Vec3& v, const float& scalar);
bool operator==(const Vec3& v1, const Vec3& v2);
bool operator!=(const Vec3& v1, const Vec3& v2);

}

