#include <extensions/stay_on_screen_cpp_system.h>

void sfge::ext::StayOnScreenCppSystem::OnEngineInit()
{
	auto* bodyManager = m_Engine.GetPhysicsManager()->GetBodyManager();
	auto bodiesEntities = m_Engine.GetEntityManager()->GetEntitiesWithType(sfge::ComponentType::BODY2D);
	for (size_t i = 0; i < bodiesEntities.size(); i++)
	{
		bodies.push_back(bodyManager->GetComponentPtr(bodiesEntities[i]));
	}
}

void sfge::ext::StayOnScreenCppSystem::OnFixedUpdate()
{
	p2Vec2 position;
	for (Body2d* body : bodies)
	{
		position = body->GetPosition();
		if (position.x > 12.8f || position.x < 0)
		{
			body->SetLinearVelocity(p2Vec2{ -body->GetLinearVelocity().x, body->GetLinearVelocity().y });
		}
		if (position.y > 7.2f || position.y < 0)
		{
			body->SetLinearVelocity(p2Vec2{ body->GetLinearVelocity().x, -body->GetLinearVelocity().y });
		}
	}
}
