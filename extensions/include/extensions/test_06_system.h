#ifndef TEST_06_SYSTEM_H
#define TEST_06_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <physics/physics2d.h>
#include <graphics/graphics2d.h>

namespace sfge::ext
{
	class Test_06_System : public System
	{
	public:
		Test_06_System(Engine& engine);

		void OnEngineInit() override;
		void OnUpdate(float dt) override;
		void OnFixedUpdate() override;
		void OnDraw() override;
		// void OnEditorDraw() override;
		// void Destroy() override;
		// void OnBeforeSceneLoad() override;
		// void OnAfterSceneLoad() override;
		// void OnContact(ColliderData* c1, ColliderData* c2, bool enter) override;

	private:
		Graphics2dManager* graphicsManager;
		InputManager* inputManager;
		Body2d* rect;
		Body2d* circle;
		Shape* rectShape;
		Shape* circleShape;
		__int8 keyboardInput = 0;
	};
}

#endif