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

enum Duet: int
{
	OO = 0,
	OI = 1,
	IO = 2,
	II = 3
};

class RectIntersectionFlag
{
public:
	std::array<Duet,4> GetFlag() const;
	void SetFlag(const std::array<Duet, 4> flag);
	Duet GetMins() const;
	void SetMins(const Duet mins);
	Duet GetMaxes() const;
	void SetMaxes(const Duet maxs);
	Duet GetMaxMins() const;
	void SetMaxMins(const Duet maxMins);
	Duet GetSymmetry() const;
	void InitSymmetry(const RectIntersectionFlag otherDimensionFlag);

private:
	__int8 m_flag;
};

enum p2ShapeType
{
	NONE,
	RECTANGLE,
	CIRCLE
};

struct Intersection
{
	std::vector<p2Vec2> intersections;
	bool anyContact;
	p2Vec2 AverageIntersection() const;
};

/**
* \brief Abstract representation of a shape
*/
class p2Shape
{
public:
	p2Shape() : m_Type(p2ShapeType::NONE){};
	p2Shape(p2ShapeType type) : m_Type(type) {};
	p2ShapeType GetType()const;
	virtual p2Vec2 GetSize() = 0;
	virtual Intersection IntersectsSameType(p2Shape& other, p2Vec2 myPosition, p2Vec2 otherPosition) = 0;
private:
	p2ShapeType m_Type;
};

/**
* \brief Representation of a physics circle
*/
class p2CircleShape : public p2Shape
{
public:
	p2CircleShape() : p2Shape(p2ShapeType::CIRCLE) {};
	p2CircleShape(const float radius) : p2Shape(p2ShapeType::CIRCLE), m_Radius(radius) {};

	float GetRadius() const;
	void SetRadius(float radius);
	p2Vec2 GetSize() override;
	Intersection IntersectsSameType(p2Shape& other, p2Vec2 myPosition, p2Vec2 otherPosition) override;
private:
	float m_Radius = 0.0f;
};

/** 
* \brief Representation of a rectangle
*/
class p2RectShape : public p2Shape
{
public:
	p2RectShape() : p2Shape(p2ShapeType::RECTANGLE) {};
	p2RectShape(const p2Vec2 size) : p2Shape(p2ShapeType::RECTANGLE), m_Size(size) {};

	void SetSize(p2Vec2 size);
	p2Vec2 GetSize() override;
	Intersection IntersectsSameType(p2Shape& other, p2Vec2 myPosition, p2Vec2 otherPosition) override;
private:
	p2Vec2 m_Size;
};

class p2PolygonShape : public p2Shape
{
	
};

#endif