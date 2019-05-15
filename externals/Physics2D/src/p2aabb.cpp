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

#include <p2aabb.h>

p2Vec2 p2AABB::GetCenter() const
{
	return (bottomLeft + topRight)/2.0f;
}

p2Vec2 p2AABB::GetExtends() const
{
	return p2Vec2(topRight.x - bottomLeft.x, bottomLeft.y - topRight.y) / 2.0f;
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
	p2Vec2 other_topBound =		other.GetCenter() - p2Vec2(0,						other.GetExtends().y);
	p2Vec2 other_bottomBound =	other.GetCenter() + p2Vec2(0,						other.GetExtends().y);
	p2Vec2 other_leftBound =	other.GetCenter() - p2Vec2(other.GetExtends().x,	0					);
	p2Vec2 other_rightBound =	other.GetCenter() + p2Vec2(other.GetExtends().x,	0					);

	if (XMin() == 6.4f && XMax() == 9.6f && YMin() == 3.6f)
	{
		int i = 0;
	}

	__int8 flag = 0;

	// If other's top or bottom bounds are located between this aabb's bounds.
	if (other_topBound.y	>= YMin() && other_topBound.y		<= YMax()  ||
		other_bottomBound.y	>= YMin() && other_bottomBound.y	<= YMax()	)
	{
		flag = 1 << 0; // Tag for vertical overlap.
	}
	// If other's left or right bounds are located between this aabb's bounds.
	if (other_leftBound.x	>= XMin() && other_leftBound.x	<= XMax()  ||
		other_rightBound.x	>= XMin() && other_rightBound.x	<= XMax()	)
	{
		flag = flag | 1 << 1; // Tag for horizontal overlap.
	}

	return flag == (1 << 1 | 1 << 0); // Return true if there's both vertical and horizontal overlapping.
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
