#include <p2collider.h>
#include <p2shape.h>
#include <p2body.h>

void p2Collider::Init(const p2ColliderDef* def)
{
	m_UserData = def->userData;
	m_IsSensor = def->isSensor;
	m_Restitution = def->restitution;
	m_Body = def->body;
	p2AABB myAabb = p2AABB();

	switch (def->shape->GetType())
	{
		case p2ShapeType::RECTANGLE:
		{
			m_Shape = new p2RectShape(*static_cast<p2RectShape*>(def->shape));
			p2Vec2 rectSize = static_cast<p2RectShape*>(m_Shape)->GetSize();
			myAabb.bottomLeft = p2Vec2(m_Body->GetPosition().x - (rectSize.x / 2.0f), m_Body->GetPosition().y + (rectSize.x / 2.0f));
			myAabb.topRight = p2Vec2(m_Body->GetPosition().x + (rectSize.x / 2.0f), m_Body->GetPosition().y - (rectSize.x / 2.0f));
		}break;
		case p2ShapeType::CIRCLE:
		{
			m_Shape = new p2CircleShape(*static_cast<p2CircleShape*>(def->shape));
			float myRadius = static_cast<p2CircleShape*>(m_Shape)->GetRadius();
			myAabb.bottomLeft = p2Vec2(m_Body->GetPosition().x - myRadius, m_Body->GetPosition().y + myRadius);
			myAabb.topRight = p2Vec2(m_Body->GetPosition().x + myRadius, m_Body->GetPosition().y - myRadius);
		}break;
		default:
		{
			throw "p2ShapeType is invalid!";
		}
		break;
	}
	m_Aabb = myAabb;
}

bool p2Collider::IsSensor()
{
	return m_IsSensor;
}

p2Collider::~p2Collider()
{
	delete m_Shape;
}

void* p2Collider::GetUserData()
{
	return m_UserData;
}

p2Shape* p2Collider::GetShape()
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

p2Vec2 p2Collider::FindMtv(p2Collider* other) const
{
	p2Vec2 axis[2]{ p2Vec2{1,0}, p2Vec2{0,1} };

	p2Mat22 myProjectionX = m_Aabb.Sides()[0].ProjectSelfOnto(axis[0]);
	p2Mat22 myProjectionY = m_Aabb.Sides()[1].ProjectSelfOnto(axis[1]);
	p2Mat22 otherProjectionX = m_Aabb.Sides()[0].ProjectSelfOnto(axis[0]);
	p2Mat22 otherProjectionY = m_Aabb.Sides()[1].ProjectSelfOnto(axis[1]);

	float myProjectionXMagnitude = myProjectionX.rows[1].x - myProjectionX.rows[0].x;
	float otherProjectionXMagnitude = otherProjectionX.rows[1].x - otherProjectionX.rows[0].x;

	p2Mat22 xOverlap;
	if (myProjectionX.rows[1].x > otherProjectionX.rows[1].x)
	{
		xOverlap.rows[0] = 
	}
}
