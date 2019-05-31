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

#include <array>
#include <p2aabb.h>

p2Vec2 p2AABB::GetCenter() const
{
	return (bottomLeft + topRight)/2.0f;
}

p2Vec2 p2AABB::GetExtends() const
{
	return p2Vec2(topRight.x - bottomLeft.x, bottomLeft.y - topRight.y) / 2.0f;
}

void p2AABB::SetCenter(const p2Vec2 center)
{
	p2Vec2 temp_bottomLeft = center + p2Vec2(- GetExtends().x, GetExtends().y);
	p2Vec2 temp_topRight = center + p2Vec2(GetExtends().x, - GetExtends().y);
	bottomLeft = temp_bottomLeft;
	topRight = temp_topRight;
}

float p2AABB::XMin() const
{
	return bottomLeft.x;
}

float p2AABB::XMax() const
{
	return topRight.x;
}

float p2AABB::YMin() const
{
	return topRight.y;
}

float p2AABB::YMax() const
{
	return bottomLeft.y;
}

std::array<p2Mat22, 4> p2AABB::Sides() const
{
	return {	p2Mat22(	p2Vec2(XMin(), YMin()),	p2Vec2(XMax(), YMin())),	// TopLeft to TopRight.
				p2Mat22(	p2Vec2(XMax(), YMin()),	p2Vec2(XMax(), YMax())),	// TopRight to BottomRight.
				p2Mat22(	p2Vec2(XMin(), YMax()),	p2Vec2(XMax(), YMax())),	// BottomLeft to BottomRight.
				p2Mat22(	p2Vec2(XMin(), YMin()),	p2Vec2(XMin(), YMax()))};	// TopLeft to BottomLeft.
}

bool p2AABB::Overlaps(const p2AABB other) const
{
	float sumOfHalfWidths = (other.XMax() - other.XMin() + XMax() - XMin()) * 0.5f;
	float sumOfHalfHeights = (other.YMax() - other.YMin() + YMax() - YMin()) * 0.5f;
	float deltaAvgX = _CMATH_::abs((other.XMin() + other.XMax()) * 0.5f - (XMin() + XMax()) * 0.5f);
	float deltaAvgY = _CMATH_::abs((other.YMin() + other.YMax()) * 0.5f - (YMin() + YMax()) * 0.5f);
	__int8 flag = 0;

	if (sumOfHalfWidths > deltaAvgX) // If there's overlap on X.
	{
		flag |= 1 << 1;
	}
	if (sumOfHalfHeights > deltaAvgY) // If there's overlap on Y.
	{
		flag |= 1;
	}

	return flag == (1 << 1 | 1);
}

std::string p2AABB::ToString() const
{
	std::string returnValue = "Left: ";
	returnValue.append(std::to_string(XMin()));
	returnValue.append("\n Right: ");
	returnValue.append(std::to_string(XMax()));
	returnValue.append("\n Top: ");
	returnValue.append(std::to_string(YMin()));
	returnValue.append("\n Bottom: ");
	returnValue.append(std::to_string(YMax()));
	returnValue.append("\n");
	return returnValue;
}
