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

#ifndef SFGE_P2CONTACT_H
#define SFGE_P2CONTACT_H

#include <array>
#include <vector>
class p2Collider;
class p2Quad;
class p2Body;
#include <p2vector.h>

struct PotentialCollision
{
	std::vector<p2Body*> siblings = std::vector<p2Body*>();
	std::vector<p2Body*> potentialCollideesAbove = std::vector<p2Body*>();
};

struct Intersection
{
	bool anyContact = false;
};
struct CircleIntersection : public Intersection
{
	// Constructors.
	CircleIntersection(): intersections(std::vector<p2Vec2>()), mtv(std::array<p2Vec2,2>()) {};
	CircleIntersection(const bool anyContact, const std::vector<p2Vec2> intersections, const std::array<p2Vec2,2> mtv) : Intersection{ anyContact }, intersections(intersections), mtv(mtv){};
	// Public methods.
	p2Vec2 AverageIntersection() const;
	// Public attributes.
	std::vector<p2Vec2> intersections = std::vector<p2Vec2>();
	std::array<p2Vec2,2> mtv = std::array<p2Vec2, 2>();
};
struct SatIntersection : public Intersection
{
	// Constructors.
	SatIntersection() {};
	SatIntersection(const bool anyContact, const p2Vec2 mtv) : Intersection{ anyContact }, minimumTranslationVector(mtv){};
	// Public attributes.
	p2Vec2 minimumTranslationVector = p2Vec2();
};

/**
* \brief Representation of a contact given as argument in a p2ContactListener
*/
struct p2Contact
{
	p2Collider* GetColliderA(); // Used by SFGE.
	p2Collider* GetColliderB();
	p2Collider* ColliderA = nullptr; // Used in physics engine.
	p2Collider* ColliderB = nullptr;
	std::string ToString() const;
};

/**
@Brief: Base class to derive from when creating a contact listener.
*/
class p2ContactListener
{
public:
	virtual void BeginContact(p2Contact* contact) = 0;
	virtual void EndContact(p2Contact* contact) = 0;
};

/**
@Brief: Manages creation, filtering and destruction of p2Contacts. Sends contact messages to contact listener.
*/
class p2ContactManager
{
public:
	// Constructors.
	p2ContactManager() {};
	p2ContactManager(p2ContactListener* listener) : m_ContactListener(listener) {};

	// Properties.
	void SetContactListener(p2ContactListener* listener);
	
	// Public methods.
	void SolveContacts(p2Quad* rootQuad);

private:
	// Private attributes.
	p2ContactListener* m_ContactListener = nullptr;
	std::vector<p2Contact> m_CurrentContacts = std::vector<p2Contact>();
};
#endif