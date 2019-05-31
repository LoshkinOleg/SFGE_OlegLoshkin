#include <gtest/gtest.h>
#include <SFML\System\Vector2.hpp>
#include <engine/engine.h>
#include <engine/config.h>
#include <engine/scene.h>
#include <physics\body2d.h>
#include <graphics\shape2d.h>
#include <physics\collider2d.h>

TEST(OlegLoshkin, test_01)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "Vector Addition" }
	};

	json systemJson = {
			{"systemClassName", "Test_01_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, test_02)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "Vector Multiplication" }
	};

	json systemJson = {
			{"systemClassName", "Test_02_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, test_03)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "Vector Projection" }
	};

	json systemJson = {
			{"systemClassName", "Test_03_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, test_04)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "Lerping" }
	};

	json systemJson = {
			{"systemClassName", "Test_04_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, test_05)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 5);
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "Bodies and Forces" }
	};

	// Set up Entitites.
	json dynamic;
	dynamic["name"] = "Dynamic";
	json dynamic_transform;
	dynamic_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	dynamic_transform["position"] = { screenSize.x / 4.0f , screenSize.y * 2.0f / 3.0f };
	dynamic_transform["scale"] = { 1.0,1.0 };
	json dynamic_shape;
	dynamic_shape["type"] = sfge::ComponentType::SHAPE2D;
	dynamic_shape["shape_type"] = sfge::ShapeType::CIRCLE;
	dynamic_shape["size"] = 100;
	json dynamic_body;
	dynamic_body["type"] = sfge::ComponentType::BODY2D;
	dynamic_body["body_type"] = p2BodyType::DYNAMIC;
	dynamic_body["mass"] = 1;
	dynamic["components"] = { dynamic_transform, dynamic_shape, dynamic_body };

	json kinematic;
	kinematic["name"] = "Kinematic";
	json kinematic_transform;
	kinematic_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	kinematic_transform["position"] = { screenSize.x * 2.0f / 4.0f , screenSize.y * 2.0f / 3.0f };
	kinematic_transform["scale"] = { 1.0,1.0 };
	json kinematic_shape;
	kinematic_shape["type"] = sfge::ComponentType::SHAPE2D;
	kinematic_shape["shape_type"] = sfge::ShapeType::CIRCLE;
	kinematic_shape["size"] = 100;
	json kinematic_body;
	kinematic_body["type"] = sfge::ComponentType::BODY2D;
	kinematic_body["body_type"] = p2BodyType::KINEMATIC;
	kinematic_body["mass"] = 1;
	kinematic["components"] = { kinematic_transform, kinematic_shape, kinematic_body };

	json stat;
	stat["name"] = "Static";
	json stat_transform;
	stat_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	stat_transform["position"] = { screenSize.x * 3.0f / 4.0f , screenSize.y * 2.0f / 3.0f };
	stat_transform["scale"] = { 1.0,1.0 };
	json stat_shape;
	stat_shape["type"] = sfge::ComponentType::SHAPE2D;
	stat_shape["shape_type"] = sfge::ShapeType::CIRCLE;
	stat_shape["size"] = 100;
	json stat_body;
	stat_body["type"] = sfge::ComponentType::BODY2D;
	stat_body["body_type"] = p2BodyType::STATIC;
	stat_body["mass"] = 1;
	stat["components"] = { stat_transform, stat_shape, stat_body };

	sceneJson["entities"] = { dynamic, kinematic, stat };

	json systemJson = {
			{"systemClassName", "Test_05_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, test_06)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "AABBs and Colliders" }
	};

	// Set up Entitites.
	json circle;
	circle["name"] = "Circle";
	json circle_transform;
	circle_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	circle_transform["position"] = { screenSize.x * 0.5f , screenSize.y * 0.5f};
	circle_transform["scale"] = { 1.0,1.0 };
	json circle_body;
	circle_body["type"] = sfge::ComponentType::BODY2D;
	circle_body["body_type"] = p2BodyType::KINEMATIC;
	circle_body["mass"] = 1;
	json circle_shape;
	circle_shape["name"] = "Circle_Shape";
	circle_shape["type"] = sfge::ComponentType::SHAPE2D;
	circle_shape["shape_type"] = sfge::ShapeType::CIRCLE;
	circle_shape["radius"] = 100;
	json circle_collider;
	circle_collider["type"] = sfge::ComponentType::COLLIDER2D;
	circle_collider["collider_type"] = sfge::ColliderType::CIRCLE;
	circle_collider["radius"] = 100;
	circle["components"] = { circle_transform, circle_body, circle_shape, circle_collider };

	json rect;
	rect["name"] = "Rect";
	json rect_transform;
	rect_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	rect_transform["position"] = { screenSize.x * 0.5f , screenSize.y * 0.5f };
	rect_transform["scale"] = { 1.0,1.0 };
	json rect_body;
	rect_body["type"] = sfge::ComponentType::BODY2D;
	rect_body["body_type"] = p2BodyType::KINEMATIC;
	rect_body["mass"] = 1;
	json rect_shape;
	rect_shape["name"] = "Rect_Shape";
	rect_shape["type"] = sfge::ComponentType::SHAPE2D;
	rect_shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rect_shape["size"] = {100,100};
	json rect_collider;
	rect_collider["type"] = sfge::ComponentType::COLLIDER2D;
	rect_collider["collider_type"] = sfge::ColliderType::BOX;
	rect_collider["size"] = { 100,100 };
	rect["components"] = { rect_transform, rect_body, rect_shape, rect_collider };

	sceneJson["entities"] = { circle, rect };

	json systemJson = {
			{"systemClassName", "Test_06_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}