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

#ifndef SFGE_P2WORLD_H
#define SFGE_P2WORLD_H

#include <p2physics.h>

const size_t MAX_BODY_LEN = 256;

class p2World
{
public:
	// Constructors.
	/**
	@param p2Vec2 gravity: self explanatory, just keep in mind that Y axis goes from top to down.
	@param p2Vec2 aabbSize: defines bounds of the root Quad of the QuadTree.
	@param int bodiesPerQuad: defines Quad capacity before it needs to Split().
	*/
	p2World(p2Vec2 gravity, p2Vec2 aabbSize, int bodiesPerQuad = 5);

	// Public methods.
	/**
	@Brief: Called every fixed update. Applies forces to bodies, modifies their positions, rebuilds QuadTree, solves contacts and sends contact messages.
	*/
	void Step(float dt);
	/**
	@Brief: Factory method creating p2Bodies.
	*/
	p2Body* CreateBody(p2BodyDef* bodyDef);
	/**
	@Brief: Relays SetContactListener instruction to this world's contact manager.
	*/
	void SetContactListener(p2ContactListener* contactListener);

	// Debugging methods.
	/**
	@Brief: Returns a list of every Quad's bounds in this QuadTree for debugging.
	*/
	std::vector<p2AABB> GetQuadTreeBounds() const;
	/**
	@Brief: Instructs all Quads in QuadTree to cout it's node level followed by number of bodies it holds.
	 */
	void LogQuadsBodyCount() const;

private:
	p2Quad m_RootQuad;
	p2Vec2 m_Gravity;
	std::vector<p2Body> m_Bodies;
	int m_BodyIndex = 0;
	p2ContactManager m_ContactManager;
};

#endif