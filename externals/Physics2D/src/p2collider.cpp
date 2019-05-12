#include "..\include\p2collider.h"

void p2Collider::Init(const p2ColliderDef* def)
{
	userData = def->userData;
	m_Shape = def->shape;
	m_IsSensor = def->isSensor;
	m_restitution = def->restitution;
	p2AABB myAabb = p2AABB();
	switch (m_Shape->GetType())
	{
		case p2ShapeType::RECTANGLE:
		{
			p2Vec2 rectSize = static_cast<p2RectShape*>(m_Shape)->GetSize();
			myAabb.bottomLeft = p2Vec2(def->position.x - (rectSize.x / 2.0f), def->position.y + (rectSize.x / 2.0f));
			myAabb.topRight = p2Vec2(def->position.x + (rectSize.x / 2.0f), def->position.y - (rectSize.x / 2.0f));
		}break;
		case p2ShapeType::CIRCLE:
		{

		}break;
		default:
		{
			throw "Trying to create an aabb for a shape of type NONE or unknown!";
		}break;
	}
	m_Aabb = myAabb;
}

bool p2Collider::IsSensor()
{
	return false;
}

void * p2Collider::GetUserData()
{
	return nullptr;
}

p2Shape* p2Collider::GetShape() const
{
	return m_Shape;
}

void p2Collider::SetUserData(void* colliderData)
{
	userData = colliderData;
}

p2AABB p2Collider::GetAabb() const
{
	return m_Aabb;
}
