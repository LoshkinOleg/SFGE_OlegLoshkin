#include <p2quadtree.h>
#include <iostream>

p2QuadTree::p2QuadTree()
{
	m_NodeLevel = -1;
	m_Bounds = p2AABB();
	m_Children[0] = nullptr;
	m_Children[1] = nullptr;
	m_Children[2] = nullptr;
	m_Children[3] = nullptr;
	m_Bodies = std::vector<p2Body*>();
	m_HasChildren = false;
}

p2QuadTree::p2QuadTree(int nodeLevel, p2AABB bounds, int childId = -1)
{
	m_NodeLevel = nodeLevel;
	m_Bounds = bounds;
	m_Children[0] = nullptr;
	m_Children[1] = nullptr;
	m_Children[2] = nullptr;
	m_Children[3] = nullptr;
	m_Bodies = std::vector<p2Body*>();
	m_HasChildren = false;
}

p2QuadTree::~p2QuadTree()
{
	// Clear();
}

p2QuadTree& p2QuadTree::operator=(p2QuadTree & other)
{
	m_NodeLevel = other.m_NodeLevel;
	m_Bounds = other.m_Bounds;
	m_HasChildren = other.m_HasChildren;
	m_Children[0] = std::move(other.m_Children[0]);
	m_Children[1] = std::move(other.m_Children[1]);
	m_Children[2] = std::move(other.m_Children[2]);
	m_Children[3] = std::move(other.m_Children[3]);
	m_Bodies = other.m_Bodies;
	return *this;
}

void p2QuadTree::Clear()
{
	// Clear children.
	if (m_HasChildren)
	{
		for (int i = 0; i < CHILD_TREE_NMB; i++)
		{
			m_Children[i]->Clear();
		}
		m_Children[0] = nullptr;
		m_Children[1] = nullptr;
		m_Children[2] = nullptr;
		m_Children[3] = nullptr;
	}
	// Clear objects list if current Node is root Node since it won't be deleted thus not triggering m_Objects deallocation automatically.
	if (m_NodeLevel == 0 && m_Bodies.size() > 0)
	{
		m_Bodies.clear();
	}
	m_HasChildren = false;
}

void p2QuadTree::Split()
{	
	m_HasChildren = true;

	// Create new instances of quadtrees and initialize them.
	p2AABB newAabb = p2AABB();
	for (int i = 0; i < CHILD_TREE_NMB; i++)
	{
		m_Children[i] = std::make_unique<p2QuadTree>();
		m_Children[i]->m_NodeLevel = m_NodeLevel + 1;
		m_Children[i]->m_Parent = this;
	}
	// TopLeft's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft	+ p2Vec2(0,							- m_Bounds.GetExtends().y));
	newAabb.topRight	= p2Vec2(m_Bounds.topRight		+ p2Vec2(- m_Bounds.GetExtends().x,	0));
	m_Children[0]->m_Bounds	= newAabb;
	// TopRight's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft	+ p2Vec2(m_Bounds.GetExtends().x,	-m_Bounds.GetExtends().y));
	newAabb.topRight	= p2Vec2(m_Bounds.topRight);
	m_Children[1]->m_Bounds	= newAabb;
	// BottomLeft's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft);
	newAabb.topRight	= p2Vec2(m_Bounds.topRight		+ p2Vec2(- m_Bounds.GetExtends().x,	m_Bounds.GetExtends().y));
	m_Children[2]->m_Bounds	= newAabb;
	// BottomRight's AABB.
	newAabb.bottomLeft	= p2Vec2(m_Bounds.bottomLeft	+ p2Vec2(m_Bounds.GetExtends().x,	0));
	newAabb.topRight	= p2Vec2(m_Bounds.topRight		+ p2Vec2(0,							m_Bounds.GetExtends().y));
	m_Children[3]->m_Bounds	= newAabb;
}

void p2QuadTree::Insert(p2Body* obj)
{
	if (obj->IsInit()) // Ignore all bodies that aren't used.
	{
		if (!m_HasChildren) // If quad has no children.
		{
			if (m_Bodies.size() < MAX_OBJECTS) // If there's still room for insertion in this node.
			{
				m_Bodies.push_back(obj); // Add body to this node's bodies list.
			}
			else // Else split quad and insert body there.
			{
				if (m_NodeLevel + 1 <= MAX_LEVELS) // If we still can split quads.
				{
					Split();

					// Fill out children with bodies aleready contained within this node.
					std::vector<p2Body*> bodiesRefCopy = m_Bodies; // Copy ptrs for analysis.
					m_Bodies.clear(); // And clear body's list.
					for (p2Body* body : bodiesRefCopy) // For each body.
					{
						// Find all children that overlap current body.
						std::vector<p2QuadTree*> matchingChildren = std::vector<p2QuadTree*>();
						for (int i = 0; i < CHILD_TREE_NMB; i++)
						{
							if (m_Children[i]->m_Bounds.Overlaps(body->GetAabb())) matchingChildren.push_back(m_Children[i].get());
						}
						if (matchingChildren.size() < 2 && matchingChildren.size() > 0) // If body only overlaps one quad.
						{
							matchingChildren[0]->Insert(body); // Insert body there.
						}
						else
						{
							m_Bodies.push_back(body); // Else add body back to this quad.
						}
					}

					// Check the body isn't overlapping two children quads.
					std::vector<p2QuadTree*> overlappingQuads = std::vector<p2QuadTree*>();
					for (int i = 0; i < 4; i++)
					{
						if (m_Children[i]->m_Bounds.Overlaps(obj->GetAabb())) overlappingQuads.push_back(m_Children[i].get());
					}
					if (overlappingQuads.size() < 2)
					{
						overlappingQuads[0]->Insert(obj); // It doesn't, insert it there.
					}
					else // It does overlap multiple quads, insert body to this quad's list instead.
					{
						m_Bodies.push_back(obj);
					}
				}
				else // Can't split any more. Add body to this quad.
				{
					m_Bodies.push_back(obj);
				}
			}
		}
		else // If the quad does have children.
		{
			// Check the body isn't overlapping two children quads.
			std::vector<p2QuadTree*> overlappingQuads = std::vector<p2QuadTree*>();
			for (int i = 0; i < 4; i++)
			{
				if (m_Children[i]->m_Bounds.Overlaps(obj->GetAabb())) overlappingQuads.push_back(m_Children[i].get());
			}
			if (overlappingQuads.size() < 2 && overlappingQuads.size() > 0)
			{
				overlappingQuads[0]->Insert(obj); // It doesn't, insert it there.
			}
			else // It does overlap multiple quads, insert body to this quad's list instead.
			{
				m_Bodies.push_back(obj);
			}
		}
	}
}

void p2QuadTree::Retrieve(std::vector<PotentialCollision>& listToFill)
{
	// Create new potential collision instance if there needs be one.
	if (m_Bodies.size() > 0 || m_HasChildren)
	{
		listToFill.push_back(PotentialCollision());
	}

	if (m_HasChildren)
	{
		int iterator = 0;

		// Add self to collidees above.
		for each (p2Body* body in m_Bodies)
		{
			listToFill[0].potentialCollideesAbove.push_back(body);
		}
		// Call children recursively.
		for (int i = 0; i < CHILD_TREE_NMB; i++)
		{
			m_Children[i]->RetrieveRecursively(listToFill, iterator);
		}

		listToFill.pop_back(); // Remove last uninitialized potential collision.
	}
	else // This is a leaf.
	{
		listToFill[0].siblings = m_Bodies;
	}
}

void p2QuadTree::RetrieveRecursively(std::vector<PotentialCollision>& listToFill, int& currentIndex)
{
	if (m_HasChildren)
	{

		// Add self to collidees above.
		for each (p2Body* body in m_Bodies)
		{
			listToFill[currentIndex].potentialCollideesAbove.push_back(body);
		}
		// Call children recursively.
		for (int i = 0; i < CHILD_TREE_NMB; i++)
		{
			int initialIndex = currentIndex;
			std::vector<p2Body*> potentialCollideesAbove_Copy = listToFill[currentIndex].potentialCollideesAbove;

			m_Children[i]->RetrieveRecursively(listToFill, currentIndex);

			if (currentIndex != initialIndex) // We've added a new potential collision in the meantime.
			{
				listToFill[currentIndex].potentialCollideesAbove = potentialCollideesAbove_Copy;
			}

			/*if (i == CHILD_TREE_NMB - 1) // If this is the last child
			{
				for (int i = 0; i < m_Bodies.size(); i++)
				{
					listToFill[currentIndex].potentialCollideesAbove.pop_back();
				}
			}*/
		}
	}
	else // This is a leaf.
	{
		if (m_Bodies.size() > 0) // This leaf has bodies in it.
		{
			listToFill[currentIndex].siblings = m_Bodies;
			listToFill.push_back(PotentialCollision());
			currentIndex++;
		}
	}
}

void p2QuadTree::GetQuadTreesAabbs(std::vector<p2AABB>& listToFill) const
{
	listToFill.push_back(m_Bounds);
	if (m_HasChildren)
	{
		m_Children[0]->GetQuadTreesAabbs(listToFill);
		m_Children[1]->GetQuadTreesAabbs(listToFill);
		m_Children[2]->GetQuadTreesAabbs(listToFill);
		m_Children[3]->GetQuadTreesAabbs(listToFill);
	}
}

void p2QuadTree::LogQuadsBodyCount() const
{
	std::cout << "Quad at level: " << m_NodeLevel << " : " << m_Bodies.size() << " bodies." << std::endl;
	if (m_HasChildren)
	{
		m_Children[0]->LogQuadsBodyCount();
		m_Children[1]->LogQuadsBodyCount();
		m_Children[2]->LogQuadsBodyCount();
		m_Children[3]->LogQuadsBodyCount();
	}
}