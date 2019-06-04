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

#ifndef SFGE_P2SHAPE_H
#define SFGE_P2SHAPE_H

#include <array>
#include <vector>
#include <string>
#include <p2vector.h>
#include <p2matrix.h>

enum p2ShapeType
{
	NONE,
	RECTANGLE,
	CIRCLE
};

class p2Shape
{
public:
	// Constructors.
	p2Shape() : m_Type(p2ShapeType::NONE){};
	p2Shape(p2ShapeType type) : m_Type(type) {};
	// Properties.
	p2ShapeType GetType()const;
	virtual p2Vec2 GetSize() = 0;
private:
	p2ShapeType m_Type = NONE;
};

class p2CircleShape : public p2Shape
{
public:
	// Constructors.
	p2CircleShape() : p2Shape(p2ShapeType::CIRCLE) {};
	p2CircleShape(const float radius) : p2Shape(p2ShapeType::CIRCLE), m_Radius(radius) {};
	// Properties.
	p2Vec2 GetSize() override;
	float GetRadius() const;
	void SetRadius(float radius);
private:
	float m_Radius = 0.0f;
};

class p2RectShape : public p2Shape
{
public:
	// Constructors.
	p2RectShape() : p2Shape(p2ShapeType::RECTANGLE) {};
	p2RectShape(const p2Vec2 size) : p2Shape(p2ShapeType::RECTANGLE), m_Size(size) {};
	// Properties.
	p2Vec2 GetSize() override;
	// std::array<p2Mat22,4> GetSides() const;
	void SetSize(p2Vec2 size);
private:
	p2Vec2 m_Size = p2Vec2();
};

/*class p2PolygonShape : public p2Shape
{
	
};*/
#endif