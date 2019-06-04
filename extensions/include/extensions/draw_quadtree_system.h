#ifndef DRAW_QUADTREE_SYSTEM_H
#define DRAW_QUADTREE_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <graphics/graphics2d.h>
#include <physics/physics2d.h>
#include <vector>
#include <p2world.h>
// #include <p2aabb.h>

namespace sfge::ext
{
	class DrawQuadTreeSystem : public System
	{
	public:
		DrawQuadTreeSystem(Engine& engine) : System(engine) {};

		void OnEngineInit() override;
		void OnFixedUpdate() override;
		void OnDraw() override;

	private:
		Graphics2dManager* graphicsManager;
		p2World* world;
		std::vector<p2AABB> bounds;
	};
}

#endif