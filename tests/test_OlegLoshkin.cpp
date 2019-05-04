#include <engine/engine.h>
#include <engine/scene.h>
#include <gtest/gtest.h>
#include "graphics/shape2d.h"
#include "physics/collider2d.h"

TEST(OlegLoshkin, ClockHands)
{
	// Init engine.
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	engine.Init(std::move(config));
	auto* sceneManager = engine.GetSceneManager();

	// Create entities.
	json sceneJson;
	sceneJson["name"] = "Clock Hands";
	
	// Create systems.
	json clockHandsSystem = {
		{ "script_path", "scripts/clock_hands_system.py" }
	};
	sceneJson["systems"] = json::array({clockHandsSystem});
	
	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, FloatingShapes)
{
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	engine.Init(std::move(config));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "Floating Shapes";

	// Creating entities.
	json rect;
	rect["name"] = "Rect";
	json rectTransform;
	rectTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	rectTransform["position"] = {426,240};
	rectTransform["scale"] = {10.0,10.0};
	rectTransform["angle"] = 45.0;
	json rectShape;
	rectShape["type"] = sfge::ComponentType::SHAPE2D;
	rectShape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShape["size"] = {20.0,20.0};
	rect["components"] = {rectTransform, rectShape};

	json circle;
	circle["name"] = "Circle";
	json circleTransform;
	circleTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform["position"] = {853,480};
	circleTransform["scale"] = {5.0,5.0};
	circleTransform["angle"] = 0.0;
	json circleShape;
	circleShape["type"] = sfge::ComponentType::SHAPE2D;
	circleShape["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShape["size"] = {1.0};
	circle["components"] = {circleTransform, circleShape};

	// Add entities to scene.
	sceneJson["entities"] = {rect, circle};

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, MovingShapes)
{
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	engine.Init(std::move(config));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "Moving Shapes";

	// Creating entities.
	json rect;
	rect["name"] = "Rect";
	json rectTransform;
	rectTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	rectTransform["position"] = {426,240};
	rectTransform["scale"] = {10.0,10.0};
	rectTransform["angle"] = 45.0;
	json rectShape;
	rectShape["type"] = sfge::ComponentType::SHAPE2D;
	rectShape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShape["size"] = {20.0,20.0};
	rect["components"] = {rectTransform, rectShape};

	json circle;
	circle["name"] = "Circle";
	json circleTransform;
	circleTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform["position"] = {853,480};
	circleTransform["scale"] = {5.0,5.0};
	circleTransform["angle"] = 0.0;
	json circleShape;
	circleShape["type"] = sfge::ComponentType::SHAPE2D;
	circleShape["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShape["size"] = {1.0};
	circle["components"] = {circleTransform, circleShape};

	// Add entities to scene.
	sceneJson["entities"] = {rect, circle};

	// Add debug 

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}