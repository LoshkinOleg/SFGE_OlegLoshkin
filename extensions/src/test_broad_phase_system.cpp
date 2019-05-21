#include <extensions/test_broad_phase_system.h>
#include <graphics/graphics2d.h>
#include <physics/physics2d.h>
#include <p2world.h>
#include <p2aabb.h>

namespace sfge::ext
{
	TestBroadPhaseSystem::TestBroadPhaseSystem(Engine& engine) : System(engine){}

	void TestBroadPhaseSystem::OnEngineInit()
	{
		// Get ptrs to managers and root quad.
		m_PhysicsManager = m_Engine.GetPhysicsManager();
		m_BodyManager = m_PhysicsManager->GetBodyManager();
		m_GraphicsManager = m_Engine.GetGraphics2dManager();
		m_ShapeManager = m_GraphicsManager->GetShapeManager();
		m_EntityManager = m_Engine.GetEntityManager();
		m_World = m_PhysicsManager->GetWorld_RawPtr();

		// Get ptrs to entities.
		auto entities_bodies = m_EntityManager->GetEntitiesWithType(ComponentType::BODY2D);
		auto entities_shapes = m_EntityManager->GetEntitiesWithType(ComponentType::SHAPE2D);
		auto entities_colliders = m_EntityManager->GetEntitiesWithType(ComponentType::COLLIDER2D);

		// Store ptrs to shapes whose color we'll be modifying and initialize contact counters.
		for (size_t i = 0; i < entities_shapes.size(); i++)
		{
			m_Shapes.push_back(m_ShapeManager->GetComponentPtr(entities_shapes[i]));
			m_ContactCount.push_back(0);
		}
		// Store ptrs to bodies.
		for (size_t i = 0; i < entities_bodies.size(); i++)
		{
			m_Bodies.push_back(m_BodyManager->GetComponentPtr(entities_bodies[i]));
		}
		// Fill contact counter dictionary.
		for (size_t i = 0; i < entities_colliders.size(); i++)
		{
			m_Dictionary[entities_colliders[i]] = (int)i;
		}

		// Give bodies initial velocity.
		float initialForceMultiplier = 0.02f;
		float randomX, randomY;
		for (size_t i = 0; i < m_Bodies.size(); i++)
		{
			// Bit of code taken from: https://stackoverflow.com/questions/686353/random-float-number-generation
			randomX = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 + 1)));
			randomY = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 + 1)));
			m_Bodies[i]->ApplyForce(p2Vec2(randomX, randomY) * initialForceMultiplier); // Apply random force with components varying between -1 and 1.
		}
	}
	void TestBroadPhaseSystem::OnFixedUpdate()
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
				m_Bodies[i]->SetPosition(p2Vec2(12.8f - 1, bodyPosition.y)); // Teleport body to right edge of screen.
			}
			if (bodyPosition.x + bodyBounds.GetExtends().x	> 12.8f) // Entering right screen edge.
			{
				m_Bodies[i]->SetPosition(p2Vec2(1, bodyPosition.y)); // Teleport body to left edge of screen.
			}
			if (bodyPosition.y - bodyBounds.GetExtends().y	< 0) // Entering top screen edge.
			{
				m_Bodies[i]->SetPosition(p2Vec2(bodyPosition.x,	7.2f - 1)); // Teleport body to bottom edge of screen.
			}
			if (bodyPosition.y + bodyBounds.GetExtends().y	> 7.2f) // Entering bottom screen edge.
			{
				m_Bodies[i]->SetPosition(p2Vec2(bodyPosition.x, 1)); // Teleport body to bottom edge of screen.
			}
		}

		// Set color depending on contact count.
		for (size_t i = 0; i < m_Shapes.size(); i++) // For each shape.
		{
			// Color it if it is colliding with anything.
			if (m_ContactCount[i] > 0)
			{
				m_Shapes[i]->SetFillColor(sf::Color::Red);
			}
			else
			{
				m_Shapes[i]->SetFillColor(sf::Color::White);
			}
		}
	}
	void TestBroadPhaseSystem::OnContact(ColliderData* c1, ColliderData* c2, bool enter)
	{
		// Increment / decrement contact counters.
		if (enter)
		{
			m_ContactCount[m_Dictionary[c1->entity]] += 1;
			m_ContactCount[m_Dictionary[c2->entity]] += 1;
		}
		else
		{
			m_ContactCount[m_Dictionary[c1->entity]] -= 1;
			m_ContactCount[m_Dictionary[c2->entity]] -= 1;
		}
	}
	void TestBroadPhaseSystem::OnDraw()
	{
		auto quadsBounds = m_World->GetQuadTreeBounds();
		std::array<p2Mat22, 4> sides;
		for (size_t i = 0; i < quadsBounds.size(); i++)
		{
			sides = quadsBounds[i].Sides();
			for (size_t j = 0; j < 4; j++)
			{
				m_GraphicsManager->DrawLine(sides[j].rows[0].ToGraphicSpace(), sides[j].rows[1].ToGraphicSpace(), sf::Color::Green);
			}
		}
	}
}
