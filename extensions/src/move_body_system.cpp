#include <extensions/move_body_system.h>

void sfge::ext::MoveBodySystem::OnEngineInit()
{
	inputManager = m_Engine.GetInputManager();

	bodyToMove = m_Engine.GetPhysicsManager()->GetBodyManager()->GetComponentPtr(m_Engine.GetEntityManager()->GetEntityByName("BodyToMove"));
}

void sfge::ext::MoveBodySystem::OnUpdate(float dt)
{
	// Code taken from: https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
	auto& keyboardManager = inputManager->GetKeyboardManager();
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

void sfge::ext::MoveBodySystem::OnFixedUpdate()
{
	if (input == 0)
	{
		bodyToMove->SetLinearVelocity(p2Vec2());
	}
	else
	{
		p2Vec2 currentVelocity = bodyToMove->GetLinearVelocity();
		if ((input >> 3) & 1)
		{
			bodyToMove->SetLinearVelocity(currentVelocity + p2Vec2(-1 * DELTA_TIME,0));
		}
		currentVelocity = bodyToMove->GetLinearVelocity();
		if ((input >> 2) & 1)
		{
			bodyToMove->SetLinearVelocity(currentVelocity + p2Vec2(1 * DELTA_TIME, 0));
		}
		currentVelocity = bodyToMove->GetLinearVelocity();
		if ((input >> 1) & 1)
		{
			bodyToMove->SetLinearVelocity(currentVelocity + p2Vec2(0, -1 * DELTA_TIME));
		}
		currentVelocity = bodyToMove->GetLinearVelocity();
		if ((input) & 1)
		{
			bodyToMove->SetLinearVelocity(currentVelocity + p2Vec2(0, 1 * DELTA_TIME));
		}
	}
}
