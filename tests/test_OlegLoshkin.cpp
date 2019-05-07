#include <engine/engine.h>
#include <engine/scene.h>
#include <gtest/gtest.h>
#include "graphics/shape2d.h"
#include "physics/collider2d.h"
#include <SFML/System/Vector2.hpp>

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
	circleShape["size"] = 50.0;
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

TEST(OlegLoshkin, FallingRectangle)
{
	// Init engine.
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	engine.Init(std::move(config));
	auto* sceneManager = engine.GetSceneManager();

	// Create scene.
	json sceneJson;
	sceneJson["name"] = "Falling Rectangle";

	// Creating entities.
	// Cleate empty entity since the engine needs at least two.
	json emptyEntity;
	emptyEntity["name"] = "EmptyEntity";
	json empty_0;
	json empty_1;
	empty_0["type"] = sfge::ComponentType::TRANSFORM2D;
	empty_1["type"] = sfge::ComponentType::TRANSFORM2D;
	emptyEntity["components"] = {empty_0, empty_1};
	// Create rect.
	json rect;
	rect["name"] = "Rect_0";
	json rectTransform;
	rectTransform["type"] = sfge::ComponentType::TRANSFORM2D;
	rectTransform["position"] = {426,240};
	rectTransform["scale"] = {5.0,5.0};
	rectTransform["angle"] = 0.0;
	json rectShape;
	rectShape["type"] = sfge::ComponentType::SHAPE2D;
	rectShape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShape["size"] = {20.0,20.0};
	json rectBody;
	rectBody["type"] = sfge::ComponentType::BODY2D;
	rectBody["body_type"] = p2BodyType::DYNAMIC;
	rectBody["gravity_scale"] = 1;
	rectBody["offset"] = {0, 0};
	rectBody["velocity"] = {0, 0};
	json rectCollider;
	rectCollider["name"] = "Rect's Collider!";
	rectCollider["type"] = sfge::ComponentType::COLLIDER2D;
	rectCollider["collider_type"] = sfge::ColliderType::BOX;
	rectCollider["size"] = {20.0,20.0};
	rectCollider["sensor"] = true;
	rect["components"] = {rectTransform, rectShape, rectBody, rectCollider};

	// Add entities to scene.
	sceneJson["entities"] = {rect, emptyEntity};

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, SeparatingAxisTheorem)
{
	// Init engine.
	sfge::Engine engine;
	sf::Vector2i resolution = sf::Vector2i(1280,720);
	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	config->screenResolution = resolution;
	engine.Init(std::move(config));
	auto* sceneManager = engine.GetSceneManager();

	// Create scene.
	json sceneJson;
	sceneJson["name"] = "SAT Demo";

	// Creating entities.
	// Create rect.
	json rect_0;
	rect_0["name"] = "Rect_0";
	json rectTransform_0;
	rectTransform_0["type"] = sfge::ComponentType::TRANSFORM2D;
	rectTransform_0["position"] = {resolution.x / 2, resolution.y / 2};
	rectTransform_0["scale"] = {5.0,5.0};
	rectTransform_0["angle"] = 0.0;
	json rectShape_0;
	rectShape_0["type"] = sfge::ComponentType::SHAPE2D;
	rectShape_0["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShape_0["size"] = {20.0,20.0};
	json rectBody_0;
	rectBody_0["type"] = sfge::ComponentType::BODY2D;
	rectBody_0["body_type"] = p2BodyType::DYNAMIC;
	rectBody_0["aabb"] = {100,100};
	rectBody_0["gravity_scale"] = 0;
	rectBody_0["offset"] = { 0, 0 };
	rectBody_0["velocity"] = { 0, 0 };
	json rectCollider_0;
	rectCollider_0["type"] = sfge::ComponentType::COLLIDER2D;
	rectCollider_0["collider_type"] = sfge::ColliderType::BOX;
	rectCollider_0["size"] = {20.0,20.0};
	rectCollider_0["sensor"] = true;
	rect_0["components"] = { rectTransform_0, rectShape_0, rectBody_0, rectCollider_0 };

	json rect_1;
	rect_1["name"] = "Rect_1";
	json rectTransform_1;
	rectTransform_1["type"] = sfge::ComponentType::TRANSFORM2D;
	rectTransform_1["position"] = {resolution.x / 3, resolution.y / 3};
	rectTransform_1["scale"] = {5.0,5.0};
	rectTransform_1["angle"] = 0.0;
	json rectShape_1;
	rectShape_1["type"] = sfge::ComponentType::SHAPE2D;
	rectShape_1["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShape_1["size"] = {20.0,20.0};
	json rectBody_1;
	rectBody_1["type"] = sfge::ComponentType::BODY2D;
	rectBody_1["body_type"] = p2BodyType::DYNAMIC;
	rectBody_1["aabb"] = {100,100};
	rectBody_1["gravity_scale"] = 0;
	rectBody_1["offset"] = {0, 0};
	rectBody_1["velocity"] = {0, 0};
	json rectCollider_1;
	rectCollider_1["type"] = sfge::ComponentType::COLLIDER2D;
	rectCollider_1["collider_type"] = sfge::ColliderType::BOX;
	rectCollider_1["size"] = {20.0,20.0};
	rectCollider_1["sensor"] = true;
	rect_1["components"] = {rectTransform_1, rectShape_1, rectBody_1, rectCollider_1};

	// Add entities to scene.
	sceneJson["entities"] = {rect_0, rect_1};

	// Create systems.
	json satDemoSystem = {
		{ "script_path", "scripts/sat_demo_system.py" }
	};
	sceneJson["systems"] = json::array({satDemoSystem});

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, ContactRectsVsRectsCirclesVsCircles)
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
	json contactRectsVsRectsCirclesVsCircles = {
		{ "script_path", "scripts/contact_rects_vs_rects_circles_vs_circles_system.py" }
	};
	sceneJson["systems"] = json::array({contactRectsVsRectsCirclesVsCircles});

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
};