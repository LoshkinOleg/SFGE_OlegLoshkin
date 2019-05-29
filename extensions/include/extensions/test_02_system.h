#ifndef TEST_02_SYSTEM_H
#define TEST_02_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <p2vector.h>

namespace sfge::ext
{
	class Test_02_System : public System
	{
	public:
		Test_02_System(Engine& engine);

		void OnEngineInit() override;
		void OnFixedUpdate() override;
		void OnDraw() override;

	private:
		p2Vec2 vectToDraw{ 0.01f,0 };
		float screenSizeY;
		Graphics2dManager* graphicsManager;
		InputManager* inputManager;
	};
}

#endif