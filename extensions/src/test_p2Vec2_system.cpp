#include <extensions/test_p2Vec2_system.h>

void sfge::ext::TestP2Vec2System::OnEngineInit()
{
	graphicsManager = m_Engine.GetGraphics2dManager();
	inputManager = m_Engine.GetInputManager();
}

void sfge::ext::TestP2Vec2System::OnUpdate(float dt)
{
	// Code taken from: https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
	auto& keyboardManager = inputManager->GetKeyboardManager();
	if (keyboardManager.IsKeyHeld(sf::Keyboard::Key::LControl))
	{
		input |= 1 << 5;
	}
	else
	{
		input &= ~(1 << 5);
	}
	if (keyboardManager.IsKeyHeld(sf::Keyboard::Key::LShift))
	{
		input |= 1 << 4;
	}
	else
	{
		input &= ~(1 << 4);
	}
	if (keyboardManager.IsKeyHeld(sf::Keyboard::Key::Left))
	{
		input |= 1 << 3;
	}
	else
	{
		input &= ~(1 << 3);
	}
	if (keyboardManager.IsKeyHeld(sf::Keyboard::Key::Right))
	{
		input |= 1 << 2;
	}
	else
	{
		input &= ~(1 << 2);
	}
	if (keyboardManager.IsKeyHeld(sf::Keyboard::Key::Up))
	{
		input |= 1 << 1;
	}
	else
	{
		input &= ~(1 << 1);
	}
	if (keyboardManager.IsKeyHeld(sf::Keyboard::Key::Down))
	{
		input |= 1;
	}
	else
	{
		input &= ~(1);
	}
}

void sfge::ext::TestP2Vec2System::OnFixedUpdate()
{
	// Handle inputs.
	if ((input >> 5) & 1)
	{
		// Divide vector by 2.
		vectorToDraw /= 2.0f;
	}
	if ((input >> 4) & 1)
	{
		// Multiply vector by 2.
		vectorToDraw *= 2.0f;
	}
	if ((input >> 3) & 1)
	{
		// Substract (1,0) from vector.
		vectorToDraw -= unitaryVectors[0];
	}
	if ((input >> 2) & 1)
	{
		// Add (1,0) to vector.
		vectorToDraw += unitaryVectors[0];
	}
	if ((input >> 1) & 1)
	{
		// Substract (0,1) from vector.
		vectorToDraw -= unitaryVectors[1];
	}
	if ((input) & 1)
	{
		// Add (0,1) to vector.
		vectorToDraw += unitaryVectors[1];
	}

	// Update projection.
	p2Mat22 segment(SCREEN_CENTER, SCREEN_CENTER + vectorToDraw);
	projectionToDraw = segment.ProjectSelfOnto(axis);
}

void sfge::ext::TestP2Vec2System::OnDraw()
{
	graphicsManager->DrawLine(AXIS_LINE[0], AXIS_LINE[1], sf::Color::Green);
	graphicsManager->DrawVector(vectorToDraw.ToGraphicSpace(), SCREEN_CENTER.ToGraphicSpace());
	graphicsManager->DrawLine(projectionToDraw.rows[0].ToGraphicSpace(), projectionToDraw.rows[1].ToGraphicSpace());
}
