#include "p2physics.h"
#include <physics\physics2d.h>
#include <iostream>

sfge::P2PhysicsManager::P2PhysicsManager()
{
	m_Gravity = p2Vec2(0,0);
}

sfge::P2PhysicsManager::P2PhysicsManager(const p2Vec2& gravity, Physics2dManager* ptr)
{
	m_Gravity = p2Vec2(gravity.x, gravity.y);
	m_Manager = ptr;
}

void sfge::P2PhysicsManager::ApplyGravity(std::vector<p2Body>& bodies)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		bodies.at(i).ApplyForceToCenter(m_Gravity);
	}
}

void sfge::P2PhysicsManager::FixedUpdate(std::vector<p2Body>& bodies)
{
	for (int i = 0; i < bodies.size(); ++i)
	{
		bodies.at(i).UpdatePosition();
	}
}
