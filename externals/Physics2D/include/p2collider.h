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


#ifndef SFGE_P2COLLIDER_H
#define SFGE_P2COLLIDER_H

#include <p2vector.h>
#include <p2aabb.h>
#include <p2shape.h>
#include <p2contact.h>
class p2Body;

struct p2ColliderDef
{
	void* userData = nullptr;
	p2Shape* shape = nullptr;
	bool isSensor = false;
	p2Body* body = nullptr;
};

class p2Collider
{
public:
	p2Collider() {};
	p2Collider(p2Body* body, p2CircleShape shape, p2AABB aabb) : m_Body(body), m_Shape(&shape), m_Aabb(aabb) {};
	~p2Collider();

	// Properties.
	void* GetUserData();
	p2Shape* GetShape();
	bool IsSensor();
	p2AABB& GetAabb();
	p2Vec2 GetPosition() const;
	p2Body* GetBody() const;
	void SetUserData(void* colliderData);

	// Public methods.
	void Init(const p2ColliderDef* def);
	void UpdateAabb(const p2Vec2 center);
	p2Vec2 FindRectRectMtv(p2Collider* other) const;
	CircleIntersection FindCircleCircleIntersection(p2Collider* other) const;

private:
	p2Body* m_Body = nullptr;
	void* m_UserData = nullptr;
	p2Shape* m_Shape = nullptr;
	// float m_Restitution = 1.0f;
	bool m_IsSensor = false;
	p2AABB m_Aabb = p2AABB();
};


#endif