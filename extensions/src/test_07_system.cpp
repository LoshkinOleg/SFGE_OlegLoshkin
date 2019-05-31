#include <extensions/test_07_system.h>
#include <p2aabb.h>
#include <input/input.h>

sfge::ext::Test_07_System::Test_07_System(Engine& engine) : System(engine)
{

}

void sfge::ext::Test_07_System::OnEngineInit()
{
	graphicsManager = m_Engine.GetGraphics2dManager();
	shapeManager = graphicsManager->GetShapeManager();

	auto* entityManager = m_Engine.GetEntityManager();
	auto* bodyManager = m_Engine.GetPhysicsManager()->GetBodyManager();
	auto* colliderManager = m_Engine.GetPhysicsManager()->GetColliderManager();
	auto bodiesEntities = entityManager->GetEntitiesWithType(sfge::ComponentType::BODY2D);
	auto colliderEntities = entityManager->GetEntitiesWithType(sfge::ComponentType::COLLIDER2D);
	auto shapeEntities = entityManager->GetEntitiesWithType(sfge::ComponentType::SHAPE2D);

	for (size_t i = 0; i < bodiesEntities.size(); i++)
	{
		bodies.push_back(bodyManager->GetComponentPtr(bodiesEntities[i]));
	}
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

	world = m_Engine.GetPhysicsManager()->GetWorld_RawPtr();
}

void sfge::ext::Test_07_System::OnFixedUpdate()
{
	quadAabbs = world->GetQuadTreeBounds();

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

void sfge::ext::Test_07_System::OnDraw()
{
	for (p2AABB& bound : quadAabbs)
	{
		graphicsManager->DrawBox(bound.GetCenter().ToGraphicSpace(), bound.GetExtends().ToGraphicSpace() * 2);
	}
	/*
	// Code found on https://stackoverflow.com/questions/15393102/go-through-map-c
	for (const auto& element : collisions)
	{
		if (element.second.contactCount > 0)
		{
			element.second.shape->SetFillColor(sf::Color::Green);
		}
		else
		{
			element.second.shape->SetFillColor(sf::Color::White);
		}
	}*/
}
/*
void sfge::ext::Test_07_System::OnContact(ColliderData* c1, ColliderData* c2, bool enter)
{
	if (enter)
	{
		collisions[c1->fixture].contactCount++;
	}
	else
	{
		collisions[c1->fixture].contactCount--;
	}
}*/
