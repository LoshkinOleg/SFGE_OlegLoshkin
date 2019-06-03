#ifndef TEST_11_SYSTEM_H
#define TEST_11_SYSTEM_H

#include <extensions/stay_on_screen_cpp.h>

namespace sfge::ext
{
	StayOnScreenCpp::StayOnScreenCpp(Engine& engine) : System(engine)
	{}

	void StayOnScreenCpp::OnEngineInit()
	{
		auto entities = m_Engine.GetEntityManager()->GetEntitiesWithType(sfge::ComponentType::BODY2D);
		Body2d* body;
		auto* bodyManager = m_Engine.GetPhysicsManager()->GetBodyManager();
		for (auto& entity : entities)
		{
			body = bodyManager->GetComponentPtr(entity);
			if (body->GetBody()->IsInit())
			{
				bodies.push_back(body);
			}
		}
	}

	void StayOnScreenCpp::OnFixedUpdate()
	{
		for (auto* body : bodies)
		{
			if (body->GetPosition().x < 0 || body->GetPosition().x > 12.8f)
			{
				body->SetLinearVelocity(p2Vec2{ -body->GetLinearVelocity().x, body->GetLinearVelocity().y });
			}
			if (body->GetPosition().y < 0 || body->GetPosition().y > 7.2f)
			{
				body->SetLinearVelocity(p2Vec2{ body->GetLinearVelocity().x, -body->GetLinearVelocity().y });
			}
		}
	}
}

#endif