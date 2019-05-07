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
#include <p2vector.h>
#include <vector>

namespace sfge
{
	class p2Collider;

	/**
	* \brief Representation of a contact given as argument in a p2ContactListener
	*/
	struct p2Contact
	{
		// Constructor.
		p2Contact();
		p2Contact(const std::vector<p2Vec2>& contacts, const bool& triggered, const p2Collider* collider, const p2Collider* collidee);
		// Attributes.
		std::vector<p2Vec2> contacts;
		bool triggered;
		const p2Collider* collider;
		const p2Collider* collidee;
	};

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
	* \brief Managing the creation and destruction of contact between colliders
	*/
	class p2ContactManager
	{

	};
}

#endif