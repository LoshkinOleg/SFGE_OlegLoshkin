#include <extensions/test_03_system.h>
#include <graphics/graphics2d.h>
#include <input/input.h>

sfge::ext::Test_03_System::Test_03_System(Engine& engine) : System(engine)
{

}

void sfge::ext::Test_03_System::OnEngineInit()
{
	// Get managers.
	graphicsManager = m_Engine.GetGraphics2dManager();
	inputManager = m_Engine.GetInputManager();

	sf::Vector2i gottenScreenRes = m_Engine.GetConfig()->screenResolution;
	screenSize = Vec2f(gottenScreenRes.x, gottenScreenRes.y);
	screenCenter = p2Vec2(screenSize.x * 0.01f, screenSize.y * 0.01f) * 0.5f;
}

void sfge::ext::Test_03_System::OnUpdate(float dt)
{
	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Right))
	{
		vectToDraw += physicalVectors[0];
		projection = p2Mat22(screenCenter, screenCenter + vectToDraw).ProjectSelfOnto(axis);
	}
	else if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Left))
	{
		vectToDraw -= physicalVectors[0];
		projection = p2Mat22(screenCenter, screenCenter + vectToDraw).ProjectSelfOnto(axis);
	}
	if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Up))
	{
		vectToDraw -= physicalVectors[1];
		projection = p2Mat22(screenCenter, screenCenter + vectToDraw).ProjectSelfOnto(axis);
	}
	else if (inputManager->GetKeyboardManager().IsKeyHeld(sf::Keyboard::Key::Down))
	{
		vectToDraw += physicalVectors[1];
		projection = p2Mat22(screenCenter, screenCenter + vectToDraw).ProjectSelfOnto(axis);
	}
}

void sfge::ext::Test_03_System::OnDraw()
{
	graphicsManager->DrawVector(vectToDraw.ToGraphicSpace(), screenCenter.ToGraphicSpace(), sf::Color::Red); // Modifiable vector.
	graphicsManager->DrawLine(Vec2f(0,0), axis.ToGraphicSpace() * 1000, sf::Color::Green); // Axis to project onto.
	graphicsManager->DrawLine(projection.rows[0].ToGraphicSpace(), projection.rows[1].ToGraphicSpace(), sf::Color::Red); // Projection.
}