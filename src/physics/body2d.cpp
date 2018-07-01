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

#include <physics/body2d.h>
#include <physics/physics.h>
#include <engine/transform.h>

namespace sfge
{


b2Body * Body2d::GetBody()
{
	return m_Body;
}

void Body2d::SetVelocity(b2Vec2 v)
{
	if (m_Body != nullptr)
	{
		m_Body->SetLinearVelocity(v);
	}
}

b2Vec2 Body2d::GetVelocity()
{
	if (m_Body != nullptr)
	{
		return m_Body->GetLinearVelocity();
	}
	return b2Vec2();
}

b2BodyType Body2d::GetBodyType()
{
	if (m_Body != nullptr)
		return m_Body->GetType();
	return b2_staticBody;
}


float Body2d::GetMass()
{
	if (m_Body != nullptr)
	{
		return m_Body->GetMass();
	}
	return 0.0f;
}

void Body2d::AddForce(b2Vec2 f)
{
	if (m_Body != nullptr)
	{
		m_Body->ApplyForce(f, m_Body->GetPosition(), true);
	}
}




}

