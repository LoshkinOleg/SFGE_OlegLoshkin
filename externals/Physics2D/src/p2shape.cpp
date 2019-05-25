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

		return Intersection{ p2Vec2(P2.x + deltaY, P2.y - deltaX), p2Vec2(P2.x - deltaY, P2.y + deltaX), P2, true };
	}
	else if (distanceBetweenCenters == m_Radius + c.m_Radius ||
			 distanceBetweenCenters == _CMATH_::abs(m_Radius - c.m_Radius)) // Case 1 intersection.
	{
		p2Vec2 contactPoint = p2Vec2(myPosition + (directionBetweenCenters).Normalized() * m_Radius);
		return Intersection{ Intersection{ contactPoint, contactPoint, contactPoint, true } };
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
	Intersection intersect{p2Vec2(), p2Vec2()};
	MirrorableFlag xFlag{0};
	MirrorableFlag yFlag{0};

	// "t" stands for "this" and "o" stands for "other". See technical documentation to understand what's going on.
	float t_XMin = myPosition.x - (m_Size.x * 0.5f);
	float t_XMax = myPosition.x + (m_Size.x * 0.5f);
	float t_YMin = myPosition.y - (m_Size.y * 0.5f);
	float t_YMax = myPosition.y + (m_Size.y * 0.5f);
	float o_XMin = otherPosition.x - (otherRectShape.m_Size.x * 0.5f);
	float o_XMax = otherPosition.x + (otherRectShape.m_Size.x * 0.5f);
	float o_YMin = otherPosition.y - (otherRectShape.m_Size.y * 0.5f);
	float o_YMax = otherPosition.y + (otherRectShape.m_Size.y * 0.5f);

	// Set up flags.
	// X flag.
	if (t_XMin <= o_XMin)
	{
		xFlag.flag |= 1 << 3;
	}
	if (t_XMin >= o_XMin)
	{
		xFlag.flag |= 1 << 2;
	}
	if (t_XMax <= o_XMax)
	{
		xFlag.flag |= 1 << 1;
	}
	if (t_XMax >= o_XMax)
	{
		xFlag.flag |= 1 << 0;
	}
	// Y flag.
	if (t_YMin <= o_YMin)
	{
		yFlag.flag |= 1 << 3;
	}
	if (t_YMin >= o_YMin)
	{
		yFlag.flag |= 1 << 2;
	}
	if (t_YMax <= o_YMax)
	{
		yFlag.flag |= 1 << 1;
	}
	if (t_YMax >= o_YMax)
	{
		yFlag.flag |= 1 << 0;
	}

	// Case 0 (IOIO || OIOI):
	if (xFlag.flag == MirrorableFlagEnum::IOIO)
	{
		if (t_XMax == o_XMin) // Case T and O barely touching at the left. They share a segment or side.
		{
			if (yFlag.flag == MirrorableFlagEnum::IOIO) // T is located at top left of O.
			{
				if (t_YMax == o_YMin)
				{
					// T barely touching O. One intersection.
					intersect.i0.x = t_XMax;
					intersect.i1.x = t_XMax;
					intersect.i0.y = t_YMax;
					intersect.i1.y = t_YMax;
					intersect.intersectionCenter = intersect.i0;
					intersect.anyContact = true;
					return intersect;
				}
				else
				{
					// T shares a segment with O. T's avg y > O's avg y but T's yMax < O's yMax.
					intersect.i0.x = t_XMax;
					intersect.i1.x = t_XMax;
					intersect.i0.y = t_YMin;
					intersect.i1.y = t_YMax;
					intersect.intersectionCenter = (intersect.i0 + intersect.i1) * 0.5f;
					intersect.anyContact = true;
					return intersect;
				}
			}
			else if (yFlag.flag == !MirrorableFlagEnum::IOIO) // T is located at bottom left of O.
			{
				if (t_YMin == o_YMax)
				{
					// T barely touching O. One intersection.
					intersect.i0.x = t_XMax;
					intersect.i1.x = t_XMax;
					intersect.i0.y = t_YMin;
					intersect.i1.y = t_YMin;
					intersect.intersectionCenter = intersect.i0;
					intersect.anyContact = true;
					return intersect;
				}
				else
				{
					// T shares a segment with O. T's avg y > O's avg y but T's yMin < O's yMin.
					intersect.i0.x = t_XMax;
					intersect.i1.x = t_XMax;
					intersect.i0.y = t_YMin;
					intersect.i1.y = t_YMax;
					intersect.intersectionCenter = (intersect.i0 + intersect.i1) * 0.5f;
					intersect.anyContact = true;
					return intersect;
				}
			}
			if (yFlag.flag == MirrorableFlagEnum::IOII || yFlag.flag == !MirrorableFlagEnum::IOII || yFlag.flag == MirrorableFlagEnum::IOOI)
			{
				// T barely touching O. T's height is greater than O's height. They share a segment.
				intersect.i0.x = t_XMax;
				intersect.i1.x = t_XMax;
				intersect.i0.y = o_YMin;
				intersect.i1.y = o_YMax;
				intersect.intersectionCenter = (intersect.i0 + intersect.i1) * 0.5f;
				intersect.anyContact = true;
				return intersect;
			}
			if (yFlag.flag == MirrorableFlagEnum::IIIO || yFlag.flag == !MirrorableFlagEnum::IIIO || yFlag.flag == MirrorableFlagEnum::IIII)
			{
				// T barely touching O. T's height is smaller or equal to O's height. They share a segment or a whole side in case of equality.
				intersect.i0.x = t_XMax;
				intersect.i1.x = t_XMax;
				intersect.i0.y = t_YMin;
				intersect.i1.y = t_YMax;
				intersect.intersectionCenter = (intersect.i0 + intersect.i1) * 0.5f;
				intersect.anyContact = true;
				return intersect;
			}
		}
		else // T and O share an area.
		{
			if (yFlag.flag == MirrorableFlagEnum::IOIO) // T is located at top left of O.
			{
				if (t_YMax == o_YMin)
				{
					// NOTE TO SELF: see drawing.
					intersect.i0.x = t_XMax;
					intersect.i1.x = t_XMax;
					intersect.i0.y = t_YMax;
					intersect.i1.y = t_YMax;
					intersect.intersectionCenter = (intersect.i0 + intersect.i1) * 0.5f;
					intersect.anyContact = true;
					return intersect;
				}
				else
				{
					intersect.i0.x = t_XMax;
					intersect.i1.x = t_XMax;
					intersect.i0.y = t_YMax;
					intersect.i1.y = t_YMax;
					intersect.intersectionCenter = (intersect.i0 + intersect.i1) * 0.5f;
					intersect.anyContact = true;
					return intersect;
				}
			}
			else if (yFlag.flag == !MirrorableFlagEnum::IOIO) // T is located at bottom left of O.
			{
				// T barely touching O.
				intersect.i0.x = t_XMax;
				intersect.i1.x = t_XMax;
				intersect.i0.y = t_YMin;
				intersect.i1.y = t_YMin;
				intersect.intersectionCenter = intersect.i0;
				intersect.anyContact = true;
				return intersect;
			}
			if (yFlag.flag == MirrorableFlagEnum::IOII || yFlag.flag == !MirrorableFlagEnum::IOII || yFlag.flag == MirrorableFlagEnum::IOOI)
			{
				// T barely touching O. T's height is greater than O's height. They share a segment.
				intersect.i0.x = t_XMax;
				intersect.i1.x = t_XMax;
				intersect.i0.y = o_YMin;
				intersect.i1.y = o_YMax;
				intersect.intersectionCenter = (intersect.i0 + intersect.i1) * 0.5f;
				intersect.anyContact = true;
				return intersect;
			}
			if (yFlag.flag == MirrorableFlagEnum::IIIO || yFlag.flag == !MirrorableFlagEnum::IIIO || yFlag.flag == MirrorableFlagEnum::IIII)
			{
				// T barely touching O. T's height is smaller or equal to O's height. They share a segment or a whole side in case of equality.
				intersect.i0.x = t_XMax;
				intersect.i1.x = t_XMax;
				intersect.i0.y = t_YMin;
				intersect.i1.y = t_YMax;
				intersect.intersectionCenter = (intersect.i0 + intersect.i1) * 0.5f;
				intersect.anyContact = true;
				return intersect;
			}
		}
	}
	else if(xFlag.flag == !MirrorableFlagEnum::IOIO)
	{

		if (t_XMin == o_XMax)
		{

		}
		else
		{

		}
	}
	// Case 1 (IOII || IIOI):
	if (xFlag.flag == MirrorableFlagEnum::IOII || xFlag.flag == !(MirrorableFlagEnum::IOII))
	{

	}
	// Case 2 (IIIO || OIII):
	if (xFlag.flag == MirrorableFlagEnum::IIIO || xFlag.flag == !(MirrorableFlagEnum::IIIO))
	{

	}
	// Case 3 (IIII):
	if (xFlag.flag == MirrorableFlagEnum::IIII)
	{

	}
	// Case 4 (IOOI):
	if (xFlag.flag == MirrorableFlagEnum::IOOI)
	{

	}
}

p2ShapeType p2Shape::GetType() const
{
	return m_Type;
}

__int8 MirrorableFlag::operator!() const
{
	// Thanks to Jeremy Ruten from https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
	return	((flag >> 3) & 1) << 0 |
			((flag >> 2) & 1) << 1 |
			((flag >> 1) & 1) << 2 |
			((flag >> 0) & 1) << 3;
}
