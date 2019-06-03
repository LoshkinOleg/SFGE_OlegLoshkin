#include <extensions/draw_quadtree.h>

sfge::ext::DrawQuadTree::DrawQuadTree(Engine& engine) : System(engine)
{}

void sfge::ext::DrawQuadTree::OnEngineInit()
{
	graphicsManager = m_Engine.GetGraphics2dManager();
	world = m_Engine.GetPhysicsManager()->GetWorld_RawPtr();
}

void sfge::ext::DrawQuadTree::OnDraw()
{
	aabbs = world->GetQuadTreeBounds();
	for (auto& bound : aabbs)
	{
		graphicsManager->DrawBox(bound.GetCenter().ToGraphicSpace(), bound.GetExtends().ToGraphicSpace() * 2);
	}
}
