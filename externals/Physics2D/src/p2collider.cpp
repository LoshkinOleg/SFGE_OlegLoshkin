#include "..\include\p2collider.h"
#include <p2aabb.h>
#include <p2body.h>
#include <iostream>
#include <engine\transform2d.h>
#include <cmath>
using Bitflag = unsigned __int8;

namespace  sfge
{
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

	const p2Body * p2Collider::Body() const
	{
		return m_Body;
	}

	void* p2Collider::GetUserData()
	{
		return nullptr;
	}

	const p2Shape* p2Collider::GetShape() const
	{
		return &m_Shape;
	}

	const Transform2d * p2Collider::GetTransform() const
	{
		return m_transform;
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

	p2Contact p2Collider::GetContacts(const p2Collider& other) const
	{
		switch (m_Shape.GetType())
		{
			case p2ShapeType::RECTANGLE:
			{
				switch (other.GetShape()->GetType())
				{
					case p2ShapeType::RECTANGLE: // Case Rect vs Rect.
					{
						return RectVsRect(other);
					}break;
					case p2ShapeType::CIRCLE: // Case Rect vs Circle.
					{
						return SeparatingAxisTheorem(other, Bitflag(2));
					}break;
					default:
					{
						throw "Unknown other passed to p2Collider::CheckContact()!";
					}break;
				}
			}break;
			case p2ShapeType::CIRCLE:
			{
				switch (other.GetShape()->GetType())
				{
					case p2ShapeType::RECTANGLE: // Case Circle vs Rect.
					{
						return SeparatingAxisTheorem(other, Bitflag(1));
					}break;
					case p2ShapeType::CIRCLE: // Case Circle vs Circle.
					{
						return CircleVsCircle(other);
					}break;
					default:
					{
						throw "Unknown other passed to p2Collider::CheckContact()!";
					}break;
				}
			}break;
			default:
			{
				throw "This p2Collider has an invalid shape type!";
			}break;
		}
	}

	p2Contact p2Collider::SeparatingAxisTheorem(const p2Collider& other, const Bitflag& flag) const
	{
		p2Contact returnValue = p2Contact();
		switch (flag)
		{
			case 1: // Circle vs Rect.
			{
				return returnValue;
			}break;
			case 2: // Rect vs Circle.
			{
				return returnValue;
			}break;
			default:
			{
				throw "Collision type not handeled by SAT!";
			}break;
		}
	}

	p2Contact p2Collider::RectVsRect(const p2Collider& other) const
	{
		Bitflag bitFlag = 0;
		p2AABB myAabb = *m_Body->GetAabb();
		p2AABB otherAabb = *other.Body()->GetAabb();

		// Check overlapping.
		if ((myAabb.XMin() >= otherAabb.XMin() && myAabb.XMin() <= otherAabb.XMax()) || // If overlapping horizontally.
			(myAabb.XMax() >= otherAabb.XMin() && myAabb.XMax() <= otherAabb.XMax()))
		{
			bitFlag = bitFlag | 1 << 1;
		}
		if ((myAabb.YMin() >= otherAabb.YMin() && myAabb.YMin() <= otherAabb.YMax()) || // If overlapping vertically.
			(myAabb.YMax() >= otherAabb.YMin() && myAabb.YMax() <= otherAabb.YMax()))
		{
			bitFlag = bitFlag | 1;
		}

		// Handle overlapping cases.
		switch (bitFlag)
		{
			case 0: // No overlapping.
			{
				return p2Contact(std::vector<p2Vec2>(), false, this, &other);
			}break;
			case 1: // Vertical overlapping only.
			{
				// TODO
				return p2Contact(std::vector<p2Vec2>{}, true, this, &other);
			}break;
			case 2: // Horizontal overlapping only.
			{
				// TODO
				return p2Contact(std::vector<p2Vec2>{}, true, this, &other);
			}break;
			case 3: // Both horizontal and vertical overlapping.
			{
				// TODO
				return p2Contact(std::vector<p2Vec2>{}, true, this, &other);
			}break;
			default:
			{
				std::cout << "Unknown overlap tag!" << std::endl;
			}break;
		}
	}

	p2Contact p2Collider::CircleVsCircle(const p2Collider& other) const
	{
		p2Contact returnValue = p2Contact();

		float myRadius = m_Shape.GetSize().at(0);
		float otherRadius = m_Shape.GetSize().at(0);
		float distanceBetweenShapes = _CMATH_::abs((other.GetTransform()->Position - m_transform->Position).GetMagnitude());
		float maximalDistanceForContact = myRadius + otherRadius;
		if (distanceBetweenShapes < maximalDistanceForContact) // Overlapping circles.
		{
			if ((distanceBetweenShapes + myRadius) < otherRadius) // This circle completely overlaps other circle. Has no contact points.
			{
				return p2Contact(std::vector<p2Vec2>{}, true, this, &other);
			}
			else if((distanceBetweenShapes + myRadius) > otherRadius) // This circle is partially overlapping other circle. Has 2 contact points.
			{
				return p2Contact(std::vector<p2Vec2>{}, true, this, &other);
			}
			else // This circle completely overlaps other circle. Has 1 contact point.
			{
				return p2Contact(std::vector<p2Vec2>{}, true, this, &other);
			}
		}
		else if(distanceBetweenShapes == maximalDistanceForContact) // 1 contact. No overlapping.
		{
			// TODO
			return p2Contact(std::vector<p2Vec2>{}, true, this, &other);
		}
		else
		{
			return p2Contact(std::vector<p2Vec2>(), false, this, &other);
		}
	}
}
