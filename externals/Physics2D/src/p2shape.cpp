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

#include <p2shape.h>
#include <cmath>
#include <p2aabb.h>
// #include <p2collider.h>

// Intersection.

p2Vec2 CircleIntersection::AverageIntersection() const
{
	p2Vec2 returnValue;
	for (size_t i = 0; i < intersections.size(); i++)
	{
		returnValue += intersections[i];
	}
	return returnValue / intersections.size();
}

// Shape.

p2ShapeType p2Shape::GetType() const
{
	return m_Type;
}

// Circle shape.

p2Vec2 p2CircleShape::GetSize()
{
	return p2Vec2(m_Radius, m_Radius);
}
float p2CircleShape::GetRadius() const
{
	return m_Radius;
}
void p2CircleShape::SetRadius(float radius)
{
	m_Radius = radius;
}
CircleIntersection p2CircleShape::FindIntersections(p2Shape& other, p2Vec2 myPosition, p2Vec2 otherPosition)
{
	// TODO: actually understand what's going on...

	p2CircleShape c = *static_cast<p2CircleShape*>(&other); // Cast other shape.
	p2Vec2 directionBetweenCenters = otherPosition - myPosition;
	float distanceBetweenCenters = directionBetweenCenters.GetMagnitude();

	if (distanceBetweenCenters < m_Radius + c.m_Radius) // Case 2 intersections.
	{
		// Code taken from: https://stackoverflow.com/questions/3349125/circle-circle-intersection-points
		p2Vec2 P0(myPosition.x, myPosition.y);
		p2Vec2 P1(otherPosition.x, otherPosition.y);
		float d, a, h;
		d = (P1 - P0).GetMagnitude();
		a = ( (m_Radius * m_Radius) - (c.m_Radius * c.m_Radius) + (d * d) ) / (2 * d);
		h = _CMATH_::sqrt( (m_Radius * m_Radius) - (a * a) );
		p2Vec2 P2 = ( (P1 - P0) * (a / d) ) + P0;

		float deltaY = h * (P1.y - P0.y) / d;
		float deltaX = h * (P1.x - P0.x) / d;

		return CircleIntersection{true, std::vector<p2Vec2>{p2Vec2(P2.x + deltaY, P2.y - deltaX), p2Vec2(P2.x - deltaY, P2.y + deltaX)} };
	}
	else if (distanceBetweenCenters == m_Radius + c.m_Radius ||
			 distanceBetweenCenters == _CMATH_::abs(m_Radius - c.m_Radius)) // Case 1 intersection.
	{
		return CircleIntersection{true, std::vector<p2Vec2>{p2Vec2(myPosition + (directionBetweenCenters).Normalized() * m_Radius)} };
	}
	else // Case no intersections.
	{
		return CircleIntersection{ false, std::vector<p2Vec2>() };
	}
}

// Rect shape.

p2Vec2 p2RectShape::GetSize()
{
	return m_Size;
}
std::array<p2Mat22,4> p2RectShape::GetSides() const
{
	std::array<p2Mat22, 4> returnValue;
	returnValue[0] = p2Mat22(p2Vec2(0,			0),			p2Vec2(m_Size.x,	0));		// Top.
	returnValue[1] = p2Mat22(p2Vec2(m_Size.x,	0),			p2Vec2(m_Size.x,	m_Size.y));	// Right.
	returnValue[2] = p2Mat22(p2Vec2(0,			m_Size.y),	p2Vec2(m_Size.x,	m_Size.y));	// Bottom.
	returnValue[3] = p2Mat22(p2Vec2(0,			0),			p2Vec2(0,			m_Size.y));	// Left.
	return returnValue;
}
void p2RectShape::SetSize(p2Vec2 size)
{
	m_Size = size;
}
SatIntersection p2RectShape::FindIntersections(p2Shape& other, p2Vec2 myPosition, p2Vec2 otherPosition)
{
	return SatIntersection();
}
