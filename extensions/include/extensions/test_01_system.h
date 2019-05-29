#ifndef TEST_01_SYSTEM_H
#define TEST_01_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <p2vector.h>

namespace sfge::ext
{
	class Test_01_System : public System
	{
	public:
		Test_01_System(Engine& engine);

		void OnEngineInit() override;
		void OnFixedUpdate() override;
		void OnDraw() override;

	private:
		p2Vec2 physicalVectors[2]{ p2Vec2(0.01f,0), p2Vec2(0,0.01f) };
		p2Vec2 vectToDraw{ 0.01f,0.01f };
		Vec2f screenSize;
		Graphics2dManager* graphicsManager;
		InputManager* inputManager;
	};
}

#endif