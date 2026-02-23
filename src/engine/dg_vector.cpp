#include "engine/dg_vector.h"

const static Vector3f Vector3f_zero = {0, 0, 0};
Vector3 Vector3::operator+(const Vector3& other)
{
	Vector3 ans = *this;

	ans.x += other.x;
	ans.y += other.y;
	ans.z += other.z;

	return ans;
}

void Vector3::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

void Vector3::operator+=(const Vector3f& other)
{
	this->x = (int)std::floor(this->x + other.x);
	this->y = (int)std::floor(this->y + other.y);
	this->z = (int)std::floor(this->z + other.z);
}

float Vector3f::sqrMagnitude() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vector3f::magnitude() const
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3f Vector3f::operator*(float multiplier) const
{
	Vector3f ans = *this;

	ans.x *= multiplier;
	ans.y *= multiplier;
	ans.z *= multiplier;

	return ans;
}

Vector3f Vector3f::operator/(int multiplier) const
{
	Vector3f ans = *this;

	ans.x /= multiplier;
	ans.y /= multiplier;
	ans.z /= multiplier;

	return ans;
}

Vector3f Vector3f::operator+(const Vector3f& other)
{
	Vector3f ans = *this;

	ans.x += other.x;
	ans.y += other.y;
	ans.z += other.z;

	return ans;
}

Vector3f Vector3f::operator-(const Vector3f& other)
{
	Vector3f ans = *this;

	ans.x -= other.x;
	ans.y -= other.y;
	ans.z -= other.z;

	return ans;
}

Vector3f Vector3f::operator*(const Vector3f& other)
{
	Vector3f ans = *this;

	ans.x *= other.x;
	ans.y *= other.y;
	ans.z *= other.z;

	return ans;
}

Vector3f Vector3f::operator/(const Vector3f& other) const
{
	Vector3f ans = *this;

	ans.x /= other.x;
	ans.y /= other.y;
	ans.z /= other.z;

	return ans;
}

void Vector3f::operator+=(const Vector3f& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

void Vector3f::operator-=(const Vector3f& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
}

void Vector3f::operator*=(float multipler)
{
	this->x *= multipler;
	this->y *= multipler;
	this->z *= multipler;
}

Vector3f::operator Vector3 () const
{
	return {this->x > 0 ? (int)ceil(this->x) : (int)floor(this->x),
		this->y > 0 ? (int)ceil(this->y) : (int)floor(this->y),
		this->z > 0 ? (int)ceil(this->z) : (int)floor(this->z)};
}

std::ostream& operator<<(std::ostream& out, const Vector3& rhs)
{
	return out << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}

std::ostream& operator<<(std::ostream& out, const Vector3f& rhs)
{
	return out << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}

Vector3 GetVector3One()
{
	return {1, 1, 1};
}

Vector3f GetVector3fZero()
{
	return Vector3f_zero;
}

Vector3f GetMinusVector3f(const Vector3f& vec)
{
	return Vector3f{-vec.x, -vec.y, -vec.z};
}

Vector3f GetVector3fSign(const Vector3f& vec)
{
	return { (vec.x >= 0 ? 1.0f : -1.0f),
		(vec.y >= 0 ? 1.0f : -1.0f),
		(vec.z >= 0 ? 1.0f : -1.0f)};
}
