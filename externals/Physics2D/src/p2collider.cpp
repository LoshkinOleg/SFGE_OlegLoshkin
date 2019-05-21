#include <p2collider.h>
#include <p2shape.h>
#include <p2body.h>

void p2Collider::Init(const p2ColliderDef* def)
{
	m_UserData = def->userData;
	m_Shape = def->shape;
	m_IsSensor = def->isSensor;
	m_Restitution = def->restitution;
	m_Body = def->body;
	p2AABB myAabb = p2AABB();
	switch (m_Shape->GetType())
	{
		case p2ShapeType::RECTANGLE:
		{
			p2Vec2 rectSize = static_cast<p2RectShape*>(m_Shape)->GetSize();
			myAabb.bottomLeft = p2Vec2(m_Body->GetPosition().x - (rectSize.x / 2.0f), m_Body->GetPosition().y + (rectSize.x / 2.0f));
			myAabb.topRight = p2Vec2(m_Body->GetPosition().x + (rectSize.x / 2.0f), m_Body->GetPosition().y - (rectSize.x / 2.0f));
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

void* p2Collider::GetUserData()
{
	return m_UserData;
}

p2Shape* p2Collider::GetShape() const
{
	return m_Shape;
}

void p2Collider::SetUserData(void* colliderData)
{
	m_UserData = colliderData;
}

p2AABB p2Collider::GetAabb() const
{
	return m_Aabb;
}

p2Vec2 p2Collider::GetPosition() const
{
	return m_Body->GetPosition();
}

p2Body* p2Collider::GetBody() const
{
	return m_Body;
}

void p2Collider::UpdateAabb(const p2Vec2 center)
{
	// std::cout << "UpdateAabb() called" << std::endl;

	m_Aabb.SetCenter(center);
}