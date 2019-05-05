#include <engine/engine.h>
#include <engine/scene.h>
#include <gtest/gtest.h>
#include "graphics/shape2d.h"
#include "physics/collider2d.h"

// Display resolution: 1280[px] x 720[px]

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
	rectTransform["position"] = {426,240}; // 1280 / 3 = 426, 720 / 3 = 240
	rectTransform["scale"] = {10.0,10.0};
	rectTransform["angle"] = 45.0;
	json rectShape;
	rectShape["type"] = sfge::ComponentType::SHAPE2D;
	rectShape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShape["size"] = {20.0,20.0}; // Rect side length of 20 = 2 Circle's radiuses of 1. For god knows what reason...
	rect["components"] = {rectTransform, rectShape};

	json circle;
	circle["name"] = "Circle";
	json circleTransform;
	circleTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform["position"] = {853,480}; // (1280 / 3) * 2 = 853, (720 / 3) * 2 = 480
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

TEST(OlegLoshkin, Lerping)
{
	// Init engine.
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	engine.Init(std::move(config));
	auto* sceneManager = engine.GetSceneManager();

	// Create scene.
	json sceneJson;
	sceneJson["name"] = "Lerping";

	// Create systems.
	json lerpingSystem = {
		{ "systemClassName", "LerpingSystem" }
	};
	sceneJson["systems"] = json::array({lerpingSystem});

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, LerpingShapes)
{
	// Init engine.
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	engine.Init(std::move(config));
	auto* sceneManager = engine.GetSceneManager();

	// Create scene.
	json sceneJson;
	sceneJson["name"] = "Lerping Shapes";

	// Creating entities.
	// Rects.
	json rect_0;
	json rect_1;
	rect_0["name"] = "Rect_0";
	rect_1["name"] = "Rect_1";
	json rectTransform_0;
	json rectTransform_1;
	rectTransform_0["type"] = sfge::ComponentType::TRANSFORM2D;
	rectTransform_1["type"] = sfge::ComponentType::TRANSFORM2D;
	rectTransform_0["position"] = {426,240};
	rectTransform_1["position"] = {853,240};
	rectTransform_0["scale"] = {5.0,5.0};
	rectTransform_1["scale"] = {5.0,5.0};
	rectTransform_0["angle"] = 0.0;
	rectTransform_1["angle"] = 0.0;
	json rectShape;
	rectShape["type"] = sfge::ComponentType::SHAPE2D;
	rectShape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShape["size"] = {20.0,20.0};
	rect_0["components"] = {rectTransform_0, rectShape};
	rect_1["components"] = {rectTransform_1, rectShape};

	// Circles.
	json circle_0;
	json circle_1;
	circle_0["name"] = "Circle_0";
	circle_1["name"] = "Circle_1";
	json circleTransform_0;
	json circleTransform_1;
	circleTransform_0["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform_1["type"] = sfge::ComponentType::TRANSFORM2D;
	circleTransform_0["position"] = {426,480};
	circleTransform_1["position"] = {853,480};
	circleTransform_0["scale"] = {5.0,5.0};
	circleTransform_1["scale"] = {5.0,5.0};
	circleTransform_0["angle"] = 0.0;
	circleTransform_1["angle"] = 0.0;
	json circleShape;
	circleShape["type"] = sfge::ComponentType::SHAPE2D;
	circleShape["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShape["size"] = {1.0};
	circle_0["components"] = {circleTransform_0, circleShape};
	circle_1["components"] = {circleTransform_1, circleShape};

	// Add entities to scene.
	sceneJson["entities"] = {rect_0, rect_1, circle_0, circle_1};

	// Create systems.
	json pythonLerpingSystem = {
		{ "script_path", "scripts/lerping_shapes_system.py" }
	};
	sceneJson["systems"] = json::array({pythonLerpingSystem});

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}