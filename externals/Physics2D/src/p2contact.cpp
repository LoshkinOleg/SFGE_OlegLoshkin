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
// #include <p2vector.h>
#include <p2quadtree.h>
// #include <p2collider.h>
#include <p2body.h>

// Intersections.
p2Vec2 CircleIntersection::AverageIntersection() const
{
	p2Vec2 returnValue;
	for (size_t i = 0; i < intersections.size(); i++)
	{
		returnValue += intersections[i];
	}
	return returnValue / intersections.size();
}

// p2Contact.
p2Collider* p2Contact::GetColliderA()
{
	return ColliderA;
}
p2Collider* p2Contact::GetColliderB()
{
	return ColliderB;
}
std::string p2Contact::ToString() const
{
	return "Contact between: " + ColliderA->GetAabb().ToString() + "and \n" + ColliderB->GetAabb().ToString() + "\n";
}

// p2ContactManager.
void p2ContactManager::SetContactListener(p2ContactListener* listener)
{
	m_ContactListener = listener;
}
void p2ContactManager::SolveContacts(p2Quad* rootQuad)
{
	// Send contact messages.
	for (p2Contact& contact : m_CurrentContacts)
	{
		m_ContactListener->EndContact(&contact);
	}

	// Broad phase.
	std::vector<PotentialCollision> potentialCollisions = rootQuad->Retrieve();
	m_CurrentContacts = std::vector<p2Contact>();

	// Filter off potential collisions using aabb's.
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
	p2Body* body_0;
	p2Body* body_1;
	p2Collider* collider_0;
	p2Collider* collider_1;
	p2Vec2 position_0;
	p2Vec2 position_1;
	p2ShapeType shapeType_0;
	p2ShapeType shapeType_1;
	p2BodyType bodyType_0;
	p2BodyType bodyType_1;
	for (p2Contact& contact : m_CurrentContacts)
	{
		// Initialize variables.
		body_0 = contact.ColliderA->GetBody();
		body_1 = contact.ColliderB->GetBody();
		collider_0 = contact.ColliderA;
		collider_1 = contact.ColliderB;
		position_0 = contact.ColliderA->GetPosition();
		position_1 = contact.ColliderB->GetPosition();
		shapeType_0 = contact.ColliderA->GetShape()->GetType();
		shapeType_1 = contact.ColliderB->GetShape()->GetType();
		bodyType_0 = contact.ColliderA->GetBody()->GetType();
		bodyType_1 = contact.ColliderB->GetBody()->GetType();

		if (shapeType_0 == p2ShapeType::CIRCLE && shapeType_1 == p2ShapeType::CIRCLE) // Case circle vs circle.
		{
			CircleIntersection intersect = contact.ColliderA->FindCircleCircleIntersection(contact.ColliderB);

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
							body_0->SetPosition(position_0 - intersect.mtv[0]);
							body_1->SetPosition(position_1 - intersect.mtv[1]);

							// Modify velocities.
							body_0->ApplyCollisionForces(body_1);
						}
						else if ((bodyType_0 == p2BodyType::DYNAMIC && bodyType_1 == p2BodyType::STATIC) || (bodyType_0 == p2BodyType::STATIC && bodyType_1 == p2BodyType::DYNAMIC)) // If this is a static vs dynamic contact.
						{
							// TODO:: handle static vs dynamic position correction.

							body_0->ApplyCollisionForces(body_1);
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
							body_0->ApplyCollisionForces(body_1);
						}
						else if ((bodyType_0 == p2BodyType::DYNAMIC && bodyType_1 == p2BodyType::STATIC) || (bodyType_0 == p2BodyType::STATIC && bodyType_1 == p2BodyType::DYNAMIC)) // If this is a static vs dynamic contact.
						{
							// TODO:: handle static vs dynamic position correction.

							body_0->ApplyCollisionForces(body_1);
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
					// Correct positions.
					p2Vec2 mtv = contact.ColliderA->FindRectRectMtv(contact.ColliderB);
					body_0->SetPosition(body_0->GetPosition() - (mtv * 0.5f));
					body_1->SetPosition(body_1->GetPosition() + (mtv * 0.5f));

					// Modify velocities.
					body_0->ApplyCollisionForces(body_1);
				}
				else if ((bodyType_0 == p2BodyType::DYNAMIC && bodyType_1 == p2BodyType::STATIC) || (bodyType_0 == p2BodyType::STATIC && bodyType_1 == p2BodyType::DYNAMIC)) // If this is a static vs dynamic contact.
				{
					// TODO:: handle static vs dynamic position correction.

					body_0->ApplyCollisionForces(body_1);
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
