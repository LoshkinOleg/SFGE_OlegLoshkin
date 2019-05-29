#include <extensions/test_02_system.h>
#include <graphics/graphics2d.h>
#include <input/input.h>

sfge::ext::Test_02_System::Test_02_System(Engine& engine) : System(engine)
{

}

void sfge::ext::Test_02_System::OnEngineInit()
{
	// Get managers.
	graphicsManager = m_Engine.GetGraphics2dManager();
	inputManager = m_Engine.GetInputManager();

	screenSizeY = m_Engine.GetConfig()->screenResolution.y / 2.0f;
}

void sfge::ext::Test_02_System::OnFixedUpdate()
{
	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Right))
	{
		vectToDraw *= 2;
	}
	else if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Left))
	{
		vectToDraw /= 2;
	}
}

void sfge::ext::Test_02_System::OnDraw()
{
	graphicsManager->DrawVector(vectToDraw.ToGraphicSpace(), Vec2f(50, screenSizeY), sf::Color::Red);
}