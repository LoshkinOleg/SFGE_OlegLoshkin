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

#include <p2vector.h>
#include <cmath>

p2Vec2::p2Vec2()
{
	x = 0;
	y = 0;
}

p2Vec2::p2Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

p2Vec2 p2Vec2::operator+(p2Vec2 v)
{
	return p2Vec2(x+v.x, y+v.y);
}

p2Vec2 p2Vec2::operator+=(p2Vec2 v)
{
	return *this+v;
}

p2Vec2 p2Vec2::operator-(p2Vec2 v)
{
	return p2Vec2(x-v.x, y-v.y);
}

p2Vec2 p2Vec2::operator-=(p2Vec2 v)
{
	return *this-v;
}

p2Vec2 p2Vec2::operator*=(float f)
{
	return (*this) * f;
}

p2Vec2 p2Vec2::operator/(float f)
{
	return p2Vec2(x/f, y/f);
}

p2Vec2 p2Vec2::operator*(float f)
{
	return p2Vec2(x*f, y*f);
}

float p2Vec2::Dot(p2Vec2 v1, p2Vec2 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}
p2Vec3 p2Vec2::Cross(p2Vec2 v1, p2Vec2 v2)
{
	return p2Vec3(0,0, (v1.x*v2.y) - (v1.y*v2.x));
}
float p2Vec2::GetMagnitude() const
{
	return _CMATH_::sqrt((x*x) + (y*y));
}

p2Vec2 p2Vec2::Normalized()
{
	return p2Vec2::StaticNormalized(*this);
}

void p2Vec2::NormalizeSelf()
{
	const float magnitude = GetMagnitude();
	x = 1 / magnitude;
	y = 1 / magnitude;
}

p2Vec2 p2Vec2::Rotate(float angle) const
{
	return p2Vec2();
}

p2Vec2 p2Vec2::Lerp(const p2Vec2& v1, const p2Vec2& v2, float t)
{
	p2Vec2 v = v1;
	p2Vec2 u = v2;
	return (v * (1 - t)) + (u * t);
}

float p2Vec2::AngleBetween(const p2Vec2& v1, const p2Vec2& v2)
{
	return _CMATH_::acos( (p2Vec2::Dot(v1,v2)) / (v1.GetMagnitude() * v2.GetMagnitude()) );
}

p2Vec2 p2Vec2::FindNormal(const p2Vec2& v1)
{
	return p2Vec2(-v1.y,v1.x);
}

p2Vec2 p2Vec2::StaticNormalized(const p2Vec2 & v1)
{
	const float magnitude = v1.GetMagnitude();
	return p2Vec2(1 / magnitude, 1 / magnitude);
}

p2Vec3 p2Vec2::to3()
{
	return p2Vec3(x, y, 0.0f);
}

p2Vec3::p2Vec3()
{
}

p2Vec3::p2Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

p2Vec3 p2Vec3::operator+(p2Vec3 v)
{
	return p2Vec3(x + v.x, y + v.y, z + v.z);
}

p2Vec3 p2Vec3::operator+=(p2Vec3 v)
{
	return *this + v;
}

p2Vec3 p2Vec3::operator-(p2Vec3 v)
{
	return p2Vec3(x - v.x, y - v.y, z- v.z);
}

p2Vec3 p2Vec3::operator-=(p2Vec3 v)
{
	return *this - v;
}

p2Vec3 p2Vec3::operator*=(float f)
{
	return (*this) * f;
}

p2Vec3 p2Vec3::operator/(float f)
{
	return p2Vec3(x / f, y / f, z/f);
}

p2Vec3 p2Vec3::operator*(float f)
{
	return p2Vec3(x*f, y*f, z*f);
}

float p2Vec3::Dot(p2Vec3 v1, p2Vec3 v2)
{
	//TODO
	return 0.0f;
}

p2Vec3 p2Vec3::Cross(p2Vec3 v1, p2Vec3 v2)
{
	//TODO
	return p2Vec3();
}

p2Vec3 p2Vec3::Rotate(float angle) const
{
	return p2Vec3();
}

p2Vec3 p2Vec3::Lerp(const p2Vec3& v1, const p2Vec3& v2, float t)
{
	return p2Vec3();
}

float p2Vec3::AngleBetween(const p2Vec3& v1, const p2Vec3& v2)
{
	return 0.0f;
}

float p2Vec3::GetMagnitude()
{
	return 0.0f;
}

p2Vec3 p2Vec3::Normalized()
{
	return p2Vec3();
}

void p2Vec3::NormalizeSelf()
{
}
