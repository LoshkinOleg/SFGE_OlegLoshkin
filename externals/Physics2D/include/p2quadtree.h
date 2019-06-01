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

#ifndef SFGE_P2QUADTREE_H
#define SFGE_P2QUADTREE_H

#include <memory>
#include <vector>
#include <p2physics.h>

/**
@Brief: Single node of a QuadTree.
*/
class p2Quad
{
public:
	// Constructors.
	p2Quad();
	p2Quad(int nodeLevel, p2AABB bounds);
	~p2Quad();

	// Overloads.
	p2Quad& operator=(p2Quad& other); // Necessary due to usage of smart pointers as attributes.

	// Public methods.
	/**
	@Brief: Clears the QuadTree and deallocates heap attributed to children. Called in Step() before rebuilding QuadTree.
	*/
	void Clear();
	/**
	@Brief: Inserts a p2Body in Quad. Called from Step() during QuadTree rebuilding.
	*/
	void Insert(p2Body* obj);
	/**
	@Brief: Returns a list of all potential collisions.
	*/
	std::vector<PotentialCollision> Retrieve();

	// Debugging methods.
	/**
	@Brief: Fills up passed vector with the aabb's of all quads for debugging.
	*/
	void GetQuadTreesAabbs(std::vector<p2AABB>& listToFill) const;
	/**
	@Brief: Instructs each Quad recursively to cout it's depth level followed by the number of objects it contains.
	*/
	void LogQuadsBodyCount() const;
	
	// Public attributes.
	/**
	@Brief: Defines how many objects a Quad can contain before splitting if it doesn't have any children.
	*/
	static int Max_Objects;

private:
	// Private methods.
	/**
	@Brief: Called when Quad reaches maximum capacity for the first time.
	*/
	void Split();
	/**
	@Brief: Called by Retrieve(). Simplified recursive variation of Retrieve().
	*/
	void RetrieveRecursively(std::vector<PotentialCollision>& listToFill, int& currentIndex);

	// Private attributes.
	static const int MAX_LEVELS = 5;
	static const int CHILD_TREE_NMB = 4;
	int m_NodeLevel;
	p2AABB m_Bounds;
	std::vector<p2Body*> m_Bodies;
	bool m_HasChildren;
	std::unique_ptr<p2Quad> m_Children[CHILD_TREE_NMB];
	p2Quad* m_Parent = nullptr;
};

#endif