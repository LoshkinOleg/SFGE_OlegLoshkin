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

#include <cmath>
#include <p2vector.h>
#include <p2matrix.h>
#include <engine/globals.h>

p2Vec2::p2Vec2()
{
}

p2Vec2::p2Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

p2Vec2 p2Vec2::operator+(const p2Vec2 v)const
{
	return p2Vec2(x+v.x, y+v.y);
}

void p2Vec2::operator+=(const p2Vec2 v)
{
	*this = *this+v;
}

p2Vec2 p2Vec2::operator-(const p2Vec2 v)const
{
	return p2Vec2(x-v.x, y-v.y);
}

void p2Vec2::operator-=(const p2Vec2 v)
{
	*this = *this-v;
}

void p2Vec2::operator*=(const float f)
{
	*this = (*this) * f;
}

void p2Vec2::operator/=(const float f) 
{
	*this = (*this) / f;
}

p2Vec2 p2Vec2::operator/(const float f)const
{
	return p2Vec2(x/f, y/f);
}

p2Vec2 p2Vec2::operator*(const float f)const
{
	return p2Vec2(x*f, y*f);
}

float p2Vec2::Dot(const p2Vec2 v1, const p2Vec2 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}
p2Vec3 p2Vec2::Cross(const p2Vec2 v1, const p2Vec2 v2)
{
	return p2Vec3(0,0, (v1.x * v2.y) - (v1.y * v2.x) );
}
float p2Vec2::GetMagnitude()const
{
	return _CMATH_::sqrt((x*x + y*y));
}

p2Vec2 p2Vec2::Normalized()const
{
	return p2Vec2(*this / GetMagnitude());
}

void p2Vec2::NormalizeSelf()
{
	*this = *this / GetMagnitude();
}

p2Vec2 p2Vec2::Rotate(const float angle) const
{
	return p2Mat22(	p2Vec2(_CMATH_::cos(angle*(PI / 180.0f)), -_CMATH_::sin(angle*(PI / 180.0f))),
					p2Vec2(_CMATH_::sin(angle*(PI / 180.0f)), _CMATH_::cos(angle*(PI / 180.0f))))		* (*this);
}

p2Vec2 p2Vec2::Lerp(const p2Vec2& v1, const p2Vec2& v2, const float t)
{
	return p2Vec2( v2 * (1 - t) + v1 * t );
}

float p2Vec2::AngleBetween(const p2Vec2& v1, const p2Vec2& v2)
{
	return (_CMATH_::acos(p2Vec2::Dot(v1,v2) / (v1.GetMagnitude() * v2.GetMagnitude()))) * (180.0f/ PI);
}

p2Vec3 p2Vec2::to3()const
{
	return p2Vec3(x, y, 0.0f);
}

std::string p2Vec2::ToString() const
{
	std::string returnValue;
	returnValue = std::string("(");
	returnValue.append(std::to_string(x));
	returnValue.push_back(';');
	returnValue.append(std::to_string(y));
	returnValue.push_back(')');
	return returnValue;
}

sfge::Vec2f p2Vec2::ToGraphicSpace() const
{
	return sfge::Vec2f(x * 100.0f,y * 100.0f);
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
	return (v1.x * v2.x) + (v1.y + v2.y) + (v1.z + v2.z);
}

p2Vec3 p2Vec3::Cross(p2Vec3 v1, p2Vec3 v2)
{
	return p2Vec3(	(v1.y * v2.z) - (v1.z * v2.y),
					(v1.z * v2.x) - (v1.x * v2.z),
					(v1.x * v2.y) - (v1.y * v2.x));
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
