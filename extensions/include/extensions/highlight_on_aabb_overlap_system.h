#ifndef HIGHLIGHT_ON_AABB_OVERLAP_SYSTEM_H
#define HIGHLIGHT_ON_AABB_OVERLAP_SYSTEM_H

#include <vector>
#include <engine/system.h>
#include <engine/engine.h>
#include <physics/physics2d.h>
#include <graphics/graphics2d.h>

namespace sfge::ext
{
	class HighlightOnAabbOverlapSystem : public System
	{
	public:
		HighlightOnAabbOverlapSystem(Engine& engine) : System(engine) {};

		void OnEngineInit() override;
		void OnDraw() override;
		void OnContact(ColliderData* c1, ColliderData* c2, bool enter) override;

	private:
		struct CollisionCount
		{
			Shape* shape = nullptr;
			int contactCount = 0;
		};

		Graphics2dManager* graphicsManager = nullptr;
		ShapeManager* shapeManager = nullptr;
		std::map<p2Collider*, CollisionCount> collisions = std::map<p2Collider*, CollisionCount>();
	};
}

#endif