#include <extensions/test_01_system.h>
#include <graphics/graphics2d.h>
#include <input/input.h>

sfge::ext::Test_01_System::Test_01_System(Engine& engine) : System(engine)
{

}

void sfge::ext::Test_01_System::OnEngineInit()
{
	// Get managers.
	graphicsManager = m_Engine.GetGraphics2dManager();
	inputManager = m_Engine.GetInputManager();

	sf::Vector2i gottenScreenRes = m_Engine.GetConfig()->screenResolution;
	screenSize = Vec2f(gottenScreenRes.x, gottenScreenRes.y) * 0.5f;
}

void sfge::ext::Test_01_System::OnFixedUpdate()
{
	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Right))
	{
		vectToDraw += physicalVectors[0] * MULTIPLIER;
	}
	else if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Left))
	{
		vectToDraw -= physicalVectors[0] * MULTIPLIER;
	}
	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Up))
	{
		vectToDraw -= physicalVectors[1] * MULTIPLIER;
	}
	else if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Down))
	{
		vectToDraw += physicalVectors[1] * MULTIPLIER;
	}
}

void sfge::ext::Test_01_System::OnDraw()
{
	graphicsManager->DrawVector(vectToDraw.ToGraphicSpace(), screenSize, sf::Color::Red);
}
