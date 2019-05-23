#include <extensions/test_collisions_system.h>
#include <physics/physics2d.h>
#include <graphics/graphics2d.h>
#include <p2aabb.h>
#include <p2shape.h>

namespace sfge::ext
{
	TestCollisionsSystem::TestCollisionsSystem(Engine& engine) : System(engine){}

	void TestCollisionsSystem::OnEngineInit()
	{
		// Get ptrs to entities.
		auto entities_bodies = m_Engine.GetEntityManager()->GetEntitiesWithType(ComponentType::BODY2D);

		// Store ptrs to bodies and store circles radii.
		Body2dManager* bodyManager = m_Engine.GetPhysicsManager()->GetBodyManager();
		m_GraphicsManager = m_Engine.GetGraphics2dManager();
		for (size_t i = 0; i < entities_bodies.size(); i++)
		{
			m_Bodies.push_back(bodyManager->GetComponentPtr(entities_bodies[i]));
			m_Radii.push_back(static_cast<p2CircleShape*>(m_Bodies[i]->GetBody()->GetCollider()->GetShape())->GetRadius());
		}

		// Give bodies initial velocity.
		float initialForceMultiplier = 0.04f;
		float randomX, randomY;
		for (size_t i = 0; i < m_Bodies.size(); i++)
		{
			// Bit of code taken from: https://stackoverflow.com/questions/686353/random-float-number-generation
			randomX = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 + 1)));
			randomY = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 + 1)));
			// m_Bodies[i]->ApplyForce(p2Vec2(randomX, randomY) * initialForceMultiplier); // Apply random force with components varying between -1 and 1.
		}
	}
	void TestCollisionsSystem::OnFixedUpdate()
	{
		// Prevent bodies from going out of bounds.
		p2Vec2 bodyPosition;
		p2AABB bodyBounds;
		for (size_t i = 0; i < m_Bodies.size(); i++)
		{
			bodyPosition = m_Bodies[i]->GetPosition();
			bodyBounds = m_Bodies[i]->GetAabb();
			if (bodyPosition.x - bodyBounds.GetExtends().x	< 0) // Entering left screen edge.
			{
				m_Bodies[i]->SetPosition(p2Vec2(12.8f - 0.51f, bodyPosition.y)); // Teleport body to right edge of screen.
			}
			if (bodyPosition.x + bodyBounds.GetExtends().x	> 12.8f) // Entering right screen edge.
			{
				m_Bodies[i]->SetPosition(p2Vec2(1, bodyPosition.y)); // Teleport body to left edge of screen.
			}
			if (bodyPosition.y - bodyBounds.GetExtends().y	< 0) // Entering top screen edge.
			{
				m_Bodies[i]->SetPosition(p2Vec2(bodyPosition.x,	7.2f - 0.51f)); // Teleport body to bottom edge of screen.
			}
			if (bodyPosition.y + bodyBounds.GetExtends().y	> 7.2f) // Entering bottom screen edge.
			{
				m_Bodies[i]->SetPosition(p2Vec2(bodyPosition.x, 0.51f)); // Teleport body to bottom edge of screen.
			}
		}
	}
	void TestCollisionsSystem::OnDraw()
	{
		p2AABB currentAABB;
		for (size_t i = 0; i < m_Bodies.size(); i++)
		{
			m_GraphicsManager->DrawCircle(m_Bodies[i]->GetPosition().ToGraphicSpace(), m_Radii[i]);
			currentAABB = m_Bodies[i]->GetAabb();
			m_GraphicsManager->DrawBox(m_Bodies[i]->GetPosition().ToGraphicSpace(), sfge::Vec2f(2 * currentAABB.GetExtends().x, 2 * currentAABB.GetExtends().y));
		}
	}
}