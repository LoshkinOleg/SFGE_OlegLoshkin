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
			Shape* shape;
			int contactCount;
		};

		Graphics2dManager* graphicsManager;
		ShapeManager* shapeManager;
		std::map<p2Collider*, CollisionCount> collisions;
	};
}

#endif