#ifndef TEST_03_SYSTEM_H
#define TEST_03_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <p2matrix.h>

namespace sfge::ext
{
	class Test_03_System : public System
	{
	public:
		Test_03_System(Engine& engine);

		void OnEngineInit() override;
		void OnUpdate(float dt) override;
		// void OnFixedUpdate() override;
		void OnDraw() override;
		// void OnEditorDraw() override;
		// void Destroy() override;
		// void OnBeforeSceneLoad() override;
		// void OnAfterSceneLoad() override;
		// void OnContact(ColliderData* c1, ColliderData* c2, bool enter) override;

	private:
		const int MULTIPLIER = 5;
		p2Vec2 axis{1.0f,0.5f};
		p2Vec2 physicalVectors[2]{ p2Vec2(1,0), p2Vec2(0,1) };
		p2Vec2 vectToDraw = p2Vec2(1.0f,1.0f);
		p2Mat22 projection;
		Vec2f screenSize;
		p2Vec2 screenCenter;
		Graphics2dManager* graphicsManager;
		InputManager* inputManager;
	};
}

#endif