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

#ifndef SFGE_P2AABB_H
#define SFGE_P2AABB_H

#include <p2vector.h>
#include <..\externals\SFML\include\SFML\System\Vector2.hpp>
#include <vector>

/**
* \brief Struct representing a Axis Aligned Bounding Box
*/
struct p2AABB
{
public:
	// Constructors
	p2AABB();
	p2AABB(const p2Vec2& bottomLeft, const p2Vec2& topRight);
	p2AABB(const p2Vec2& size);
	p2AABB(const sf::Vector2f& size);

	// Properties.
	// Getters.
	p2Vec2 Center();
	p2Vec2 Extends();
	p2Vec2 BottomLeft() const;
	p2Vec2 TopRight() const;
	// Setters.
	float XMin() const;
	float XMax() const;
	float YMin() const;
	float YMax() const;
	void BottomLeft(const p2Vec2& newBottomLeft);
	void TopRight(const p2Vec2& newBottomLeft);

private:
	// Attributes.
	p2Vec2 m_BottomLeft;
	p2Vec2 m_TopRight;
	float m_XMin;
	float m_XMax;
	float m_YMin;
	float m_YMax;
};
#endif
