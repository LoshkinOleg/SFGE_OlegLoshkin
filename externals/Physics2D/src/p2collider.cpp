#include <p2collider.h>
#include <p2body.h>

void p2Collider::Init(const p2ColliderDef* def)
{
	m_UserData = def->userData;
	m_IsSensor = def->isSensor;
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

p2AABB& p2Collider::GetAabb()
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
	m_Aabb.SetCenter(center);
}

p2Vec2 p2Collider::FindRectRectMtv(p2Collider* other) const
{
	// Since we're not dealing with rotations, we've only got to check projections on X and Y axis.

	// Initialize variables.
	p2Vec2 axis[2]{ p2Vec2{1,0}, p2Vec2{0,1} };
	p2Mat22 projection;
	float myProjectionX[2], otherProjectionX[2];
	float myProjectionY[2], otherProjectionY[2];

	// Find projections on X.
	projection = m_Aabb.Sides()[0].ProjectSelfOnto(axis[0]);
	myProjectionX[0] = projection.rows[0].x;
	myProjectionX[1] = projection.rows[1].x;
	projection = other->m_Aabb.Sides()[0].ProjectSelfOnto(axis[0]);
	otherProjectionX[0] = projection.rows[0].x;
	otherProjectionX[1] = projection.rows[1].x;
	// Find projections on Y.
	projection = m_Aabb.Sides()[1].ProjectSelfOnto(axis[1]);
	myProjectionY[0] = projection.rows[0].y;
	myProjectionY[1] = projection.rows[1].y;
	projection = other->m_Aabb.Sides()[1].ProjectSelfOnto(axis[1]);
	otherProjectionY[0] = projection.rows[0].y;
	otherProjectionY[1] = projection.rows[1].y;

	float overlapOnX[2]{	((myProjectionX[0] > otherProjectionX[0]) ? myProjectionX[0] : otherProjectionX[0]),	// Pick greatest minimum and smallest maximum.
							((myProjectionX[1] < otherProjectionX[1]) ? myProjectionX[1] : otherProjectionX[1]) };
	float overlapOnXMagnitude = overlapOnX[1] - overlapOnX[0];

	float overlapOnY[2]{	((myProjectionY[0] > otherProjectionY[0]) ? myProjectionY[0] : otherProjectionY[0]),
							((myProjectionY[1] < otherProjectionY[1]) ? myProjectionY[1] : otherProjectionY[1]) };
	float overlapOnYMagnitude = overlapOnY[1] - overlapOnY[0];

	// TODO: This doesn't make sense, it would pick an axis if the rects are overlapping diagonally and separate them either horizontally or vertically rather than diagonally...
	if (overlapOnXMagnitude < overlapOnYMagnitude)
	{
		return axis[0] * overlapOnXMagnitude;
	}
	else
	{
		return axis[1] * overlapOnYMagnitude;
	}
}

CircleIntersection p2Collider::FindCircleCircleIntersection(p2Collider* other) const
{
	// Initialize variables.
	p2CircleShape myCircle = *static_cast<p2CircleShape*>(m_Shape);
	p2CircleShape otherCircle = *static_cast<p2CircleShape*>(other->GetShape());
	p2Vec2 myPosition = GetPosition();
	p2Vec2 otherPosition = other->GetPosition();
	p2Vec2 directionBetweenCenters = (otherPosition - myPosition).Normalized();
	float distanceBetweenCenters = directionBetweenCenters.Magnitude();
	float myRadius = myCircle.GetRadius();
	float otherRadius = otherCircle.GetRadius();

	if (distanceBetweenCenters < myRadius + otherRadius) // Case 2 intersections.
	{
		// TODO: actually understand what's going on...
		// Code taken from: https://stackoverflow.com/questions/3349125/circle-circle-intersection-points
		// See Fig.2 in techical documentation.
		p2Vec2 P0(myPosition.x, myPosition.y);
		p2Vec2 P1(otherPosition.x, otherPosition.y);
		float d, a, h;
		d = (P1 - P0).Magnitude();
		a = ((myRadius * myRadius) - (otherRadius * otherRadius) + (d * d)) / (2 * d);
		h = _CMATH_::sqrt((myRadius * myRadius) - (a * a));
		p2Vec2 P2 = ((P1 - P0) * (a / d)) + P0;

		float deltaY = h * (P1.y - P0.y) / d;
		float deltaX = h * (P1.x - P0.x) / d;

		return CircleIntersection{	true,
									std::vector<p2Vec2>{	p2Vec2(P2.x + deltaY, P2.y - deltaX),	p2Vec2(P2.x - deltaY, P2.y + deltaX)	},
									std::array<p2Vec2,2>{	directionBetweenCenters * (myRadius - a),	directionBetweenCenters	* -(otherRadius - (distanceBetweenCenters - a))	}};
	}
	else if (distanceBetweenCenters == myRadius + otherRadius ||
			 distanceBetweenCenters == _CMATH_::abs(myRadius - otherRadius)) // Case 1 intersection.
	{
		return CircleIntersection{	true,
									std::vector<p2Vec2>{	p2Vec2(myPosition + (directionBetweenCenters)* myRadius)	},
									std::array<p2Vec2,2>()};
	}
	else // Case no intersections.
	{
		return CircleIntersection{ false, std::vector<p2Vec2>(), std::array<p2Vec2,2>() };
	}
}
