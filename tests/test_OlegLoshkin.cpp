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

TEST(OlegLoshkin, BodiesAndForces)
{
	// Set up engine.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0.0f, 0.05f);
	engine.Init(std::move(initConfig));

	// Set up scene.
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
			{ "name", "Bodies and Forces" }
	};

	// Set up Entitites.
	json dynamicRect;
	dynamicRect["name"] = "Dynamic Rect";
	json dynamicRect_Transform;
	dynamicRect_Transform["type"] = sfge::ComponentType::TRANSFORM2D;
	dynamicRect_Transform["position"] = { screenSize.x/3 , screenSize.y/3 };
	dynamicRect_Transform["scale"] = {1.0,1.0};
	dynamicRect_Transform["angle"] = 0.0;
	json dynamicRect_Shape;
	dynamicRect_Shape["type"] = sfge::ComponentType::SHAPE2D;
	dynamicRect_Shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	dynamicRect_Shape["size"] = { 100,100 };
	json dynamicRect_Body;
	dynamicRect_Body["type"] = sfge::ComponentType::BODY2D;
	dynamicRect_Body["body_type"] = p2BodyType::DYNAMIC;
	dynamicRect["components"] = { dynamicRect_Transform, dynamicRect_Shape, dynamicRect_Body };

	json kinematicRect;
	kinematicRect["name"] = "Kinematic Rect";
	json kinematicRect_Transform;
	kinematicRect_Transform["type"] = sfge::ComponentType::TRANSFORM2D;
	kinematicRect_Transform["position"] = {2 * screenSize.x / 3 , screenSize.y / 3};
	kinematicRect_Transform["scale"] = {1.0,1.0};
	kinematicRect_Transform["angle"] = 0.0;
	json kinematicRect_Shape;
	kinematicRect_Shape["type"] = sfge::ComponentType::SHAPE2D;
	kinematicRect_Shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	kinematicRect_Shape["size"] = {100,100};
	json kinematicRect_Body;
	kinematicRect_Body["type"] = sfge::ComponentType::BODY2D;
	kinematicRect_Body["body_type"] = p2BodyType::KINEMATIC;
	kinematicRect["components"] = {kinematicRect_Transform, kinematicRect_Shape, kinematicRect_Body};

	json staticRect;
	staticRect["name"] = "Kinematic Rect";
	json staticRect_Transform;
	staticRect_Transform["type"] = sfge::ComponentType::TRANSFORM2D;
	staticRect_Transform["position"] = {screenSize.x / 2 , 2 * screenSize.y / 3};
	staticRect_Transform["scale"] = {1.0,1.0};
	staticRect_Transform["angle"] = 0.0;
	json staticRect_Shape;
	staticRect_Shape["type"] = sfge::ComponentType::SHAPE2D;
	staticRect_Shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	staticRect_Shape["size"] = {100,100};
	json staticRect_Body;
	staticRect_Body["type"] = sfge::ComponentType::BODY2D;
	staticRect_Body["body_type"] = p2BodyType::STATIC;
	staticRect["components"] = {staticRect_Transform, staticRect_Shape, staticRect_Body};

	sceneJson["entities"] = { dynamicRect, kinematicRect, staticRect };

	// Set up systems.
	json systemJson = {
			{"script_path", "scripts/test_forces_system.py"}
	};
	sceneJson["systems"] = json::array({systemJson});

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, QuadTree)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	initConfig->gravity = p2Vec2(0,0);
	auto screenSize = sf::Vector2i(1280,720);
	engine.Init(std::move(initConfig));

	// Set up scene.
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
			{ "name", "p2Vec2 Testing" }
	};

	// Create entities.
	json entities[64];
	for (int i = 0; i < 64; i++)
	{
		json rect;
		rect["name"] = "Rect_" + std::to_string(i);
		json transform;
		transform["type"] = sfge::ComponentType::TRANSFORM2D;
		transform["position"] = { rand() % screenSize.x, rand() % screenSize.y };
		transform["scale"] = { 1.0,1.0 };
		json shape;
		shape["type"] = sfge::ComponentType::SHAPE2D;
		shape["shape_type"] = sfge::ShapeType::RECTANGLE;
		shape["size"] = { 10.0,10.0 };
		json body;
		body["type"] = sfge::ComponentType::BODY2D;
		body["body_type"] = p2BodyType::DYNAMIC;
		// rect["components"] = { transform, shape, body };
		json collider;
		collider["type"] = sfge::ComponentType::COLLIDER2D;
		collider["collider_type"] = sfge::ColliderType::BOX;
		collider["size"] = {10.0,10.0};
		collider["sensor"] = false;

		rect["components"] = {transform, shape, body, collider};
		entities[i] = rect;
	}

	sceneJson["entities"] = entities;

	// Set up systems.
	json systemJson = {
			{"script_path", "scripts/test_quadtree_system.py"}
	};
	sceneJson["systems"] = json::array({systemJson});

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, BroadPhase)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 3;
	auto screenSize = sf::Vector2i(1280, 720);
	engine.Init(std::move(initConfig));

	// Set up scene.
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
			{ "name", "BroadPhase" }
	};

	/*
	// Create entities.
	const int ROWS = 3;
	const int COLUMNS = 5;
	float spacingX = screenSize.x / (float)COLUMNS;
	float spacingY = screenSize.y / (float)ROWS;

	json entities[(ROWS * COLUMNS) + 1];
	json rect;
	json transform;
	transform["type"] = sfge::ComponentType::TRANSFORM2D;
	transform["scale"] = { 1.0,1.0 };
	json shape;
	shape["type"] = sfge::ComponentType::SHAPE2D;
	shape["shape_type"] = sfge::ShapeType::RECTANGLE;
	shape["size"] = { 100.0,100.0 };
	json collider;
	collider["type"] = sfge::ComponentType::COLLIDER2D;
	collider["collider_type"] = sfge::ColliderType::BOX;
	collider["size"] = { 100.0,100.0 };
	collider["sensor"] = false;
	json body;
	body["type"] = sfge::ComponentType::BODY2D;
	body["body_type"] = p2BodyType::DYNAMIC;

	int entityCounter = 0;
	for (size_t x = 1; x <= COLUMNS; x++)
	{
		for (size_t y = 1; y <= ROWS; y++)
		{
			rect["name"] = "Rect_" + std::to_string(COLUMNS) + ":" + std::to_string(ROWS);
			transform["position"] = { spacingX * x - (spacingX / 2.0f), spacingY * y - (spacingY / 2.0f) };
			rect["components"] = { transform, shape, body, collider };
			entities[entityCounter++] = rect;
		}
	}

	rect["name"] = "MovingRect";
	transform["position"] = { 51.0,51.0 };
	body["velocity"] = {1.0,5.0};
	rect["components"] = { transform, shape, body, collider };
	entities[entityCounter] = rect;
	*/

	// Create entities.
	json entities[16];
	for (int i = 0; i < 16; i++)
	{
		json rect;
		rect["name"] = "Rect_" + std::to_string(i);
		json transform;
		transform["type"] = sfge::ComponentType::TRANSFORM2D;
		transform["position"] = { rand() % screenSize.x, rand() % screenSize.y };
		transform["scale"] = { 1.0,1.0 };
		json shape;
		shape["type"] = sfge::ComponentType::SHAPE2D;
		shape["shape_type"] = sfge::ShapeType::RECTANGLE;
		shape["size"] = { 100.0,100.0 };
		json body;
		body["type"] = sfge::ComponentType::BODY2D;
		body["body_type"] = p2BodyType::DYNAMIC;
		json collider;
		collider["type"] = sfge::ComponentType::COLLIDER2D;
		collider["collider_type"] = sfge::ColliderType::BOX;
		collider["size"] = { 100.0,100.0 };
		collider["sensor"] = false;

		rect["components"] = { transform, shape, body, collider };
		entities[i] = rect;
	}

	sceneJson["entities"] = entities;

	// Set up systems.
	json systemJson = {
			{"systemClassName", "TestBroadPhaseSystem"}
	};
	sceneJson["systems"] = json::array({systemJson});

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, SpheresPerpetualCollisions)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 3;
	auto screenSize = sf::Vector2i(1280, 720);
	engine.Init(std::move(initConfig));

	// Set up scene.
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
			{ "name", "Spheres Perpetual Collisions" }
	};

	// Create entities.
	json entities[2];
	json circle;
	json transform;
	json shape;
	json body;
	json collider;

	circle["name"] = "Circle_0";
	transform["type"] = sfge::ComponentType::TRANSFORM2D;
	transform["position"] = { screenSize.x / 3.0f, screenSize.y / 2.0f };
	transform["scale"] = { 1.0,1.0 };
	shape["type"] = sfge::ComponentType::SHAPE2D;
	shape["shape_type"] = sfge::ShapeType::CIRCLE;
	shape["radius"] = 50;
	body["type"] = sfge::ComponentType::BODY2D;
	body["body_type"] = p2BodyType::DYNAMIC;
	body["velocity"] = { 20,0 };
	body["mass"] = 1;
	collider["type"] = sfge::ComponentType::COLLIDER2D;
	collider["collider_type"] = sfge::ColliderType::CIRCLE;
	collider["radius"] = 50;
	collider["sensor"] = false;
	circle["components"] = { transform, shape, body, collider };
	entities[0] = circle;

	circle["name"] = "Circle_1";
	transform["type"] = sfge::ComponentType::TRANSFORM2D;
	transform["position"] = { 2.0f * screenSize.x / 3.0f, screenSize.y / 2.0f };
	transform["scale"] = { 1.0,1.0 };
	shape["type"] = sfge::ComponentType::SHAPE2D;
	shape["shape_type"] = sfge::ShapeType::CIRCLE;
	shape["radius"] = 100;
	body["type"] = sfge::ComponentType::BODY2D;
	body["body_type"] = p2BodyType::DYNAMIC;
	body["velocity"] = {0,0};
	body["mass"] = 2;
	collider["type"] = sfge::ComponentType::COLLIDER2D;
	collider["collider_type"] = sfge::ColliderType::CIRCLE;
	collider["radius"] = 100;
	collider["sensor"] = false;
	circle["components"] = { transform, shape, body, collider };
	entities[1] = circle;

	sceneJson["entities"] = entities;

	// Set up systems.
	json systemJson = {
			{"systemClassName", "TestCollisionsSystem"}
	};
	sceneJson["systems"] = json::array({ systemJson });

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, Collisions)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 3;
	auto screenSize = sf::Vector2i(1280, 720);
	engine.Init(std::move(initConfig));

	// Set up scene.
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
			{ "name", "Collisions" }
	};

	// Create entities.
	json entities[16];
	for (int i = 0; i < 16; i++)
	{
		json circle;
		circle["name"] = "Circle_" + std::to_string(i);
		json transform;
		transform["type"] = sfge::ComponentType::TRANSFORM2D;
		transform["position"] = { rand() % screenSize.x, rand() % screenSize.y };
		transform["scale"] = { 1.0,1.0 };
		json shape;
		shape["type"] = sfge::ComponentType::SHAPE2D;
		shape["shape_type"] = sfge::ShapeType::CIRCLE;
		shape["size"] = 100;
		json body;
		body["type"] = sfge::ComponentType::BODY2D;
		body["body_type"] = p2BodyType::DYNAMIC;
		json collider;
		collider["type"] = sfge::ComponentType::COLLIDER2D;
		collider["collider_type"] = sfge::ColliderType::CIRCLE;
		collider["size"] = 100;
		collider["sensor"] = false;

		circle["components"] = { transform, shape, body, collider };
		entities[i] = circle;
	}

	sceneJson["entities"] = entities;

	// Set up systems.
	json systemJson = {
			{"systemClassName", "TestCollisionsSystem"}
	};
	sceneJson["systems"] = json::array({ systemJson });

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}