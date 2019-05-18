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

#ifndef SFGE_P2CONTACT_H
#define SFGE_P2CONTACT_H

#include <p2collider.h>
class p2Body;
class p2QuadTree;

/**
* \brief Listener of contacts happening in an attached p2World
*/
class p2ContactListener
{
public:
	virtual void BeginContact(p2Contact* contact) = 0;
	virtual void EndContact(p2Contact* contact) = 0;
};

/**
* \brief Representation of a contact given as argument in a p2ContactListener
*/
struct p2Contact
{
	p2Collider* ColliderA;
	p2Collider* ColliderB;
};

/**
@Brief: Manages creation, filtering and destruction of p2Contacts. Sends contact messages to contact listener.
*/
class p2ContactManager
{
public:
	// Constructors.
	p2ContactManager() {};
	p2ContactManager(p2ContactListener* listener) : m_ContactListener(listener) {};

	// Properties.
	void SetContactListener(p2ContactListener* listener);
	
	// Public methods.
	void SolveContacts(p2QuadTree* rootQuad) const;

private:
	// Private methods.
	void SendContactMessage() const;
	std::vector<p2Contact> FilteringBroadPhase(std::vector<p2Body*> bodies) const;
	void FilteringNarrowPhase(std::vector<p2Contact>& contactsToFilter) const;
	
	// Private attributes.
	p2ContactListener* m_ContactListener = nullptr;
};
#endif