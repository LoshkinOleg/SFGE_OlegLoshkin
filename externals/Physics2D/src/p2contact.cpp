/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <p2contact.h>
#include <p2quadtree.h>
#include <p2body.h>
// debugging
#include <iostream>

void p2ContactManager::SetContactListener(p2ContactListener* listener)
{
	m_ContactListener = listener;
}

void p2ContactManager::SolveContacts(p2QuadTree* rootQuad)
{
	// Send contact messages.
	for (p2Contact& contact : m_CurrentContacts)
	{
		m_ContactListener->EndContact(&contact);
	}

	// Broad phase.
	std::vector<PotentialCollision> potentialCollisions = rootQuad->Retrieve();
	m_CurrentContacts = std::vector<p2Contact>();

	for each (PotentialCollision potentialCol in potentialCollisions)
	{
		// Check against bodies above.
		for each (p2Body* leafBody in potentialCol.siblings)
		{
			for (int i = 0; i < potentialCol.potentialCollideesAbove.size(); i++)
			{
				if (leafBody->GetAabb().Overlaps(potentialCol.potentialCollideesAbove[i]->GetAabb()))
				{
					m_CurrentContacts.push_back(p2Contact());
					m_CurrentContacts.back().ColliderA = &leafBody->GetCollider();
					m_CurrentContacts.back().ColliderB = &potentialCol.potentialCollideesAbove[i]->GetCollider();
				}
			}
		}

		// Check against siblings.
		int firstSiblingToCheck = 1;
		for (int sibling = 0; sibling < potentialCol.siblings.size() - 1; sibling++)
		{
			for (int otherSibling = firstSiblingToCheck; otherSibling < potentialCol.siblings.size(); otherSibling++)
			{
				if (potentialCol.siblings[sibling]->GetAabb().Overlaps(potentialCol.siblings[otherSibling]->GetAabb()))
				{
					m_CurrentContacts.push_back(p2Contact());
					m_CurrentContacts.back().ColliderA = &potentialCol.siblings[sibling]->GetCollider();
					m_CurrentContacts.back().ColliderB = &potentialCol.siblings[otherSibling]->GetCollider();
				}
			}

			firstSiblingToCheck++;
		}
	}

	// Narrow phase.

	// Send contact messages.
	for (p2Contact& contact : m_CurrentContacts)
	{
		m_ContactListener->BeginContact(&contact);
	}
}