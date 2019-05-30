#ifndef TEST_05_SYSTEM_H
#define TEST_05_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <physics/physics2d.h>
#include <graphics/graphics2d.h>
#include <p2vector.h>
#include <p2body.h>

namespace sfge::ext
{
	class Test_05_System : public System
	{
	public:
		Test_05_System(Engine& engine);

		void OnEngineInit() override;
		// void OnUpdate(float dt) override;
		void OnFixedUpdate() override;
		void OnDraw() override;
		// void OnEditorDraw() override;
		// void Destroy() override;
		// void OnBeforeSceneLoad() override;
		// void OnAfterSceneLoad() override;
		// void OnContact(ColliderData* c1, ColliderData* c2, bool enter) override;

	private:
		float yPosTrigger[2]{ 7.2f / 3.0f, 7.2f * 2.0f / 3.0f };
		float drawTimer[3];
		float forceMagnitude = 3;
		Graphics2dManager* graphicsManager;
		Body2d* dynamic;
		Body2d* kinematic;
		Body2d* stat;
	};
}

#endif