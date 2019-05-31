#include <extensions/test_10_system.h>

sfge::ext::Test_10_System::Test_10_System(Engine& engine) : System(engine)
{}

void sfge::ext::Test_10_System::OnEngineInit()
{
	graphicsManager = m_Engine.GetGraphics2dManager();

	auto bodiesEntities = m_Engine.GetEntityManager()->GetEntitiesWithType(sfge::ComponentType::BODY2D);
	for (size_t i = 0; i < bodiesEntities.size(); i++)
	{
		bodies.push_back(m_Engine.GetPhysicsManager()->GetBodyManager()->GetComponentPtr(bodiesEntities[i]));
	}
}

void sfge::ext::Test_10_System::OnFixedUpdate()
{
	p2Vec2 position, linearVelocity;
	for (size_t i = 0; i < bodies.size(); i++)
	{
		position = bodies[i]->GetPosition();
		linearVelocity = bodies[i]->GetLinearVelocity();

		if (position.x < 0 || position.x > 12.8f)
		{
			bodies[i]->SetLinearVelocity(p2Vec2{ -linearVelocity.x, linearVelocity.y });
		}
		if (position.y < 0 || position.y > 7.2f)
		{
			bodies[i]->SetLinearVelocity(p2Vec2{ linearVelocity.x, -linearVelocity.y });
		}
	}

}
