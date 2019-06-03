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
#include <iostream>
#include <p2body.h>

void p2Body::Init(p2BodyDef* bodyDef)
{
	m_Colliders.resize(MAX_COLLIDER_LEN);
	m_Type = bodyDef->type;
	m_Position = bodyDef->position;
	m_GravityScale = bodyDef->gravityScale;
	m_LinearVelocity = bodyDef->linearVelocity;
	m_Mass = bodyDef->mass;
	if (bodyDef->restitution >= 0 && bodyDef->restitution <= 1) m_Restitution = bodyDef->restitution;
	m_IsInit = true;
}

p2Vec2 p2Body::GetLinearVelocity() const
{
	return m_LinearVelocity;
}
void p2Body::SetLinearVelocity(p2Vec2 velocity)
{
	m_LinearVelocity = velocity;
}

p2Vec2 p2Body::GetPosition()
{
	return m_Position;
}
void p2Body::SetPosition(const p2Vec2 position)
{
	this->m_Position = position;
	m_Colliders[0].UpdateAabb(position);
}

float p2Body::GetAngularVelocity() // NOTE: Not used.
{
	return m_AngularVelocity;
}

void p2Body::UpdatePosition()
{
	m_Position += m_LinearVelocity * 0.02f;
	m_Colliders[0].UpdateAabb(m_Position);
}

p2Collider * p2Body::CreateCollider(p2ColliderDef * colliderDef)
{
	p2Collider& collider = m_Colliders[m_ColliderIndex];
	collider.Init(colliderDef);
	m_ColliderIndex++;
	return &collider;
}

void p2Body::ApplyForceToCenter(const p2Vec2& force)
{
	m_LinearVelocity += (force / m_Mass);
}

void p2Body::ApplyCollisionForces(p2Body* other)
{
	// https://en.wikipedia.org/wiki/Coefficient_of_restitution
	// https://en.wikipedia.org/wiki/Inelastic_collision

	float m0 = m_Mass;
	float m1 = other->m_Mass;
	float v0_x = m_LinearVelocity.x;
	float v0_y = m_LinearVelocity.y;
	float v1_x = other->m_LinearVelocity.x;
	float v1_y = other->m_LinearVelocity.y;
	float r0 = m_Restitution;
	float r1 = other->m_Restitution;

	float e_x;
	float Ecin_beforeCollision_x = (m0 * v0_x * v0_x * 0.5f) + (m1 * v1_x * v1_x * 0.5f);
	float Ecin_afterCollision_x = (m0 * v0_x * v0_x * 0.5f * r0) + (m1 * v1_x * v1_x * 0.5f * r1);
	if (Ecin_beforeCollision_x != 0)
	{
		e_x = _CMATH_::sqrt((Ecin_afterCollision_x)/(Ecin_beforeCollision_x));
	}
	else
	{
		e_x = 1;
	}

	float e_y;
	float Ecin_beforeCollision_y = (m0 * v0_y * v0_y * 0.5f) + (m1 * v1_y * v1_y * 0.5f);
	float Ecin_afterCollision_y = (m0 * v0_y * v0_y * 0.5f * r0) + (m1 * v1_y * v1_y * 0.5f * r1);
	if (Ecin_beforeCollision_y != 0)
	{
		e_y = _CMATH_::sqrt((Ecin_afterCollision_y) / (Ecin_beforeCollision_y));
	}
	else
	{
		e_y = 1;
	}

	p2Vec2 u0, u1;
	u0.x = (((v1_x - v0_x) * e_x * m1) + (v0_x * m0) + (v1_x * m1)) / (m0 + m1);
	u1.x = (((v0_x - v1_x) * e_x * m0) + (v0_x * m0) + (v1_x * m1)) / (m0 + m1);
	u0.y = (((v1_y - v0_y) * e_y * m1) + (v0_y * m0) + (v1_y * m1)) / (m0 + m1);
	u1.y = (((v0_y - v1_y) * e_y * m0) + (v0_y * m0) + (v1_y * m1)) / (m0 + m1);

	SetLinearVelocity(u0);
	other->SetLinearVelocity(u1);
}

p2BodyType p2Body::GetType() const
{
	return m_Type;
}

float p2Body::GetMass() const
{
	return m_Mass;
}

p2AABB& p2Body::GetAabb()
{
	if (m_ColliderIndex < 1)
	{
		std::cout << "Trying to get the aabb of an uninitialized collider!" << std::endl;
		throw;
	}
	return m_Colliders[(size_t)m_ColliderIndex - 1].GetAabb();
}

float p2Body::GetRestitution() const
{
	return m_Restitution;
}

p2Collider* p2Body::GetCollider()
{
	return &m_Colliders[0]; // Only dealing with one collider for now.
}

bool p2Body::IsInit() const
{
	return m_IsInit;
}
