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
#include <p2body.h>
#include <iostream>

void p2Body::Init(p2BodyDef* bodyDef)
{
	m_Colliders.resize(MAX_COLLIDER_LEN);
	m_Type = bodyDef->type;
	m_Position = bodyDef->position;
	m_GravityScale = bodyDef->gravityScale;
	m_LinearVelocity = bodyDef->linearVelocity;
	m_Mass = bodyDef->mass;
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
void p2Body::SetPosition(const p2Vec2 position)
{
	this->m_Position = position;
	m_Colliders[0].UpdateAabb(position);
}
float p2Body::GetAngularVelocity()
{
	return m_AngularVelocity;
}

p2Vec2 p2Body::GetPosition()
{
	return m_Position;
}

void p2Body::UpdatePosition()
{
	m_Position += m_LinearVelocity * 0.02f;
	m_Colliders[0].UpdateAabb(m_Position * 0.02f);
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

p2BodyType p2Body::GetType() const
{
	return m_Type;
}

float p2Body::GetMass() const
{
	return m_Mass;
}

p2AABB p2Body::GetAabb() const
{
	return m_Colliders[(size_t)(m_ColliderIndex) - 1].GetAabb();
}

p2Collider* p2Body::GetCollider()
{
	return &m_Colliders[0]; // Only dealing with one collider for now.
}

bool p2Body::IsInit() const
{
	return m_IsInit;
}
