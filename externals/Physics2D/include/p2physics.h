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

#ifndef SFGE_P2PHYSICS_H
#define SFGE_P2PHYSICS_H
#include <p2vector.h>
#include <p2body.h>
#include <p2contact.h>

namespace sfge
{
class Physics2dManager;

	class P2PhysicsManager
	{
	public:
		P2PhysicsManager();
		P2PhysicsManager(const p2Vec2& gravity, Physics2dManager* ptr);

		// Public methods.
		void FixedUpdate(std::vector<p2Body>& bodies) const;

	private:
		// Methods.
		void ApplyGravity(std::vector<p2Body>& bodies) const;
		void HandleContacts(std::vector<p2Body>& bodies) const;
		// Attributes.
		friend class p2Body;
		p2Vec2 m_Gravity;
		Physics2dManager* m_Manager;
	};
}
#endif