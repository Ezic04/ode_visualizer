#pragma once

namespace graphics {

struct Vec3 {

  Vec3(void) : x(0.0f), y(0.0f), z(0.0f) {}
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vec3(const Vec3 &v) : x(v.x), y(v.y), z(v.z) {}

  static Vec3 normalize(const Vec3 &v);
  static float length(const Vec3 &v);
  static float lengthSquared(const Vec3 &v);
  static float dotProduct(const Vec3 &v1, const Vec3 &v2);

  Vec3 operator+=(const Vec3 &v);
  Vec3 operator-=(const Vec3 &v);
  Vec3 operator*=(float s);
  Vec3 operator/=(float s);

  float x, y, z;
};

Vec3 operator+(const Vec3 &v1, const Vec3 &v2);
Vec3 operator-(const Vec3 &v1, const Vec3 &v2);
Vec3 operator*(const Vec3 &v, float s);
Vec3 operator/(const Vec3 &v, float s);
bool operator==(const Vec3 &v1, const Vec3 &v2);
bool operator!=(const Vec3 &v1, const Vec3 &v2);

} // namespace graphics
