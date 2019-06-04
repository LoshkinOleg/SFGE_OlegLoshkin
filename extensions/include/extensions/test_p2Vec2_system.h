#ifndef TEST_P2VEC2_SYSTEM_H
#define TEST_P2VEC2_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <p2vector.h>
#include <p2matrix.h>
#include <graphics/graphics2d.h>
#include <input/input.h>

namespace sfge::ext
{
	class TestP2Vec2System : public System
	{
	public:
		TestP2Vec2System(Engine& engine) : System(engine) {};

		void OnEngineInit() override;
		void OnUpdate(float dt) override;
		void OnFixedUpdate() override;
		void OnDraw() override;

	private:
		Graphics2dManager* graphicsManager;
		InputManager* inputManager;
		p2Vec2 unitaryVectors[2]{ p2Vec2(1,0), p2Vec2(0,1) };
		p2Vec2 vectorToDraw = p2Vec2{1,1};
		p2Vec2 axis = p2Vec2(1280,720).Normalized();
		p2Mat22 projectionToDraw;
		__int8 input; // Last bit = down, last bit - 1 = up, last bit - 2 = right, last bit - 3 = left, last bit - 4 = LShift, last bit - 5 = LCtrl.
		const p2Vec2 SCREEN_CENTER{12.8 * 0.5f, 7.2 * 0.5f};
		const Vec2f AXIS_LINE[2]{ Vec2f{0,0}, Vec2f{1280,720} };
	};
}

#endif