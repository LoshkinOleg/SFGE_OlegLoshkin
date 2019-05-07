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

p2CircleShape::p2CircleShape() : p2Shape(p2ShapeType::CIRCLE){}

std::vector<float> p2CircleShape::GetSize() const
{
	return std::vector<float>{ m_Radius };
}

void p2CircleShape::SetRadius(float radius)
{
}

p2RectShape::p2RectShape() : p2Shape(p2ShapeType::RECTANGLE)
{}

std::vector<float> p2RectShape::GetSize() const
{
	return std::vector<float>{ m_Size.x, m_Size.y };
}

void p2RectShape::SetSize(p2Vec2 size)
{
}

p2Shape::p2Shape()
{
	m_type = p2ShapeType::NONE;
}

p2Shape::p2Shape(const p2ShapeType& type)
{
	m_type = type;
}

p2ShapeType p2Shape::GetType() const
{
	return m_type;
}
