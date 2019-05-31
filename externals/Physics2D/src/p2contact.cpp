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
#include <p2shape.h>
#include <iostream>
#include <p2aabb.h>

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
					m_CurrentContacts.back().ColliderA = leafBody->GetCollider();
					m_CurrentContacts.back().ColliderB = potentialCol.potentialCollideesAbove[i]->GetCollider();
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
					m_CurrentContacts.back().ColliderA = potentialCol.siblings[sibling]->GetCollider();
					m_CurrentContacts.back().ColliderB = potentialCol.siblings[otherSibling]->GetCollider();
				}
			}

			firstSiblingToCheck++;
		}
	}
	
	// Narrow phase.
	std::vector<p2Contact> filteredContacts = std::vector<p2Contact>();
	for (p2Contact& contact : m_CurrentContacts)
	{
		p2Body* body_0 = contact.ColliderA->GetBody();
		p2Body* body_1 = contact.ColliderB->GetBody();
		p2Vec2 position_0 = contact.ColliderA->GetPosition();
		p2Vec2 position_1 = contact.ColliderB->GetPosition();
		p2ShapeType shapeType_0 = contact.ColliderA->GetShape()->GetType();
		p2ShapeType shapeType_1 = contact.ColliderB->GetShape()->GetType();
		p2BodyType bodyType_0 = contact.ColliderA->GetBody()->GetType();
		p2BodyType bodyType_1 = contact.ColliderB->GetBody()->GetType();

		if (shapeType_0 == p2ShapeType::CIRCLE && shapeType_1 == p2ShapeType::CIRCLE) // Case circle vs circle.
		{
			p2CircleShape circle_0 = *static_cast<p2CircleShape*>(contact.ColliderA->GetShape());
			p2CircleShape circle_1 = *static_cast<p2CircleShape*>(contact.ColliderB->GetShape());
			CircleIntersection intersect = circle_0.FindIntersections(circle_1, position_0, position_1);

			if (intersect.anyContact)
			{
				filteredContacts.push_back(contact); // Keep contact.

				if (intersect.intersections.size() > 1) // 2 intersections.
				{
					if (!(contact.ColliderA->IsSensor() || contact.ColliderB->IsSensor())) // If not a sensor type contact.
					{
						if (bodyType_0 == p2BodyType::DYNAMIC && bodyType_1 == p2BodyType::DYNAMIC) // If this is a dynamic vs dynamic contact.
						{
							// Correct positions.
							float penetration_0 = circle_0.GetRadius() - (intersect.AverageIntersection() - position_0).GetMagnitude();
							float penetration_1 = circle_1.GetRadius() - (intersect.AverageIntersection() - position_1).GetMagnitude();
							p2Vec2 direction_0 = (position_1 - position_0).Normalized();
							p2Vec2 direction_1 = (position_0 - position_1).Normalized();
							body_0->SetPosition(position_0 - (direction_0 * penetration_0));
							body_1->SetPosition(position_1 - (direction_1 * penetration_1));

							// Modify velocities.
							body_0->Collide(body_1);
						}
						else if ((bodyType_0 == p2BodyType::DYNAMIC && bodyType_1 == p2BodyType::STATIC) || (bodyType_0 == p2BodyType::STATIC && bodyType_1 == p2BodyType::DYNAMIC)) // If this is a static vs dynamic contact.
						{
							// TODO:: handle static vs dynamic position correction.

							body_0->Collide(body_1);
						}
					}
				}
				else // There's only one contact.
				{
					if (!(contact.ColliderA->IsSensor() || contact.ColliderB->IsSensor())) // If not a sensor type contact.
					{
						if (bodyType_0 == p2BodyType::DYNAMIC && bodyType_1 == p2BodyType::DYNAMIC) // If this is a dynamic vs dynamic contact.
						{
							// Modify velocities.
							body_0->Collide(body_1);
						}
						else if ((bodyType_0 == p2BodyType::DYNAMIC && bodyType_1 == p2BodyType::STATIC) || (bodyType_0 == p2BodyType::STATIC && bodyType_1 == p2BodyType::DYNAMIC)) // If this is a static vs dynamic contact.
						{
							body_0->Collide(body_1);
						}
					}
				}
			}

		}
		if (shapeType_0 == p2ShapeType::RECTANGLE && shapeType_1 == p2ShapeType::RECTANGLE) // Case rect vs rect.
		{
			filteredContacts.push_back(contact); // Keep contact.

			if (!(contact.ColliderA->IsSensor() || contact.ColliderB->IsSensor())) // If not a sensor type contact.
			{
				if (bodyType_0 == p2BodyType::DYNAMIC && bodyType_1 == p2BodyType::DYNAMIC) // If this is a dynamic vs dynamic contact.
				{
					// Find mtv
					p2Vec2 mtv = contact.ColliderA.FindMtv(contact.ColliderB);

					// Modify velocities.
					body_0->Collide(body_1);
				}
				else if ((bodyType_0 == p2BodyType::DYNAMIC && bodyType_1 == p2BodyType::STATIC) || (bodyType_0 == p2BodyType::STATIC && bodyType_1 == p2BodyType::DYNAMIC)) // If this is a static vs dynamic contact.
				{
					// TODO:: handle static vs dynamic position correction.

					body_0->Collide(body_1);
				}
			}
		}
	}

	// Send contact messages.
	for (p2Contact& contact : m_CurrentContacts)
	{
		m_ContactListener->BeginContact(&contact);
	}
}

p2Collider* p2Contact::GetColliderA()
{
	return ColliderA;
}

p2Collider* p2Contact::GetColliderB()
{
	return ColliderB;
}

void p2Contact::ToString() const
{
	std::cout << "--------------" << std::endl;
	std::cout << "Contact between: " << ColliderA->GetAabb().ToString() << "and \n" << ColliderB->GetAabb().ToString() << std::endl;
}
