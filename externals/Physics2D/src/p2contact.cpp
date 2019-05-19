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

#include <p2contact.h>
#include <p2quadtree.h>
#include <p2body.h>

void p2ContactManager::SetContactListener(p2ContactListener* listener)
{
	m_ContactListener = listener;
}

void p2ContactManager::SendContactMessage() const
{
	// TODO
}

void p2ContactManager::SolveContacts(p2QuadTree* rootQuad) const
{
	
}

std::vector<p2Contact> p2ContactManager::FilteringBroadPhase(std::vector<p2Body*> bodies) const
{
	// TODO
}

void p2ContactManager::FilteringNarrowPhase(std::vector<p2Contact>& contactsToFilter) const
{
	// TODO
}