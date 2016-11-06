#include "vec3.h"
#include <cmath>


vec3::vec3()
{
	x = y = z = 0;
}

vec3::vec3(const vec3& other) : x(other.x), y(other.y), z(other.z)
{
}

vec3::vec3(vec3&& other) noexcept
	: x(other.x),
	y(other.y),
	z(other.z)
{
}

vec3& vec3::operator=(const vec3& other)
{
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

vec3& vec3::operator=(vec3&& other) noexcept
{
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

vec3::vec3(float x, float y, float z) : x(x), y(y), z(z)
{
}

vec3::~vec3()
{
}

void vec3::normalize()
{
	float len = length();
	x /= len;
	y /= len;
	z /= len;
}

void vec3::set(vec3& o)
{
	x = o.x;
	y = o.y;
	z = o.z;
}

float vec3::length() const
{
	return sqrt(length_sq());
}

float vec3::length_sq() const
{
	return x * x + y * y + z * z;
}

vec3 vec3::operator+(const vec3& o) const
{
	return vec3(x + o.x, y + o.y, z + o.z);
}

vec3 vec3::operator-(const vec3& o) const
{
	return vec3(x - o.x, y - o.y, z - o.z);
}

vec3 vec3::operator/(float d) const
{
	return vec3(x / d, y / d, z / d);
}

vec3 vec3::operator*(const vec3& o) const
{
	return vec3(x * o.x, y * o.y, z * o.z);
}

vec3 vec3::operator*(float d) const
{
	return vec3(x * d, y * d, z * d);
}

bool vec3::operator==(const vec3& o) const
{
	return x == o.x && y == o.y && z == o.z;
}

float vec3::dot(const vec3& a, const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3::cross(const vec3& a, const vec3& b)
{
	return vec3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y);
}

void vec3::rot_z(float theta)
{
	x = x * cos(theta) - y * sin(theta);
	y = x * sin(theta) + y * cos(theta);
}

void vec3::rot_y(float theta)
{
	x = x * cos(theta) + z * sin(theta);
	z = -x * sin(theta) + z * cos(theta);
}

void vec3::rot_x(float theta)
{
	y = y * cos(theta) - z * sin(theta);
	z = y * sin(theta) + z * cos(theta);
}

float vec3::get_ang_z() const
{
	float rotx = get_ang_x();
	float roty = get_ang_y();
	return atan2(cos(rotx), sin(rotx) * sin(roty));
}

float vec3::get_ang_y() const
{
	return atan2(x * cos(get_ang_x()), z);
}

float vec3::get_ang_x() const
{
	return atan2(y, z);
}

vec3 vec3::get_rot_vec() const
{
	return vec3(get_ang_x(), get_ang_y(), get_ang_z());
}

void vec3::rotate_axis(vec3& axis, float angle)
{
	float norm = axis.length();
	float halfAngle = -0.5f * angle;
	float coeff = sin(halfAngle) / norm;

	float q0 = cos(halfAngle);
	float q1 = coeff * axis.x;
	float q2 = coeff * axis.y;
	float q3 = coeff * axis.z;

	float s = q1 * x + q2 * y + q3 * z;
	x = 2 * (q0 * (x * q0 - (q2 * z - q3 * y)) + s * q1) - x;
	y = 2 * (q0 * (y * q0 - (q3 * x - q1 * z)) + s * q2) - y;
	z = 2 * (q0 * (z * q0 - (q1 * y - q2 * x)) + s * q3) - z;
}

