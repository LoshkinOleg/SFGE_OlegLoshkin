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

#include <iostream>
#include <p2world.h>

p2World::p2World(p2Vec2 gravity, p2Vec2 aabbSize, int bodiesPerQuad): m_Gravity(gravity)
{
	m_Bodies.resize(MAX_BODY_LEN);
	m_RootQuad = p2QuadTree(0, p2AABB(p2Vec2(0, aabbSize.y), p2Vec2(aabbSize.x, 0)));
	p2QuadTree::Max_Objects = bodiesPerQuad;
	m_ContactManager = p2ContactManager();
}

void p2World::Step(float dt)
{
	// Update bodies' forces and positions.
	for (p2Body& body : m_Bodies)
	{
		switch (body.GetType())
		{
			case p2BodyType::DYNAMIC:
			{
				// Apply gravity and update positions.
				body.ApplyForceToCenter(m_Gravity * dt * body.GetMass());
				body.UpdatePosition();
			}break;
			case p2BodyType::KINEMATIC:
			{
				// Update positions only.
				body.UpdatePosition();
			}break;
			case p2BodyType::STATIC:
			{
				// Don't apply gravity and don't bother updating position.
			}break;
		}
	}

	// Update QuadTree.
	m_RootQuad.Clear(); // Clear it.
	// Refill it.
	for (p2Body& body : m_Bodies)
	{
		m_RootQuad.Insert(&body);
	}

	// Solve contacts.
	// m_ContactManager.SolveContacts(&m_RootQuad);
}

p2Body * p2World::CreateBody(p2BodyDef* bodyDef)
{
	p2Body& body = m_Bodies[m_BodyIndex];
	body.Init(bodyDef);
	m_BodyIndex++;
	return &body;
}

void p2World::SetContactListener(p2ContactListener * contactListener)
{
	m_ContactManager.SetContactListener(contactListener);
}

std::vector<p2AABB> p2World::GetQuadTreeBounds() const
{
	std::vector<p2AABB> returnValue = std::vector<p2AABB>();
	m_RootQuad.GetQuadTreesAabbs(returnValue);
	return returnValue;
}

void p2World::LogQuadsBodyCount() const
{
	std::cout << "--------------------------------" << std::endl;
	m_RootQuad.LogQuadsBodyCount();
}
