#include <extensions/explosion_system.h>

void sfge::ext::ExplosionSystem::OnEngineInit()
{
	inputManager = m_Engine.GetInputManager();
	auto* bodiesManager = m_Engine.GetPhysicsManager()->GetBodyManager();
	auto entities = m_Engine.GetEntityManager()->GetEntitiesWithType(sfge::ComponentType::BODY2D);
	for (auto entity : entities)
	{
		bodies.push_back(bodiesManager->GetComponentPtr(entity));
	}
}

void sfge::ext::ExplosionSystem::OnUpdate(float dt)
{
	if (inputManager->GetKeyboardManager().IsKeyDown(sf::Keyboard::Key::E))
	{
		for (auto* body : bodies)
		{
			body->ApplyForce((body->GetPosition() - (p2Vec2(12.8f, 7.2f) * 0.5f)) * EXPLOSION_MULTIPLIER);
		}
	}
}
