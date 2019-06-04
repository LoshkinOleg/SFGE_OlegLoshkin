#include <extensions/reset_scene_system.h>

void sfge::ext::ResetSceneSystem::OnEngineInit()
{
	inputManager = m_Engine.GetInputManager();

	auto* bodiesManager = m_Engine.GetPhysicsManager()->GetBodyManager();
	auto* shapeManager = m_Engine.GetGraphics2dManager()->GetShapeManager();
	auto entities = m_Engine.GetEntityManager()->GetEntitiesWithType(sfge::ComponentType::BODY2D);
	for (auto entity : entities)
	{
		bodies.push_back(bodiesManager->GetComponentPtr(entity));
		initialPositions.push_back(bodies.back()->GetPosition());
		initialVelocities.push_back(bodies.back()->GetLinearVelocity());
		shapes.push_back(shapeManager->GetComponentPtr(entity));
		initialColors.push_back(shapes.back()->GetShape()->getFillColor());
	}
}

void sfge::ext::ResetSceneSystem::OnUpdate(float dt)
{
	if (inputManager->GetKeyboardManager().IsKeyDown(sf::Keyboard::Key::R))
	{
		for (size_t i = 0; i < bodies.size(); i++)
		{
			bodies[i]->SetPosition(initialPositions[i]);
			bodies[i]->SetLinearVelocity(initialVelocities[i]);
			shapes[i]->SetFillColor(initialColors[i]);
		}
	}
}
