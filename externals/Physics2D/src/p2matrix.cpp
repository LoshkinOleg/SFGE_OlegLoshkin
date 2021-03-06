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

#include <p2matrix.h>

p2Mat22::p2Mat22()
{
}

p2Mat22::p2Mat22(p2Vec2 r1, p2Vec2 r2)
{
	rows[0] = r1;
	rows[1] = r2;
}

p2Mat22 p2Mat22::operator+(p2Mat22 m1)
{
	return p2Mat22();
}

p2Mat22 p2Mat22::operator-(p2Mat22 m1)
{
	return p2Mat22();
}

p2Mat22 p2Mat22::operator*(p2Mat22 m1)
{
	return p2Mat22();
}

p2Vec2 p2Mat22::operator*(p2Vec2 v)
{
	return p2Vec2( (rows[0].x * v.x) + ((rows[0]).y * v.y), (rows[1].x * v.x) + (rows[1].y * v.y) );
}

p2Mat22 p2Mat22::operator*(float f)
{
	return p2Mat22();
}

p2Mat22 p2Mat22::operator/(float f)
{
	return p2Mat22();
}

p2Mat22 p2Mat22::Invert()
{
	return p2Mat22();
}

float p2Mat22::GetDeterminant()
{
	return 0.0f;
}

p2Mat22 p2Mat22::ProjectSelfOnto(const p2Vec2 axis) const
{
	return p2Mat22{ rows[0].ProjectSelfOnto(axis), rows[1].ProjectSelfOnto(axis) };
}

std::string p2Mat22::To_String()
{
	std::string str = rows[0].ToString();
	str.append(rows[1].ToString());
	return str;
}

p2Mat33::p2Mat33()
{
}

p2Mat33::p2Mat33(p2Vec3 r1, p2Vec3 r2, p2Vec3 r3)
{
}

p2Mat33 p2Mat33::operator+(p2Mat33 m1)
{
	return p2Mat33();
}

p2Mat33 p2Mat33::operator-(p2Mat33 m1)
{
	return p2Mat33();
}

p2Mat33 p2Mat33::operator*(p2Mat33 m1)
{
	return p2Mat33();
}

p2Vec3 p2Mat33::operator*(p2Vec3)
{
	return p2Vec3();
}

p2Mat33 p2Mat33::operator*(float f)
{
	return p2Mat33();
}

p2Mat33 p2Mat33::operator/(float f)
{
	return p2Mat33();
}

p2Mat33 p2Mat33::Invert()
{
	return p2Mat33();
}

float p2Mat33::GetDeterminant()
{
	return 0.0f;
}
