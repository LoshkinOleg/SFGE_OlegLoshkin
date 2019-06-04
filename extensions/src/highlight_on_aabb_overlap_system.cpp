#include <extensions/highlight_on_aabb_overlap_system.h>

void sfge::ext::HighlightOnAabbOverlapSystem::OnEngineInit()
{
	graphicsManager = m_Engine.GetGraphics2dManager();
	shapeManager = graphicsManager->GetShapeManager();

	auto* entityManager = m_Engine.GetEntityManager();
	auto* bodyManager = m_Engine.GetPhysicsManager()->GetBodyManager();
	auto* colliderManager = m_Engine.GetPhysicsManager()->GetColliderManager();
	auto colliderEntities = entityManager->GetEntitiesWithType(sfge::ComponentType::COLLIDER2D);
	auto shapeEntities = entityManager->GetEntitiesWithType(sfge::ComponentType::SHAPE2D);

	std::vector<p2Collider*> colliders;
	for (size_t i = 0; i < colliderEntities.size(); i++)
	{
		colliders.push_back(colliderManager->GetComponentPtr(colliderEntities[i])->fixture);
	}
	std::vector<Shape*> shapes;
	for (size_t i = 0; i < shapeEntities.size(); i++)
	{
		shapes.push_back(shapeManager->GetComponentPtr(shapeEntities[i]));
	}
	for (size_t i = 0; i < colliders.size(); i++)
	{
		collisions.insert({ colliders[i], CollisionCount{shapes[i], 0} });
	}
}

void sfge::ext::HighlightOnAabbOverlapSystem::OnDraw()
{
	// Code found on https://stackoverflow.com/questions/15393102/go-through-map-c
	p2Vec2 extends;
	p2Vec2 center;
	for (const auto& element : collisions)
	{
		graphicsManager->DrawBox(element.first->GetAabb());

		if (element.second.contactCount > 0)
		{
			element.second.shape->SetFillColor(sf::Color::Green);
		}
		else
		{
			element.second.shape->SetFillColor(sf::Color::White);
		}
	}
}

void sfge::ext::HighlightOnAabbOverlapSystem::OnContact(ColliderData* c1, ColliderData* c2, bool enter)
{
	if (enter)
	{
		collisions[c1->fixture].contactCount++;
		collisions[c2->fixture].contactCount++;
	}
	else
	{
		collisions[c1->fixture].contactCount--;
		collisions[c2->fixture].contactCount--;
	}
}
