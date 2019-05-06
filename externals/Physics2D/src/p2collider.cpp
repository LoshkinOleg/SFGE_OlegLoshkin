#include "..\include\p2collider.h"

p2Collider::p2Collider()
{
	m_Shape = p2Shape();
	m_IsSensor = false;
	m_Restitution = 0.5f;
}

bool p2Collider::IsSensor()
{
	return false;
}

void* p2Collider::GetUserData()
{
	return nullptr;
}

p2Shape* p2Collider::GetShape()
{
	return &m_Shape;
}

void p2Collider::SetUserData(void* colliderData)
{
	m_UserData = colliderData;
}

void p2Collider::SetShape(const p2Shape& shape)
{
	m_Shape = shape;
}

void p2Collider::SetIsSensor(const bool& isSensor)
{
	m_IsSensor = isSensor;
}

void p2Collider::SetRestitution(const float& restitution)
{
	m_Restitution = restitution;
}
