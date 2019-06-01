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
#include <p2shape.h>

// p2Shape.
p2ShapeType p2Shape::GetType() const
{
	return m_Type;
}

// p2CircleShape.
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

// p2RectShape.
p2Vec2 p2RectShape::GetSize()
{
	return m_Size;
}
/*std::array<p2Mat22,4> p2RectShape::GetSides() const
{
	std::array<p2Mat22, 4> returnValue;
	returnValue[0] = p2Mat22(p2Vec2(0,			0),			p2Vec2(m_Size.x,	0));		// Top.
	returnValue[1] = p2Mat22(p2Vec2(m_Size.x,	0),			p2Vec2(m_Size.x,	m_Size.y));	// Right.
	returnValue[2] = p2Mat22(p2Vec2(0,			m_Size.y),	p2Vec2(m_Size.x,	m_Size.y));	// Bottom.
	returnValue[3] = p2Mat22(p2Vec2(0,			0),			p2Vec2(0,			m_Size.y));	// Left.
	return returnValue;
}*/
void p2RectShape::SetSize(p2Vec2 size)
{
	m_Size = size;
}