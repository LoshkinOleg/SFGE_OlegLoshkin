#include "..\include\p2quadtree.h"

p2QuadTree::p2QuadTree()
{
	m_NodeLevel = -1;
	m_Bounds = p2AABB();
}

p2QuadTree::p2QuadTree(int nodeLevel, p2AABB bounds)
{
	m_NodeLevel = nodeLevel;
	m_Bounds = bounds;
}

p2QuadTree::~p2QuadTree()
{
}

void p2QuadTree::Clear()
{
}

void p2QuadTree::Split()
{
	// Create new instances of quadtrees and initialize them.
	p2AABB newAabb = p2AABB();
	for (int i = 0; i < CHILD_TREE_NMB; ++i)
	{
		nodes[i] = std::make_unique<p2QuadTree>();
		nodes[i]->m_NodeLevel = m_NodeLevel + 1;
	}
	// TopLeft's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft	- p2Vec2(0,							m_Bounds.GetExtends().y));
	newAabb.topRight	= p2Vec2(m_Bounds.topRight		- p2Vec2(m_Bounds.GetExtends().x,	0));
	nodes[0]->m_Bounds	= newAabb;
	// TopRight's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft	+ p2Vec2(m_Bounds.GetExtends().x,	-m_Bounds.GetExtends().y));
	newAabb.topRight	= p2Vec2(m_Bounds.topRight);
	nodes[1]->m_Bounds	= newAabb;
	// BottomLeft's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft);
	newAabb.topRight	= p2Vec2(m_Bounds.topRight		- p2Vec2(m_Bounds.GetExtends().x,	m_Bounds.GetExtends().y));
	nodes[2]->m_Bounds	= newAabb;
	// BottomRight's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft	+ p2Vec2(m_Bounds.GetExtends().x,	0));
	newAabb.topRight	= p2Vec2(m_Bounds.topRight		+ p2Vec2(0,							m_Bounds.GetExtends().y));
	nodes[3]->m_Bounds	= newAabb;
}

int p2QuadTree::GetIndex(p2Body * rect)
{
	return 0;
}

void p2QuadTree::Insert(p2Body* obj)
{
	if (nodes == nullptr) // If quad has no children.
	{
		if (m_Objects.size() < MAX_OBJECTS) // If there's still room for insertion in this node.
		{
			m_Objects.push_back(obj); // Add body to this node's bodies list.
		}
		else // Else split quad and insert body there.
		{
			if (m_NodeLevel + 1 <= MAX_LEVELS) // If we still can split quads.
			{
				Split();

				// Check the body isn't overlapping two children quads.
				std::vector<p2QuadTree*> overlappingQuads = std::vector<p2QuadTree*>();
				for (int i = 0; i < 4; i++)
				{
					if (nodes[i]->m_Bounds.Overlaps(obj->GetAabb())) overlappingQuads.push_back(nodes[i].get());
				}
				if (overlappingQuads.size() < 2)
				{
					overlappingQuads[0]->Insert(obj); // It doesn't, insert it there.
				}
				else // It does overlap multiple quads, insert body to this quad's list instead.
				{
					m_Objects.push_back(obj);
				}
			}
			else // Can't split any more. Add body to this quad.
			{
				m_Objects.push_back(obj);
			}
		}
	}
	else // If the quad does have children.
	{
		// Check the body isn't overlapping two children quads.
		std::vector<p2QuadTree*> overlappingQuads = std::vector<p2QuadTree*>();
		for (int i = 0; i < 4; i++)
		{
			if (nodes[i]->m_Bounds.Overlaps(obj->GetAabb())) overlappingQuads.push_back(nodes[i].get());
		}
		if (overlappingQuads.size() < 2)
		{
			overlappingQuads[0]->Insert(obj); // It doesn't, insert it there.
		}
		else // It does overlap multiple quads, insert body to this quad's list instead.
		{
			m_Objects.push_back(obj);
		}
	}
}

void p2QuadTree::Retrieve()
{
}
