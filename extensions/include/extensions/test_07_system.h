#ifndef TEST_07_SYSTEM_H
#define TEST_07_SYSTEM_H

#include <vector>
#include <engine/system.h>
#include <engine/engine.h>
#include <physics/physics2d.h>
#include <graphics/graphics2d.h>
#include <p2aabb.h>

namespace sfge::ext
{
	class Test_07_System : public System
	{
	public:
		Test_07_System(Engine& engine);

		void OnEngineInit() override;
		// void OnUpdate(float dt) override;
		void OnFixedUpdate() override;
		void OnDraw() override;
		// void OnEditorDraw() override;
		// void Destroy() override;
		// void OnBeforeSceneLoad() override;
		// void OnAfterSceneLoad() override;
		void OnContact(ColliderData* c1, ColliderData* c2, bool enter) override;

	private:
		struct CollisionCount
		{
			Shape* shape;
			int contactCount;
		};

		Graphics2dManager* graphicsManager;
		ShapeManager* shapeManager;
		std::vector<Body2d*> bodies;
		std::vector<p2AABB> quadAabbs;
		std::map<p2Collider*, CollisionCount> collisions;
		p2World* world;
	};
}

#endif