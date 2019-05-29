#include <extensions/test_04_system.h>
#include <graphics/graphics2d.h>
#include <input/input.h>

sfge::ext::Test_04_System::Test_04_System(Engine& engine) : System(engine)
{

}

void sfge::ext::Test_04_System::OnEngineInit()
{
	// Get managers.
	graphicsManager = m_Engine.GetGraphics2dManager();
	inputManager = m_Engine.GetInputManager();
}

void sfge::ext::Test_04_System::OnUpdate(float dt)
{
	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Right))
	{
		t += dt;
		if (t > 1) t = 1;
	}
	else if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Left))
	{
		t -= dt;
		if (t < 0) t = 0;
	}
}

void sfge::ext::Test_04_System::OnFixedUpdate()
{
	vectorToLerp = p2Vec2::Lerp(v,u,t);
}

void sfge::ext::Test_04_System::OnDraw()
{
	graphicsManager->DrawVector(v.ToGraphicSpace(), Vec2f(1,1), sf::Color::Green);
	graphicsManager->DrawVector(u.ToGraphicSpace(), Vec2f(1,1), sf::Color::Green);
	graphicsManager->DrawVector(vectorToLerp.ToGraphicSpace(), Vec2f(1,1), sf::Color::Red);
}