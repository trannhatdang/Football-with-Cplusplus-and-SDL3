#ifndef DG_VECTOR_H_
#define DG_VECTOR_H_

#include <iostream>
#include <algorithm>

struct Vector2;
struct Vector3;
struct Vector3f;

typedef struct Vector2
{
	int x;
	int y;
} Vector2;

typedef struct Vector3
{
	Vector3(int x = 0, int y = 0, int z = 0);
	int x;
	int y;
	int z;
	int sqrMagnitude() const;
	Vector3 operator+(const Vector3& other);
	void operator+=(const Vector3f& other);
	void operator+=(const Vector3& other);
} Vector3;

typedef struct Vector3f
{
	float x;
	float y;
	float z;
	float sqrMagnitude() const;
	float magnitude() const;
	Vector3f operator*(int multipler) const;
	Vector3f operator*(float multipler) const;
	Vector3f operator/(int multipler) const;
	Vector3f operator+(const Vector3f& other);
	Vector3f operator-(const Vector3f& other);
	Vector3f operator/(const Vector3f& other) const;
	Vector3f operator*(const Vector3f& other);
	void operator+=(const Vector3f& other);
	void operator-=(const Vector3f& other);
	void operator*=(float multipler);

	operator Vector3 () const;
} Vector3f;
std::ostream& operator<<(std::ostream& out, const Vector3& rhs);
std::ostream& operator<<(std::ostream& out, const Vector3f& rhs);
bool operator==(const Vector3f& lhs, const Vector3f& rhs);
Vector3f operator*(int lhs, const Vector3f& rhs);
Vector3f operator*(float lhs, const Vector3f& rhs);

Vector3 Vector3_One();
Vector3f Vector3f_Zero();
Vector3f Vector3f_GetUnitVector(const Vector3f& vec);
Vector3f Vector3f_Sqrt(const Vector3f& vec);
Vector3f Vector3f_GetAbs(const Vector3f& vec);
Vector3f Vector3f_Clamp(const Vector3f& vec, const Vector3f& min, const Vector3f& max);
Vector3f GetMinusVector3f(const Vector3f& vec);
Vector3f GetVector3fSign(const Vector3f& vec);

#endif
