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

#ifndef SFGE_P2BODY_H
#define SFGE_P2BODY_H

#include <vector>
#include <p2vector.h>
#include <p2aabb.h>
#include <p2collider.h>

const size_t MAX_COLLIDER_LEN = 1;

enum class p2BodyType
{
	STATIC,
	KINEMATIC,
	DYNAMIC
};

struct p2BodyDef
{
	p2BodyType type;
	p2Vec2 position;
	p2Vec2 linearVelocity;
	float gravityScale;
	float mass;
	float restitution;
};

class p2Body
{
public:
	// Properties
	p2BodyType GetType() const;
	p2Vec2 GetPosition();
	p2Vec2 GetLinearVelocity() const;
	float GetAngularVelocity();
	bool IsInit() const;
	float GetMass() const;
	p2AABB& GetAabb();
	float GetRestitution() const;
	p2Collider* GetCollider();
	void SetPosition(const p2Vec2 position);
	void SetLinearVelocity(p2Vec2 velocity);

	// Public methods.
	void Init(p2BodyDef* bodyDef);
	/**
	@Brief: Factory method creating a p2Collider
	@param p2ColliderDef* colliderDef: Definition of a collider.
	@return p2Collider*: Ptr to initialized p2Collider.
	*/
	p2Collider* CreateCollider(p2ColliderDef* colliderDef);
	void UpdatePosition();
	void ApplyForceToCenter(const p2Vec2& force);
	/**
	@Brief: Applies collision forces both to this body and other.
	*/
	void ApplyCollisionForces(p2Body* other);

private:
	p2BodyType m_Type;
	p2Vec2 m_Position;
	p2Vec2 m_LinearVelocity;
	float m_AngularVelocity; // NOTE: Not used.
	float m_Restitution = 1;
	float m_GravityScale; // NOTE: Not used.
	float m_Mass = 1;
	bool m_IsInit;
	int m_ColliderIndex = 0;
	std::vector<p2Collider> m_Colliders;
};

#endif