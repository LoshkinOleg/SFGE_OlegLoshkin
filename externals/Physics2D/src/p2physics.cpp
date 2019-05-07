#include "p2physics.h"
#include <physics\physics2d.h>
#include <iostream>
#include <p2body.h>

sfge::P2PhysicsManager::P2PhysicsManager()
{
	m_Gravity = p2Vec2(0,0);
}

sfge::P2PhysicsManager::P2PhysicsManager(const p2Vec2& gravity, Physics2dManager* ptr)
{
	m_Gravity = p2Vec2(gravity.x, gravity.y);
	m_Manager = ptr;
}

void sfge::P2PhysicsManager::FixedUpdate(std::vector<p2Body>& bodies) const
{
	for (int i = 0; i < bodies.size(); ++i)
	{
		HandleContacts(bodies);
		ApplyGravity(bodies);
		bodies.at(i).UpdatePosition();
	}
}

void sfge::P2PhysicsManager::ApplyGravity(std::vector<p2Body>& bodies) const
{
	for (int i = 0; i < bodies.size(); i++)
	{
		if (bodies.at(i).GetType() == p2BodyType::DYNAMIC)
		{
			bodies.at(i).ApplyGravity(m_Gravity);
		}
	}
}

void sfge::P2PhysicsManager::HandleContacts(std::vector<p2Body>& bodies) const
{
	// Get all bodies that needs collision checking.
	std::vector<p2Body*> bodiesToCheck = std::vector<p2Body*>();
	for (int i = 0; i < bodies.size(); i++)
	{
		if (bodies.at(i).IsInit())
		{
			bodiesToCheck.push_back(&bodies.at(i));
		}
	}

	// Check collisions.
	for (int i = bodiesToCheck.size(); i > 0; i++)
	{
		for (int j = 0; j < i; j++)
		{
			// TODO: Check collisions between all elements.
		}
	}
}