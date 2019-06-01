/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef SFGE_P2VECTOR_H
#define SFGE_P2VECTOR_H

#include <string>
#include <engine/vector.h>
#include <p2physics.h>

struct p2Vec2
{
	// Constructors.
	p2Vec2();
	p2Vec2(float x, float y);

	// Overloads.
	p2Vec2 operator+(const p2Vec2 v)const;
	p2Vec2 operator-(const p2Vec2 v)const;
	p2Vec2 operator*(const float f)const;
	p2Vec2 operator/(const float f)const;
	void operator+=(const p2Vec2 v);
	void operator-=(const p2Vec2 v);
	void operator*=(const float f);
	void operator/=(const float f);
	bool operator==(const p2Vec2 other) const;
	bool operator!=(const p2Vec2 other) const;

	// Static members.
	static float Dot(p2Vec2 v1, p2Vec2 v2);
	static p2Vec3 Cross(p2Vec2 v1, p2Vec2 v2);
	static p2Vec2 Lerp(const p2Vec2& v1, const p2Vec2& v2, const float t);
	static float AngleBetween(const p2Vec2& v1, const p2Vec2& v2);

	// Public methods.
	float Magnitude()const;
	p2Vec2 Normalized()const;
	std::array<p2Vec2, 2> Normals();
	void NormalizeSelf();
	p2Vec2 Rotate(const float angle) const;
	p2Vec2 ProjectSelfOnto(const p2Vec2 axis) const;
	sfge::Vec2f ToGraphicSpace() const;

	// Debugging methods.
	std::string ToString() const;

	// Attributes.
	float x = 0.0f;
	float y = 0.0f;
};

struct p2Vec3
{
	p2Vec3();
	p2Vec3(float x, float y, float z);

	p2Vec3 operator+(p2Vec3 v);
	p2Vec3 operator+=(p2Vec3 v);
	p2Vec3 operator-(p2Vec3 v);
	p2Vec3 operator-=(p2Vec3 v);
	p2Vec3 operator*=(float f);
	p2Vec3 operator /(float f);
	p2Vec3 operator *(float f);

	static float Dot(p2Vec3 v1, p2Vec3 v2);
	static p2Vec3 Cross(p2Vec3 v1, p2Vec3 v2);
	static p2Vec3 Lerp(const p2Vec3& v1, const p2Vec3& v2, float t);
	static float AngleBetween(const p2Vec3& v1, const p2Vec3& v2);

	float Magnitude();
	p2Vec3 Normalized();
	void NormalizeSelf();
	p2Vec3 Rotate(float angle) const;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

#endif