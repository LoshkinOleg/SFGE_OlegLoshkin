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

void p2Body::Init(p2BodyDef* bodyDef)
{
	m_Colliders.resize(MAX_COLLIDER_LEN);
	m_Type = bodyDef->type;
	m_Position = bodyDef->position;
	m_LinearVelocity = bodyDef->linearVelocity;
	m_GravityScale = bodyDef->gravityScale;
	m_Dt = bodyDef->dt;
}

p2Vec2 p2Body::GetLinearVelocity() const
{
	return m_LinearVelocity;
}

void p2Body::SetLinearVelocity(p2Vec2 velocity)
{
	m_LinearVelocity = velocity;
}
float p2Body::GetAngularVelocity()
{
	return m_AngularVelocity;
}

p2Vec2 p2Body::GetPosition()
{
	return m_Position;
}

p2Collider * p2Body::CreateCollider(const p2ColliderDef* colliderDef)
{
	p2Collider& collider = m_Colliders[m_ColliderIndex];
	collider.SetUserData(colliderDef->userData);
	collider.SetShape(colliderDef->shape);
	collider.SetRestitution(colliderDef->restitution);
	collider.SetIsSensor(colliderDef->isSensor);
	m_ColliderIndex++;
	return &collider;
}

void p2Body::UpdatePosition()
{
	m_Position = m_Position + (m_LinearVelocity * m_Dt);
}

void p2Body::ApplyForceToCenter(const p2Vec2& force)
{
	m_LinearVelocity = m_LinearVelocity + (p2Vec2(force) * m_Dt);
}

p2BodyType p2Body::GetType() const
{
	return p2BodyType::STATIC;
}

float p2Body::GetMass() const
{
	return 0.0f;
}
