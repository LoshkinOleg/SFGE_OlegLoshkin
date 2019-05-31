#include <extensions/test_06_system.h>
#include <p2aabb.h>
#include <input/input.h>

sfge::ext::Test_06_System::Test_06_System(Engine& engine) : System(engine)
{

}

void sfge::ext::Test_06_System::OnEngineInit()
{
	graphicsManager = m_Engine.GetGraphics2dManager();
	inputManager = m_Engine.GetInputManager();
	rect = m_Engine.GetPhysicsManager()->GetBodyManager()->GetComponentPtr(m_Engine.GetEntityManager()->GetEntityByName("Rect"));
	circle = m_Engine.GetPhysicsManager()->GetBodyManager()->GetComponentPtr(m_Engine.GetEntityManager()->GetEntityByName("Circle"));
	rectShape = graphicsManager->GetShapeManager()->GetComponentPtr(m_Engine.GetEntityManager()->GetEntityByName("Rect"));
	circleShape = graphicsManager->GetShapeManager()->GetComponentPtr(m_Engine.GetEntityManager()->GetEntityByName("Circle"));

}

void sfge::ext::Test_06_System::OnUpdate(float dt)
{
	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Left))
	{
		keyboardInput |= 1 << 3;
	}
	else
	{
		keyboardInput &= ~(1 << 3);
	}

	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Right))
	{
		keyboardInput |= 1 << 2;
	}
	else
	{
		keyboardInput &= ~(1 << 2);
	}

	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Up))
	{
		keyboardInput |= 1 << 1;
	}
	else
	{
		keyboardInput &= ~(1 << 1);
	}

	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Down))
	{
		keyboardInput |= 1 << 0;
	}
	else
	{
		keyboardInput &= ~(1 << 0);
	}
}

void sfge::ext::Test_06_System::OnFixedUpdate()
{
	// X axis.
	if ((keyboardInput >> 3) & 1)
	{
		rect->ApplyForce(p2Vec2(-1,0));
	}
	if ((keyboardInput >> 2) & 1)
	{
		rect->ApplyForce(p2Vec2(1, 0));
	}
	// Y axis.
	if ((keyboardInput >> 1) & 1)
	{
		rect->ApplyForce(p2Vec2(0, -1));
	}
	if ((keyboardInput >> 0) & 1)
	{
		rect->ApplyForce(p2Vec2(0, 1));
	}
	// Reset velocity.
	if (keyboardInput == 0)
	{
		rect->SetLinearVelocity(p2Vec2());
	}
}

void sfge::ext::Test_06_System::OnDraw()
{
	graphicsManager->DrawCircle(circle->GetPosition().ToGraphicSpace(), circle->GetBody()->GetCollider()->GetShape()->GetSize().x * 100);
	graphicsManager->DrawBox(circle->GetPosition().ToGraphicSpace(), circle->GetAabb().GetExtends().ToGraphicSpace() * 2);
	graphicsManager->DrawBox(rect->GetPosition().ToGraphicSpace(), rect->GetAabb().GetExtends().ToGraphicSpace() * 2);

	if (circle->GetAabb().Overlaps(rect->GetAabb()))
	{
		rectShape->SetFillColor(sf::Color::Green);
		circleShape->SetFillColor(sf::Color::Green);
	}
	else
	{
		rectShape->SetFillColor(sf::Color::White);
		circleShape->SetFillColor(sf::Color::White);
	}
}
