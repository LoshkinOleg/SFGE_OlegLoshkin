#include <extensions/test_05_system.h>
#include <physics/body2d.h>

sfge::ext::Test_05_System::Test_05_System(Engine& engine): System(engine)
{
}

void sfge::ext::Test_05_System::OnEngineInit()
{
	graphicsManager = m_Engine.GetGraphics2dManager();

	auto dynamicEntity = m_Engine.GetEntityManager()->GetEntityByName("Dynamic");
	auto kinematicEntity = m_Engine.GetEntityManager()->GetEntityByName("Kinematic");
	auto staticEntity = m_Engine.GetEntityManager()->GetEntityByName("Static");
	dynamic = m_Engine.GetPhysicsManager()->GetBodyManager()->GetComponentPtr(dynamicEntity);
	kinematic = m_Engine.GetPhysicsManager()->GetBodyManager()->GetComponentPtr(kinematicEntity);
	stat = m_Engine.GetPhysicsManager()->GetBodyManager()->GetComponentPtr(staticEntity);
}

void sfge::ext::Test_05_System::OnFixedUpdate()
{
	if (dynamic->GetPosition().y >= yPosTrigger[1])
	{
		dynamic->SetLinearVelocity(p2Vec2());
		dynamic->ApplyForce(p2Vec2(0,-1) * forceMagnitude);
		drawTimer[0] = 0.25f;
	}
	if (kinematic->GetPosition().y >= yPosTrigger[1])
	{
		kinematic->SetLinearVelocity(p2Vec2());
		kinematic->ApplyForce(p2Vec2(0, -1) * forceMagnitude);
		drawTimer[1] = 0.25f;
	}
	else if (kinematic->GetPosition().y <= yPosTrigger[0])
	{
		kinematic->SetLinearVelocity(p2Vec2());
		kinematic->ApplyForce(p2Vec2(0, 1) * forceMagnitude);
		drawTimer[1] = 0.25f;
	}
	if (drawTimer[2] < 0)
	{
		stat->SetLinearVelocity(p2Vec2());
		stat->ApplyForce(p2Vec2(0, -1) * forceMagnitude);
		drawTimer[2] = 1;
	}
	drawTimer[0] -= 0.02f;
	drawTimer[1] -= 0.02f;
	drawTimer[2] -= 0.02f;
}

void sfge::ext::Test_05_System::OnDraw()
{
	if (drawTimer[0] > 0)
	{
		graphicsManager->DrawVector((p2Vec2(0,-1) * forceMagnitude).ToGraphicSpace(), dynamic->GetPosition().ToGraphicSpace(), sf::Color::Red);
	}
	if (drawTimer[1] > 0)
	{
		graphicsManager->DrawVector((p2Vec2(0, kinematic->GetLinearVelocity().y > 0 ? 1 : -1) * forceMagnitude).ToGraphicSpace(), kinematic->GetPosition().ToGraphicSpace(), sf::Color::Red);
	}
	if (drawTimer[1] > 0)
	{
		graphicsManager->DrawVector((p2Vec2(0, -1) * forceMagnitude).ToGraphicSpace(), stat->GetPosition().ToGraphicSpace(), sf::Color::Red);
	}
}
