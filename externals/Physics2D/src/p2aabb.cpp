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

p2AABB::p2AABB()
{
	m_BottomLeft = p2Vec2(0,0);
	m_TopRight = p2Vec2(0, 0);
	m_XMin = 0;
	m_XMax = 0;
	m_YMin = 0;
	m_YMax = 0;
}

p2AABB::p2AABB(const p2Vec2 & bottomLeft, const p2Vec2 & topRight)
{
	m_BottomLeft = bottomLeft;
	m_TopRight = topRight;
	m_XMin = m_BottomLeft.x;
	m_XMax = m_TopRight.x;
	m_YMin = m_TopRight.y;
	m_YMax = m_BottomLeft.y;
}

p2AABB::p2AABB(const p2Vec2& size)
{
	m_BottomLeft = p2Vec2(0, size.y);
	m_TopRight = p2Vec2(size.x, 0);
	m_XMin = m_BottomLeft.x;
	m_XMax = m_TopRight.x;
	m_YMin = m_TopRight.y;
	m_YMax = m_BottomLeft.y;
}

p2AABB::p2AABB(const sf::Vector2f& size)
{
	m_BottomLeft = p2Vec2(0, size.y);
	m_TopRight = p2Vec2(size.x, 0);
	m_XMin = m_BottomLeft.x;
	m_XMax = m_TopRight.x;
	m_YMin = m_TopRight.y;
	m_YMax = m_BottomLeft.y;
}

p2Vec2 p2AABB::Center()
{
	return p2Vec2(m_BottomLeft.x + Extends().x, m_TopRight.y + Extends().y);
}

p2Vec2 p2AABB::Extends()
{
	return p2Vec2((m_TopRight.x - m_BottomLeft.x) / 2.0f, (m_BottomLeft.y - m_TopRight.y) / 2.0f);
}