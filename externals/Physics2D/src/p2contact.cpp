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

void p2ContactManager::SetContactListener(p2ContactListener* listener)
{
	m_ContactListener = listener;
}

void p2ContactManager::SendContactMessage() const
{
	// TODO
}

void p2ContactManager::SolveContacts(p2QuadTree* rootQuad) const
{
	// TODO: implement bfs first

	// Init variables we'll be using a lot.
	std::vector<p2Body*> allBodies = std::vector<p2Body*>();
	std::vector<p2QuadTree*> allBodiesQuads = std::vector<p2QuadTree*>();
	std::vector<p2Body*> potentialCollidees = std::vector<p2Body*>(); // Used for collision checking in broad phase.
	std::vector<p2QuadTree*> potentialCollideesQuads = std::vector<p2QuadTree*>();
	std::vector<p2Contact> potentialContacts = std::vector<p2Contact>(); // Used for collision checking in narrow phase.
	p2Contact newPotentialContact = p2Contact();
	int firstSiblingToCheck = 1; // Avoids checking against aleready checked siblings.

	// Get all bodies and their corresponding quads.
	// rootQuad->RetrieveFromChildren(allBodies, allBodiesQuads);
	if (allBodies.size() != allBodiesQuads.size()) // Sanity check.
	{
		throw "Number of quads does not match number of bodies!";
	}

	// Reverse lists to end up with lowest level nodes first. Possible since Retrieve traverses nodes in a BFS fashion.
	// std::reverse(allBodies.begin(), allBodies.end());
	// std::reverse(allBodiesQuads.begin(), allBodiesQuads.end());

	// Broad phase: check AABBs and generate potential contacts.
	int nbOfBodies = allBodies.size();
	for (int currentBody = 0; currentBody < nbOfBodies; currentBody++)
	{
		if (!allBodies[currentBody]->IsInit()) // Sanity check.
		{
			throw "Checking collision for an uninitialized body!";
		}

		// Retrieve all bodies from this body's node and lower.
		// allBodiesQuads[currentBody]->RetrieveFromChildren(potentialCollidees, potentialCollideesQuads);
		// std::reverse(potentialCollidees.begin(), potentialCollidees.end()); // Reverse list to end up with siblings first.

		// Count siblings.
		int siblingsCounter = 1; // There's always at least one body in a given node.
		while (allBodiesQuads[currentBody] == potentialCollideesQuads[siblingsCounter])
		{
			if (potentialCollidees[siblingsCounter] == allBodies[currentBody]) // Sanity check.
			{
				throw "Comparing self to self!";
			}

			siblingsCounter++;
		}

		// If current body has any siblings.
		if (siblingsCounter > 1)
		{
			// Check collisions against siblings.
			for (int sibling = firstSiblingToCheck; sibling < siblingsCounter; sibling++)
			{
				if (allBodiesQuads[currentBody] != potentialCollideesQuads[sibling]) // Sanity check.
				{
					throw "A non sibling ended up being considered a sibling!";
				}

				if (allBodies[currentBody]->GetAabb().Overlaps(potentialCollidees[sibling]->GetAabb()))
				{
					newPotentialContact.ColliderA = &allBodies[currentBody]->GetCollider();
					newPotentialContact.ColliderB = &potentialCollidees[sibling]->GetCollider();
					potentialContacts.push_back(newPotentialContact);
				}
			}
			// If this was the last sibling of this node.
			if (firstSiblingToCheck >= siblingsCounter)
			{
				firstSiblingToCheck = 1; // Reset counter.
			}
			else
			{
				firstSiblingToCheck++; // Else increment.
			}
		}

		// Check collisions against all other potential collidees.
		int nbOfPotentialCollidees = potentialCollidees.size();
		for (int i = siblingsCounter + 1; i < nbOfPotentialCollidees; i++)
		{
			if (allBodies[currentBody]->GetAabb().Overlaps(potentialCollidees[i]->GetAabb())) // See if it's AABB overlaps current body's AABB.
			{
				// If so, create a potential contact to be analysed during narrow phase.
				newPotentialContact.ColliderA = &allBodies[currentBody]->GetCollider();
				newPotentialContact.ColliderB = &potentialCollidees[i]->GetCollider();
				potentialContacts.push_back(newPotentialContact);
			}
		}
	}


	// Get definitive contacts with narrow phase

	// Send collision message


	// correct positions and velocities
}

std::vector<p2Contact> p2ContactManager::FilteringBroadPhase(std::vector<p2Body*> bodies) const
{
	// TODO
}

void p2ContactManager::FilteringNarrowPhase(std::vector<p2Contact>& contactsToFilter) const
{
	// TODO
}