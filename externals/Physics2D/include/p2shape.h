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
#include <p2vector.h>
#include <string>
#include <p2matrix.h>

// Intersection related.

struct Intersection
{
	bool anyContact;
};
struct CircleIntersection : public Intersection
{
	// Constructors.
	CircleIntersection(const bool anyContact, const std::vector<p2Vec2> intersections) : Intersection{anyContact}, intersections(intersections){};
	// Public methods.
	p2Vec2 AverageIntersection() const;
	// Public attributes.
	std::vector<p2Vec2> intersections;
};
struct SatIntersection : public Intersection
{
	// Constructors.
	SatIntersection() {};
	SatIntersection(const bool anyContact, const p2Vec2 mtv) : Intersection{ anyContact }, minimumTranslationVector(mtv){};
	// Public attributes.
	p2Vec2 minimumTranslationVector;
};

// Shape related.

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
	p2ShapeType m_Type;
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
	// Public methods.
	CircleIntersection FindIntersections(p2Shape& other, p2Vec2 myPosition, p2Vec2 otherPosition);
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
	std::array<p2Mat22,4> GetSides() const;
	void SetSize(p2Vec2 size);
	// Public methods.
	SatIntersection FindIntersections(p2Shape& other, p2Vec2 myPosition, p2Vec2 otherPosition);
private:
	p2Vec2 m_Size;
};

class p2PolygonShape : public p2Shape
{
	
};
#endif