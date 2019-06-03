#ifndef DRAW_QUADTREE_H
#define DRAW_QUADTREE_H

#include <engine/system.h>
#include <engine/engine.h>
// #include <vector>
#include <p2world.h>
#include <graphics/graphics2d.h>
#include <physics/physics2d.h>

namespace sfge::ext
{
	class DrawQuadTree : public System
	{
	public:
		DrawQuadTree(Engine& engine);
		void OnEngineInit() override;
		void OnDraw() override;

	private:
		p2World* world;
		std::vector<p2AABB> aabbs;
		Graphics2dManager* graphicsManager;
	};
}

#endif