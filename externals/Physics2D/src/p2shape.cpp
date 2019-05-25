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

float p2CircleShape::GetRadius() const
{
	return m_Radius;
}

void p2CircleShape::SetRadius(float radius)
{
	m_Radius = radius;
}

p2Vec2 p2CircleShape::GetSize()
{
	return p2Vec2(m_Radius, m_Radius);
}

Intersection p2CircleShape::IntersectsSameType(p2Shape& other, p2Vec2 myPosition, p2Vec2 otherPosition)
{
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

		return Intersection{ std::vector<p2Vec2>{p2Vec2(P2.x + deltaY, P2.y - deltaX), p2Vec2(P2.x - deltaY, P2.y + deltaX)}, true };
	}
	else if (distanceBetweenCenters == m_Radius + c.m_Radius ||
			 distanceBetweenCenters == _CMATH_::abs(m_Radius - c.m_Radius)) // Case 1 intersection.
	{
		return Intersection{ Intersection{ std::vector<p2Vec2>{p2Vec2(myPosition + (directionBetweenCenters).Normalized() * m_Radius)}, true } };
	}
	else // Case no intersections.
	{
		Intersection intersect;
		intersect.anyContact = false;
		return intersect;
	}
}

void p2RectShape::SetSize(p2Vec2 size)
{
	m_Size = size;
}

p2Vec2 p2RectShape::GetSize()
{
	return m_Size;
}

Intersection p2RectShape::IntersectsSameType(p2Shape& other, p2Vec2 myPosition, p2Vec2 otherPosition)
{
	p2RectShape otherRectShape = *static_cast<p2RectShape*>(&other); // Cast other.
	p2Vec2 collisionDirection = otherPosition - myPosition;
	Intersection intersect{std::vector<p2Vec2>(), false};
	RectIntersectionFlag xFlag;
	RectIntersectionFlag yFlag;

	// "t" stands for "this" and "o" stands for "other". See technical documentation to understand what's going on.
	float t_XMin = myPosition.x - (m_Size.x * 0.5f);
	float t_XMax = myPosition.x + (m_Size.x * 0.5f);
	float t_YMin = myPosition.y - (m_Size.y * 0.5f);
	float t_YMax = myPosition.y + (m_Size.y * 0.5f);
	float o_XMin = otherPosition.x - (otherRectShape.m_Size.x * 0.5f);
	float o_XMax = otherPosition.x + (otherRectShape.m_Size.x * 0.5f);
	float o_YMin = otherPosition.y - (otherRectShape.m_Size.y * 0.5f);
	float o_YMax = otherPosition.y + (otherRectShape.m_Size.y * 0.5f);



	return intersect;
}

p2ShapeType p2Shape::GetType() const
{
	return m_Type;
}

p2Vec2 Intersection::AverageIntersection() const
{
	return p2Vec2();
}

#pragma region RectIntersectionFlag
std::array<Duet, 4> RectIntersectionFlag::GetFlag() const
{
	return std::array<Duet, 4>{ GetMins(), GetMaxes(), GetMaxMins(), GetSymmetry() };
}

void RectIntersectionFlag::SetFlag(const std::array<Duet, 4> flag)
{}

Duet RectIntersectionFlag::GetMins() const
{
	return (Duet)(m_flag >> 6);
}

void RectIntersectionFlag::SetMins(const Duet mins)
{
	m_flag |= ((mins >> 1) & 1) << 7 | (mins & 1) << 6;
}

Duet RectIntersectionFlag::GetMaxes() const
{
	return (Duet)((m_flag >> 4) | (0 << 3) || (0 << 2));
}

void RectIntersectionFlag::SetMaxes(const Duet maxs)
{
	m_flag |= ((maxs >> 1) & 1) << 5 | (maxs & 1) << 4;
}

Duet RectIntersectionFlag::GetMaxMins() const
{
	return (Duet)((m_flag >> 2) | (0 << 5) | (0 << 4) | (0 << 3) | (0 << 2));
}

void RectIntersectionFlag::SetMaxMins(const Duet maxMins)
{
	m_flag |= ((maxMins >> 1) & 1) << 3 | (maxMins & 1) << 2;
}

Duet RectIntersectionFlag::GetSymmetry() const
{
	return (Duet)(m_flag | (0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 3) | (0 << 2));
}

void RectIntersectionFlag::InitSymmetry(const RectIntersectionFlag otherDimensionFlag)
{
	// TODO: take into account symmetrical cases.

	// Bases.
	__int8 IOIO = 1 << 3 | 1 << 1;
	__int8 IOII = 1 << 3 | 1 << 1 | 1;
	__int8 IIIO = 1 << 3 | 1 << 2 | 1 << 1;
	// Symmetries.
	__int8 OIOI = 1 << 2 | 1;
	__int8 IIOI = 1 << 3 | 1 << 2 | 1;
	__int8 OIII = 1 << 2 | 1 << 1 | 1;
	// Get flag components.
	__int8 thisDimension_mins = (__int8)GetMins();
	__int8 thisDimension_maxes = (__int8)GetMaxes();
	__int8 otherDimension_mins = (__int8)otherDimensionFlag.GetMins();
	__int8 otherDimension_maxes = (__int8)otherDimensionFlag.GetMaxes();
	// Set up partial flag for analysis.
	__int8 thisDimension_partialFlag = (thisDimension_mins >> 1) & 1 << 3 | (thisDimension_mins & 1) << 2 | (thisDimension_maxes >> 1) & 1 << 1 | (thisDimension_maxes & 1);
	__int8 otherDimension_partialFlag = (otherDimension_mins >> 1) & 1 << 3 | (otherDimension_mins & 1) << 2 | (otherDimension_maxes >> 1) & 1 << 1 | (otherDimension_maxes & 1);
	// Analyse flags.
	if (thisDimension_partialFlag == OIOI || thisDimension_partialFlag == IIOI || thisDimension_partialFlag == OIII) // This intersection's D dimension's intersection case is a symmetry of a base case.
	{
		m_flag |= 1 << 7;
	}
	if (otherDimension_partialFlag == OIOI || otherDimension_partialFlag == IIOI || otherDimension_partialFlag == OIII) // This intersection's D + 1 dimension's intersection case is a symmetry of a base case.
	{
		m_flag |= 1 << 6;
	}
}
#pragma endregion
