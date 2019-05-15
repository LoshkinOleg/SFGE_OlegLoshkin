#include <p2quadtree.h>
#include <iostream>

p2QuadTree::p2QuadTree()
{
	m_NodeLevel = -1;
	m_Bounds = p2AABB();
	nodes[0] = nullptr;
	nodes[1] = nullptr;
	nodes[2] = nullptr;
	nodes[3] = nullptr;
	m_Objects = std::make_unique<std::vector<p2Body*>>();
	hasChildren = false;
}

p2QuadTree::p2QuadTree(int nodeLevel, p2AABB bounds)
{
	m_NodeLevel = nodeLevel;
	m_Bounds = bounds;
	nodes[0] = nullptr;
	nodes[1] = nullptr;
	nodes[2] = nullptr;
	nodes[3] = nullptr;
	m_Objects = std::make_unique<std::vector<p2Body*>>();
	hasChildren = false;
}

p2QuadTree::~p2QuadTree()
{
	Clear();
}

p2QuadTree& p2QuadTree::operator=(p2QuadTree & other)
{
	m_NodeLevel = other.m_NodeLevel;
	m_Bounds = other.m_Bounds;
	hasChildren = other.hasChildren;
	nodes[0] = std::move(other.nodes[0]);
	nodes[1] = std::move(other.nodes[1]);
	nodes[2] = std::move(other.nodes[2]);
	nodes[3] = std::move(other.nodes[3]);
	m_Objects = std::move(other.m_Objects);
	return *this;
}

void p2QuadTree::Clear()
{
	// Clear children.
	if (hasChildren)
	{
		for (int i = 0; i < CHILD_TREE_NMB; i++)
		{
			nodes[i]->Clear();
		}
	}
	// Clear objects list if current Node is root Node since it won't be deleted thus not triggering m_Objects deallocation automatically.
	if (m_NodeLevel == 0 && m_Objects != nullptr)
	{
		m_Objects->clear();
		hasChildren = false;
	}
}

void p2QuadTree::Split()
{	
	hasChildren = true;

	// Create new instances of quadtrees and initialize them.
	p2AABB newAabb = p2AABB();
	for (int i = 0; i < CHILD_TREE_NMB; i++)
	{
		nodes[i] = std::make_unique<p2QuadTree>();
		nodes[i]->m_NodeLevel = m_NodeLevel + 1;
	}
	// TopLeft's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft	+ p2Vec2(0,							- m_Bounds.GetExtends().y));
	newAabb.topRight	= p2Vec2(m_Bounds.topRight		+ p2Vec2(- m_Bounds.GetExtends().x,	0));
	nodes[0]->m_Bounds	= newAabb;
	// TopRight's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft	+ p2Vec2(m_Bounds.GetExtends().x,	-m_Bounds.GetExtends().y));
	newAabb.topRight	= p2Vec2(m_Bounds.topRight);
	nodes[1]->m_Bounds	= newAabb;
	// BottomLeft's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft);
	newAabb.topRight	= p2Vec2(m_Bounds.topRight		+ p2Vec2(- m_Bounds.GetExtends().x,	m_Bounds.GetExtends().y));
	nodes[2]->m_Bounds	= newAabb;
	// BottomRight's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft	+ p2Vec2(m_Bounds.GetExtends().x,	0));
	newAabb.topRight	= p2Vec2(m_Bounds.topRight		+ p2Vec2(0,							m_Bounds.GetExtends().y));
	nodes[3]->m_Bounds	= newAabb;
}

int p2QuadTree::GetIndex(p2Body* rect)
{
	return 0;
}

void p2QuadTree::Insert(p2Body* obj)
{
	if (obj->IsInit()) // Ignore all bodies that aren't used.
	{
		if (!hasChildren) // If quad has no children.
		{
			if (m_Objects->size() < MAX_OBJECTS) // If there's still room for insertion in this node.
			{
				m_Objects->push_back(obj); // Add body to this node's bodies list.
			}
			else // Else split quad and insert body there.
			{
				if (m_NodeLevel + 1 <= MAX_LEVELS) // If we still can split quads.
				{
					Split();

					// Fill out children with bodies aleready contained within this node.
					std::vector<p2Body*> bodiesRefCopy = *m_Objects.get(); // Copy ptrs for analysis.
					m_Objects->clear(); // And clear body's list.
					for (p2Body* body : bodiesRefCopy) // For each body.
					{
						// Find all children that overlap current body.
						std::vector<p2QuadTree*> matchingChildren = std::vector<p2QuadTree*>();
						for (int i = 0; i < CHILD_TREE_NMB; i++)
						{
							if (nodes[i]->m_Bounds.Overlaps(body->GetAabb())) matchingChildren.push_back(nodes[i].get());
						}
						if (matchingChildren.size() < 2) // If body only overlaps one quad.
						{
							matchingChildren[0]->Insert(body); // Insert body there.
						}
						else
						{
							m_Objects->push_back(body); // Else add body back to this quad.
						}
					}

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
						m_Objects->push_back(obj);
					}
				}
				else // Can't split any more. Add body to this quad.
				{
					m_Objects->push_back(obj);
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
				m_Objects->push_back(obj);
			}
		}
		
	}

}

std::vector<p2Body*> p2QuadTree::Retrieve() const
{
	return *m_Objects;
}

void p2QuadTree::GetQuadTreesAabbs(std::vector<p2AABB>& listToFill) const
{
	listToFill.push_back(m_Bounds);
	if (hasChildren)
	{
		nodes[0]->GetQuadTreesAabbs(listToFill);
		nodes[1]->GetQuadTreesAabbs(listToFill);
		nodes[2]->GetQuadTreesAabbs(listToFill);
		nodes[3]->GetQuadTreesAabbs(listToFill);
	}
}

void p2QuadTree::LogQuadsBodyCount() const
{
	std::cout << "Quad at level: " << m_NodeLevel << " : " << m_Objects->size() << " bodies." << std::endl;
	if (hasChildren)
	{
		nodes[0]->LogQuadsBodyCount();
		nodes[1]->LogQuadsBodyCount();
		nodes[2]->LogQuadsBodyCount();
		nodes[3]->LogQuadsBodyCount();
	}
}
