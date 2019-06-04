#include <extensions/draw_quadtree_system.h>

void sfge::ext::DrawQuadTreeSystem::OnEngineInit()
{
	graphicsManager = m_Engine.GetGraphics2dManager();

	world = m_Engine.GetPhysicsManager()->GetWorld_RawPtr();
}

void sfge::ext::DrawQuadTreeSystem::OnFixedUpdate()
{
	bounds = world->GetQuadTreeBounds();
}

void sfge::ext::DrawQuadTreeSystem::OnDraw()
{
	for (p2AABB& bound : bounds)
	{
		graphicsManager->DrawBox(bound.GetCenter().ToGraphicSpace(), bound.GetExtends().ToGraphicSpace() * 2);
	}
}
