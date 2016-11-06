#pragma once

struct vec3
{
	float x, y, z;

	vec3();
	vec3(float x, float y, float z);
	vec3(const vec3& other);
	vec3(vec3&& other) noexcept;
	vec3& operator=(const vec3& other);
	vec3& operator=(vec3&& other) noexcept;
	~vec3();

	vec3& normalize();
	void set(vec3 &o);
	float length() const;
	float length_sq() const;

	vec3 operator+(const vec3 &o) const;
	vec3 operator-(const vec3 &o) const;
	vec3 operator/(float d) const;
	vec3 operator*(const vec3 &o) const;
	vec3 operator*(float d) const;
	bool operator==(const vec3 &o) const;

	static float dot(const vec3 &a, const vec3 &b);
	static vec3 cross(const vec3 &a, const vec3 &b);

	void rot_z(float theta);
	void rot_y(float theta);
	void rot_x(float theta);
	float get_ang_z() const;
	float get_ang_y() const;
	float get_ang_x() const;
	vec3 get_rot_vec() const;
	void rotate_axis(vec3 &axis, float angle);

};

