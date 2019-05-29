#ifndef TEST_04_SYSTEM_H
#define TEST_04_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>

namespace sfge::ext
{
	class Test_04_System : public System
	{
	public:
		Test_04_System(Engine& engine);

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
		p2Vec2 vectorToLerp;
		p2Vec2 v{ 12.8f,0 };
		p2Vec2 u{ 0,7.2f };
		float t = 0;
		Graphics2dManager* graphicsManager;
		InputManager* inputManager;
	};
}

#endif