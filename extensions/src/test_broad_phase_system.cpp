#include <extensions/test_broad_phase_system.h>
#include <graphics/graphics2d.h>
#include <physics/physics2d.h>

namespace sfge::ext
{
	TestBroadPhaseSystem::TestBroadPhaseSystem(Engine& engine) : System(engine){}

	void TestBroadPhaseSystem::OnEngineInit()
	{
		// Get ptrs to managers and entities.
		Body2dManager* bodyManager = m_Engine.GetPhysicsManager()->GetBodyManager();
		ShapeManager* shapeManager = m_Engine.GetGraphics2dManager()->GetShapeManager();
		EntityManager* entityManager = m_Engine.GetEntityManager();
		auto bodies = entityManager->GetEntitiesWithType(ComponentType::BODY2D);
		auto shapes = entityManager->GetEntitiesWithType(ComponentType::SHAPE2D);
		
		// Store ptrs to shapes whose color we'll be modifying and initialize contact counters.
		for (size_t i = 0; i < shapes.size(); i++)
		{
			m_Shapes.push_back(shapeManager->GetComponentPtr(shapes[i]));
			m_ContactCount.push_back(0);
		}

		// Give bodies initial velocity.
		p2Vec2 randomForce;
		float initialForceMultiplier = 0.02f;
		for (size_t i = 0; i < bodies.size(); i++)
		{
			randomForce = p2Vec2(rand() % 2 - 1, rand() % 2 - 1) * initialForceMultiplier; // Get random force between x = [-1;1] and y = [-1;1] and multiply.
			bodyManager->GetComponentRef(bodies[i]).ApplyForce(randomForce); // Apply random force.
		}
	}
	void TestBroadPhaseSystem::OnAfterSceneLoad()
	{
		// Add random forces to objects.
	}
	void TestBroadPhaseSystem::OnFixedUpdate()
	{
		// Update shape colors.
	}
	void TestBroadPhaseSystem::OnContact(ColliderData* c1, ColliderData* c2, bool enter)
	{
		// Increment / decrement contact counters.
	}
}
