#include "engine/dg_vector.h"

Vector3::Vector3(int x, int y, int z) : x(x), y(y), z(z)
{

}

int Vector3::sqrMagnitude() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

int Vector3::magnitude() const
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::operator+(const Vector3& other)
{
	Vector3 ans = *this;

	ans.x += other.x;
	ans.y += other.y;
	ans.z += other.z;

	return ans;
}

Vector3 Vector3::operator-(const Vector3& other)
{
	Vector3 ans = *this;

	ans.x -= other.x;
	ans.y -= other.y;
	ans.z -= other.z;

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
	int newX = (other.x > 0 ? std::floor(other.x) : std::ceil(other.x));
	int newY = (other.y > 0 ? std::floor(other.y) : std::ceil(other.y));
	int newZ = (other.z > 0 ? std::floor(other.z) : std::ceil(other.z));

	this->x = this->x + newX;
	this->y = this->y + newY;
	this->z = this->z + newZ;
}

Vector3::operator Vector3f () const
{
	return { (float)x, (float)y, (float)z};

}

float Vector3f::sqrMagnitude() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vector3f::magnitude() const
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3f Vector3f::operator*(int multiplier) const
{
	Vector3f ans = *this;

	ans.x *= multiplier;
	ans.y *= multiplier;
	ans.z *= multiplier;

	return ans;
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
	return {this->x > 0 ? (int)floor(this->x) : (int)ceil(this->x),
		this->y > 0 ? (int)floor(this->y) : (int)ceil(this->y),
		this->z > 0 ? (int)floor(this->z) : (int)ceil(this->z)};
}

bool operator==(const Vector3f& lhs, const Vector3f& rhs)
{
	return std::abs(rhs.x - lhs.x) < 0.01f && std::abs(rhs.y - lhs.y) < 0.01f && std::abs(rhs.z - lhs.z) < 0.01f;
}

std::ostream& operator<<(std::ostream& out, const Vector3& rhs)
{
	return out << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}

std::ostream& operator<<(std::ostream& out, const Vector3f& rhs)
{
	return out << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}

Vector3f operator*(int lhs, const Vector3f& rhs)
{
	return rhs * lhs;
}

Vector3f operator*(float lhs, const Vector3f& rhs)
{
	return rhs * lhs;
}

Vector3 Vector3_Zero()
{
	return {0, 0, 0};
}

Vector3 Vector3_One()
{
	return {1, 1, 1};
}

int Vector3_Dot(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3f Vector3f_Zero()
{
	return {0, 0, 0};
}

Vector3f Vector3f_Left()
{
	return {-1, 0, 0};
}

Vector3f Vector3f_Right()
{
	return {1, 0, 0};
}

Vector3f Vector3f_Up()
{
	return {0, -1, 0};
}

Vector3f Vector3f_Down()
{
	return {0, 1, 0};
}

Vector3f Vector3f_GetUnitVector(const Vector3f& vec)
{
	float mag = vec.magnitude();
	float x = vec.x / mag;
	float y = vec.y / mag;
	float z = vec.z / mag;
	return { x, y, z };
}

Vector3f Vector3f_Sqrt(const Vector3f& vec)
{
	float x = std::max(vec.x, 0.0f);
	float y = std::max(vec.y, 0.0f);
	float z = std::max(vec.z, 0.0f);

	return {sqrt(x), sqrt(y), sqrt(z)};
}

Vector3f Vector3f_GetAbs(const Vector3f& vec)
{
	return {std::abs(vec.x), std::abs(vec.y), std::abs(vec.z)};
}

Vector3f Vector3f_Clamp(const Vector3f& vec, const Vector3f& min, const Vector3f& max)
{
	return {
		std::max(std::min(vec.x, max.x), min.x),
		std::max(std::min(vec.y, max.y), min.y),
		std::max(std::min(vec.z, max.z), min.z)
	};
}

Vector3f Vector3f_GetPrimaryDirection(const Vector3f& vec)
{
	if(vec == Vector3_Zero())
	{
		return Vector3_Zero();
	}

	if(std::abs(vec.x) > std::abs(vec.y))
	{
		if(vec.x > 0)
		{
			return Vector3f_Right();
		}
		else
		{
			return Vector3f_Left();
		}
	}
	else
	{
		if(vec.y > 0)
		{
			return Vector3f_Down();
		}
		else
		{
			return Vector3f_Up();
		}
	}
}

float Vector3f_Dot(const Vector3f& lhs, const Vector3f& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
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
