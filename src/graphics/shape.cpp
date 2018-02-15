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

#include <graphics/graphics.h>
#include <graphics/shape.h>
#include <utility/json_utility.h>
#include <engine/log.h>
#include <engine/transform.h>

namespace sfge
{

Shape::Shape(GameObject* gameObject, sf::Vector2f offset):
		Component(gameObject)
{
	m_Offset = offset;
}

void Shape::Init()
{
}

void Shape::Update(float time)
{
	if (m_Shape != nullptr)
	{
		m_Shape->setPosition(m_GameObject->GetTransform()->GetPosition() + m_Offset);
	}
}

void Shape::Draw(sf::RenderWindow& window)
{
	if(m_Shape != nullptr)
	{
		window.draw(*m_Shape);
	}
}


Shape* Shape::LoadShape(Engine& engine, json& componentJson, GameObject* gameObject)
{
	Shape* shape = nullptr;
	sf::Vector2f offset;
	if(CheckJsonParameter(componentJson, "offset", json::value_t::array))
	{
		if(componentJson["offset"].size() == 2)
		{
			offset = sf::Vector2f(componentJson["offset"][0], componentJson["offset"][1]);
		}
	}

	if(CheckJsonNumber(componentJson, "shape_type"))
	{
		ShapeType shapeType = (ShapeType)componentJson["shape_type"];
		switch(shapeType)
		{
		case ShapeType::CIRCLE:
			shape = Circle::LoadCircle(componentJson, gameObject, offset);
			break;
		case ShapeType::RECTANGLE:
			shape = Rectangle::LoadRectangle(componentJson, gameObject, offset);
			break;

		}
	}
	if(shape != nullptr)
	{
		{
			Log::GetInstance()->Msg("Load shape");
		}
		auto graphicsManager = std::dynamic_pointer_cast<GraphicsManager>(
				engine.GetModule(EngineModule::GRAPHICS_MANAGER));
		graphicsManager->GetShapeManager()->AddShape(shape);
	}
	return shape;
}

Circle::Circle(GameObject* gameObject,  sf::Vector2f position, float radius):
		Shape(gameObject,  position)
{
	m_Radius = radius;
	m_Shape = std::make_shared<sf::CircleShape>(radius);
	m_Shape->setFillColor(sf::Color::Green);
	m_Shape->setPosition(position);
}



Circle* Circle::LoadCircle(json& componentJson, GameObject* gameObject, sf::Vector2f offset)
{
	float radius = 1.0f;

	if(CheckJsonNumber(componentJson, "radius"))
	{
		radius = componentJson["radius"];
	}

	return new Circle(gameObject, offset, radius);

}
Rectangle::Rectangle(GameObject* gameObject, sf::Vector2f position, sf::Vector2f size):
		Shape(gameObject, position)
{
	m_Size = size;
	m_Shape = std::make_shared<sf::RectangleShape>(size);
	m_Shape->setFillColor(sf::Color::Red);
	m_Shape->setPosition(position);
}

Rectangle* Rectangle::LoadRectangle(json& componentJson, GameObject* gameObject, sf::Vector2f position)
{

	sf::Vector2f size;
	if(CheckJsonParameter(componentJson, "size", json::value_t::array))
	{
		if(componentJson["size"].size() == 2)
		{
			size = sf::Vector2f(componentJson["size"][0], componentJson["size"][1]);
		}
	}
	return new Rectangle(gameObject,  position, size);
}


ShapeManager::ShapeManager(GraphicsManager& graphicsManager):
		m_GraphicsManager(graphicsManager)
{

}


void ShapeManager::Draw(sf::RenderWindow& window)
{
	for(auto shape : m_Shapes)
	{
		shape->Draw(window);
	}
}

void ShapeManager::AddShape(Shape* shape)
{
	m_Shapes.push_back(shape);
}


}