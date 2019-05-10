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

#include <p2shape.h>
#include <p2contact.h>

class p2Body;

/**
* \brief Struct defining a p2Collider when creating one
*/
struct p2ColliderDef
{
	void* userData; // Hell is that?
	float restitution;
	bool isSensor;
};

/**
* \brief Representation of a Collider attached to a p2Body
*/

class p2Collider // Note: doesn't have a constructor because collider creation is managed internally by p2Body.
{
public:
	p2Collider();

	bool IsSensor();
	const p2Body* Body() const;
	void* GetUserData();
	const Transform2d* GetTransform() const;
	void SetUserData(void* colliderData);
	void SetShape(const p2Shape& shape);
	void SetIsSensor(const bool& isSensor);
	void SetRestitution(const float& restitution);
	p2Contact GetContacts(const p2Collider& other) const;
private:
	// Attributes.
	void* m_UserData = nullptr;
	bool m_IsSensor;
	float m_Restitution;
	// References.
	p2Body* m_Body;
};



#endif