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
	json dynamic_collider;
	dynamic_collider["type"] = sfge::ComponentType::COLLIDER2D;
	dynamic_collider["collider_type"] = sfge::ColliderType::CIRCLE;
	dynamic_collider["radius"] = 10;
	dynamic_collider["sensor"] = false;
	dynamic["components"] = { dynamic_transform, dynamic_shape, dynamic_body, dynamic_collider };

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
	json kinematic_collider;
	kinematic_collider["type"] = sfge::ComponentType::COLLIDER2D;
	kinematic_collider["collider_type"] = sfge::ColliderType::CIRCLE;
	kinematic_collider["radius"] = 10;
	kinematic_collider["sensor"] = false;
	kinematic["components"] = { kinematic_transform, kinematic_shape, kinematic_body, kinematic_collider };

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
	json stat_collider;
	stat_collider["type"] = sfge::ComponentType::COLLIDER2D;
	stat_collider["collider_type"] = sfge::ColliderType::CIRCLE;
	stat_collider["radius"] = 10;
	stat_collider["sensor"] = false;
	stat["components"] = { stat_transform, stat_shape, stat_body, stat_collider };

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

TEST(OlegLoshkin, test_07)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	auto screenSize = initConfig->screenResolution;
	// initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 2;
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "QuadTree" }
	};

	// Set up jsons.
	json entities[256];
	json circle;
	json transform;
	transform["type"] = sfge::ComponentType::TRANSFORM2D;
	transform["scale"] = { 1.0,1.0 };
	json body;
	body["type"] = sfge::ComponentType::BODY2D;
	body["body_type"] = p2BodyType::KINEMATIC;
	body["mass"] = 1;
	json shape;
	shape["type"] = sfge::ComponentType::SHAPE2D;
	shape["shape_type"] = sfge::ShapeType::CIRCLE;
	shape["radius"] = 10;
	json collider;
	collider["type"] = sfge::ComponentType::COLLIDER2D;
	collider["collider_type"] = sfge::ColliderType::CIRCLE;
	collider["radius"] = 10,10;
	collider["sensor"] = true;

	// Set up entities.
	for (size_t i = 0; i < 256; i++)
	{
		circle["name"] = "Circle_" + std::to_string(i);
		transform["position"] = { rand() % screenSize.x , rand() % screenSize.y }; // Random position on screen.
		// Code taken from https://stackoverflow.com/questions/686353/random-float-number-generation
		body["velocity"] = { -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))), -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))) }; // Random velocity with X and Y components between -1 and 1;
		circle["components"] = { transform, body, shape, collider };
		entities[i] = circle;
	}
	sceneJson["entities"] = entities;

	json systemJson = {
			{"systemClassName", "Test_07_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, test_08)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "Circle vs Circle" }
	};

	// Set up Entitites.
	json entities[4];

	json circle0;
	circle0["name"] = "Circle_0";
	json circle0_transform;
	circle0_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	circle0_transform["position"] = { screenSize.x / 3.0f , screenSize.y / 3.0f };
	circle0_transform["scale"] = { 1.0,1.0 };
	json circle0_body;
	circle0_body["type"] = sfge::ComponentType::BODY2D;
	circle0_body["body_type"] = p2BodyType::DYNAMIC;
	circle0_body["mass"] = 1;
	circle0_body["velocity"] = {4,0};
	json circle0_shape;
	circle0_shape["type"] = sfge::ComponentType::SHAPE2D;
	circle0_shape["shape_type"] = sfge::ShapeType::CIRCLE;
	circle0_shape["radius"] = 100;
	json circle0_collider;
	circle0_collider["type"] = sfge::ComponentType::COLLIDER2D;
	circle0_collider["collider_type"] = sfge::ColliderType::CIRCLE;
	circle0_collider["radius"] = 100;
	circle0_collider["sensor"] = false;
	circle0["components"] = { circle0_transform, circle0_body, circle0_shape, circle0_collider };
	entities[0] = circle0;

	json circle1;
	circle1["name"] = "Circle_1";
	json circle1_transform;
	circle1_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	circle1_transform["position"] = { screenSize.x * 2 / 3.0f , screenSize.y / 3.0f };
	circle1_transform["scale"] = { 1.0,1.0 };
	json circle1_body;
	circle1_body["type"] = sfge::ComponentType::BODY2D;
	circle1_body["body_type"] = p2BodyType::DYNAMIC;
	circle1_body["mass"] = 0.5f;
	json circle1_shape;
	circle1_shape["type"] = sfge::ComponentType::SHAPE2D;
	circle1_shape["shape_type"] = sfge::ShapeType::CIRCLE;
	circle1_shape["radius"] = 50;
	json circle1_collider;
	circle1_collider["type"] = sfge::ComponentType::COLLIDER2D;
	circle1_collider["collider_type"] = sfge::ColliderType::CIRCLE;
	circle1_collider["radius"] = 50;
	circle1_collider["sensor"] = false;
	circle1["components"] = { circle1_transform, circle1_body, circle1_shape, circle1_collider };
	entities[1] = circle1;

	json circle2;
	circle2["name"] = "Circle_2";
	json circle2_transform;
	circle2_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	circle2_transform["position"] = { screenSize.x / 3.0f , screenSize.y * 2 / 3.0f };
	circle2_transform["scale"] = { 1.0,1.0 };
	json circle2_body;
	circle2_body["type"] = sfge::ComponentType::BODY2D;
	circle2_body["body_type"] = p2BodyType::DYNAMIC;
	circle2_body["mass"] = 1;
	circle2_body["velocity"] = { 4,0 };
	circle2_body["restitution"] = 0.8f;
	json circle2_shape;
	circle2_shape["type"] = sfge::ComponentType::SHAPE2D;
	circle2_shape["shape_type"] = sfge::ShapeType::CIRCLE;
	circle2_shape["radius"] = 100;
	json circle2_collider;
	circle2_collider["type"] = sfge::ComponentType::COLLIDER2D;
	circle2_collider["collider_type"] = sfge::ColliderType::CIRCLE;
	circle2_collider["radius"] = 100;
	circle2_collider["sensor"] = false;
	circle2["components"] = { circle2_transform, circle2_body, circle2_shape, circle2_collider };
	entities[2] = circle2;

	json circle3;
	circle3["name"] = "Circle_3";
	json circle3_transform;
	circle3_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	circle3_transform["position"] = { screenSize.x * 2 / 3.0f , screenSize.y * 2 / 3.0f };
	circle3_transform["scale"] = { 1.0,1.0 };
	json circle3_body;
	circle3_body["type"] = sfge::ComponentType::BODY2D;
	circle3_body["body_type"] = p2BodyType::DYNAMIC;
	circle3_body["mass"] = 0.5f;
	circle2_body["restitution"] = 0.8f;
	json circle3_shape;
	circle3_shape["type"] = sfge::ComponentType::SHAPE2D;
	circle3_shape["shape_type"] = sfge::ShapeType::CIRCLE;
	circle3_shape["radius"] = 50;
	json circle3_collider;
	circle3_collider["type"] = sfge::ComponentType::COLLIDER2D;
	circle3_collider["collider_type"] = sfge::ColliderType::CIRCLE;
	circle3_collider["radius"] = 50;
	circle3_collider["sensor"] = false;
	circle3["components"] = { circle3_transform, circle3_body, circle3_shape, circle3_collider };
	entities[3] = circle3;

	sceneJson["entities"] = entities;

	json systemJson = {
			{"systemClassName", "Test_08_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, test_09)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 2;
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "Many Circles" }
	};

	// Set up jsons.
	json entities[256];
	json circle;
	json transform;
	transform["type"] = sfge::ComponentType::TRANSFORM2D;
	transform["scale"] = { 1.0,1.0 };
	json body;
	body["type"] = sfge::ComponentType::BODY2D;
	body["body_type"] = p2BodyType::DYNAMIC;
	body["mass"] = 1;
	json shape;
	shape["type"] = sfge::ComponentType::SHAPE2D;
	shape["shape_type"] = sfge::ShapeType::CIRCLE;
	shape["radius"] = 10;
	json collider;
	collider["type"] = sfge::ComponentType::COLLIDER2D;
	collider["collider_type"] = sfge::ColliderType::CIRCLE;
	collider["radius"] = 10;
	collider["sensor"] = false;

	// Set up entities.
	for (size_t i = 0; i < 256; i++)
	{
		circle["name"] = "Circle_" + std::to_string(i);
		transform["position"] = { rand() % screenSize.x , rand() % screenSize.y }; // Random position on screen.
		// Code taken from https://stackoverflow.com/questions/686353/random-float-number-generation
		body["velocity"] = { -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))), -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))) }; // Random velocity with X and Y components between -1 and 1;
		circle["components"] = { transform, body, shape, collider };
		entities[i] = circle;
	}
	sceneJson["entities"] = entities;

	json systemJson = {
			{"systemClassName", "Test_09_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, test_10)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "Rect vs Rect" }
	};

	// Set up Entitites.
	json entities[4];

	json rect0;
	rect0["name"] = "Rect_0";
	json rect0_transform;
	rect0_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	rect0_transform["position"] = { screenSize.x / 3.0f , screenSize.y / 3.0f };
	rect0_transform["scale"] = { 1.0,1.0 };
	json rect0_body;
	rect0_body["type"] = sfge::ComponentType::BODY2D;
	rect0_body["body_type"] = p2BodyType::DYNAMIC;
	rect0_body["mass"] = 1;
	rect0_body["velocity"] = { 4,0 };
	json rect0_shape;
	rect0_shape["type"] = sfge::ComponentType::SHAPE2D;
	rect0_shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rect0_shape["size"] = { 200,200 };
	json rect0_collider;
	rect0_collider["type"] = sfge::ComponentType::COLLIDER2D;
	rect0_collider["collider_type"] = sfge::ColliderType::BOX;
	rect0_collider["size"] = { 200,200 };
	rect0_collider["sensor"] = false;
	rect0["components"] = { rect0_transform, rect0_body, rect0_shape, rect0_collider };
	entities[0] = rect0;

	json rect1;
	rect1["name"] = "Rect_1";
	json rect1_transform;
	rect1_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	rect1_transform["position"] = { screenSize.x * 2 / 3.0f , screenSize.y / 3.0f };
	rect1_transform["scale"] = { 1.0,1.0 };
	json rect1_body;
	rect1_body["type"] = sfge::ComponentType::BODY2D;
	rect1_body["body_type"] = p2BodyType::DYNAMIC;
	rect1_body["mass"] = 0.5f;
	json rect1_shape;
	rect1_shape["type"] = sfge::ComponentType::SHAPE2D;
	rect1_shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rect1_shape["size"] = { 100,100 };
	json rect1_collider;
	rect1_collider["type"] = sfge::ComponentType::COLLIDER2D;
	rect1_collider["collider_type"] = sfge::ColliderType::BOX;
	rect1_collider["size"] = { 100,100 };
	rect1_collider["sensor"] = false;
	rect1["components"] = { rect1_transform, rect1_body, rect1_shape, rect1_collider };
	entities[1] = rect1;

	json rect2;
	rect2["name"] = "Rect_2";
	json rect2_transform;
	rect2_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	rect2_transform["position"] = { screenSize.x / 3.0f , screenSize.y * 2 / 3.0f };
	rect2_transform["scale"] = { 1.0,1.0 };
	json rect2_body;
	rect2_body["type"] = sfge::ComponentType::BODY2D;
	rect2_body["body_type"] = p2BodyType::DYNAMIC;
	rect2_body["mass"] = 1;
	rect2_body["velocity"] = { 4,0 };
	rect2_body["restitution"] = 0.8f;
	json rect2_shape;
	rect2_shape["type"] = sfge::ComponentType::SHAPE2D;
	rect2_shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rect2_shape["size"] = { 200,200 };
	json rect2_collider;
	rect2_collider["type"] = sfge::ComponentType::COLLIDER2D;
	rect2_collider["collider_type"] = sfge::ColliderType::BOX;
	rect2_collider["size"] = { 200,200 };
	rect2_collider["sensor"] = false;
	rect2["components"] = { rect2_transform, rect2_body, rect2_shape, rect2_collider };
	entities[2] = rect2;

	json rect3;
	rect3["name"] = "Rect_3";
	json rect3_transform;
	rect3_transform["type"] = sfge::ComponentType::TRANSFORM2D;
	rect3_transform["position"] = { screenSize.x * 2 / 3.0f , screenSize.y * 2 / 3.0f };
	rect3_transform["scale"] = { 1.0,1.0 };
	json rect3_body;
	rect3_body["type"] = sfge::ComponentType::BODY2D;
	rect3_body["body_type"] = p2BodyType::DYNAMIC;
	rect3_body["mass"] = 0.5f;
	rect2_body["restitution"] = 0.8f;
	json rect3_shape;
	rect3_shape["type"] = sfge::ComponentType::SHAPE2D;
	rect3_shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	rect3_shape["size"] = { 100,100 };
	json rect3_collider;
	rect3_collider["type"] = sfge::ComponentType::COLLIDER2D;
	rect3_collider["collider_type"] = sfge::ColliderType::BOX;
	rect3_collider["size"] = { 100,100 };
	rect3_collider["sensor"] = false;
	rect3["components"] = { rect3_transform, rect3_body, rect3_shape, rect3_collider };
	entities[3] = rect3;

	sceneJson["entities"] = entities;

	json systemJson = {
			{"systemClassName", "Test_10_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, test_11)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 2;
	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();

	json sceneJson = {
			{ "name", "Many Rects" }
	};

	// Set up jsons.
	json entities[256];
	json rect;
	json transform;
	transform["type"] = sfge::ComponentType::TRANSFORM2D;
	transform["scale"] = { 1.0,1.0 };
	json body;
	body["type"] = sfge::ComponentType::BODY2D;
	body["body_type"] = p2BodyType::DYNAMIC;
	body["mass"] = 1;
	json shape;
	shape["type"] = sfge::ComponentType::SHAPE2D;
	shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	shape["size"] = {10,10};
	json collider;
	collider["type"] = sfge::ComponentType::COLLIDER2D;
	collider["collider_type"] = sfge::ColliderType::BOX;
	collider["size"] = { 10,10 };
	collider["sensor"] = false;

	// Set up entities.
	for (size_t i = 0; i < 256; i++)
	{
		rect["name"] = "Rect_" + std::to_string(i);
		transform["position"] = { rand() % screenSize.x , rand() % screenSize.y }; // Random position on screen.
		// Code taken from https://stackoverflow.com/questions/686353/random-float-number-generation
		body["velocity"] = { -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))), -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))) }; // Random velocity with X and Y components between -1 and 1;
		rect["components"] = { transform, body, shape, collider };
		entities[i] = rect;
	}
	sceneJson["entities"] = entities;

	json systemJson = {
			{"systemClassName", "Test_11_System"}
	};
	sceneJson["systems"] = json::array({ systemJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}