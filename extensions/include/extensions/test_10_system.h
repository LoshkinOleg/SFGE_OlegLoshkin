#ifndef TEST_10_SYSTEM_H
#define TEST_10_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <physics/physics2d.h>

namespace sfge::ext
{
	class Test_10_System : public System
	{
	public:
		Test_10_System(Engine& engine);

		void OnEngineInit() override;
		// void OnUpdate(float dt) override;
		void OnFixedUpdate() override;
		// void OnDraw() override;
		// void OnEditorDraw() override;
		// void Destroy() override;
		// void OnBeforeSceneLoad() override;
		// void OnAfterSceneLoad() override;
		// void OnContact(ColliderData* c1, ColliderData* c2, bool enter) override;

	private:
		Graphics2dManager* graphicsManager;
		std::vector<Body2d*> bodies;
	};
}

#endif