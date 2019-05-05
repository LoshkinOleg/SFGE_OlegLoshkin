#include <extensions\lerping_system.h>
#include <cmath>

#include <iostream>

using namespace sfge::ext;

// Constructor
LerpingSystem::LerpingSystem(Engine& engine) : System(engine){}

// Set up variables.
void LerpingSystem::OnEngineInit()
{
	m_v = p2Vec2(0,0.3f);
	m_u = p2Vec2(0.3f,0);
	m_t = 0.0f;
	m_result = m_u; // Set result to start off aligned with u.
	m_result_x = p2Vec2(m_result.x, 0);
	m_result_y = p2Vec2(0, m_result.y);
	m_fixed_dt = m_Engine.GetConfig()->fixedDeltaTime;
	m_graphics_manager = m_Engine.GetGraphics2dManager();
}

void LerpingSystem::OnFixedUpdate()
{
	// Lerp result between v and u. f(t) = cos(t)/2 + 1/2 is a sinusoidal function yielding results between 0 and 1 and a period of 2 PI.
	m_result = p2Vec2::Lerp(m_v, m_u, (_CMATH_::cos(M_SPEED_MULTIPLIER * m_t)/2.0f + (0.5f)));
	m_result_x = p2Vec2(0, m_result.y);
	m_result_y = p2Vec2(m_result.x, 0);
	m_t += m_fixed_dt;
}

void LerpingSystem::OnDraw()
{
	m_graphics_manager->DrawVector(meter2pixel(m_v), Vec2f(0, 0), sf::Color::Red);
	m_graphics_manager->DrawVector(meter2pixel(m_u), Vec2f(0, 0), sf::Color::Red);
	m_graphics_manager->DrawVector(meter2pixel(m_result), Vec2f(0, 0), sf::Color::Blue);
	m_graphics_manager->DrawVector(meter2pixel(m_result_x), Vec2f(meter2pixel(m_result.x) * 20,0), sf::Color::Cyan); // I've got no idea where the factors of 10 and 2 come from... but it works?
	m_graphics_manager->DrawVector(meter2pixel(m_result_y), Vec2f(0, meter2pixel(m_result.y) * 20), sf::Color::Cyan);
}