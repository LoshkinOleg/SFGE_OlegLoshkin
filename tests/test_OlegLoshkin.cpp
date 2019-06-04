#include <gtest/gtest.h>
#include <SFML\System\Vector2.hpp>
#include <engine/engine.h>
#include <engine/config.h>
#include <engine/scene.h>
#include <physics/physics2d.h>
#include <graphics/graphics2d.h>
#include <p2body.h>

TEST(OlegLoshkin, Vectors)
{
	// Set up config and scene base.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();

	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 5;

	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
		{ "name", "Vectors" }
	};

	// Add systems.
	sceneJson["systems"] = json::array(
	{
		{
			{ "systemClassName", "TestP2Vec2System" }
		}
	});

	// Start the engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, Bodies_vs_Forces)
{
	// Set up config and scene base.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();

	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 9.81f);
	initConfig->quadTreeBodiesPerQuad = 5;

	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
		{ "name", "Bodies vs Forces" }
	};

	// Create entities.
	json entities[3];

	p2Vec2 positions[3]
	{
		p2Vec2{ screenSize.x * 0.5f - 200, screenSize.y * 0.5f },
		p2Vec2{ screenSize.x * 0.5f, screenSize.y * 0.5f },
		p2Vec2{ screenSize.x * 0.5f + 200, screenSize.y * 0.5f }
	};
	for (size_t i = 0; i < 3; i++)
	{
		positions[i] *= 0.01f;
	}
	p2BodyType bodyTypes[3]
	{
		p2BodyType::DYNAMIC,
		p2BodyType::KINEMATIC,
		p2BodyType::STATIC
	};

	json entity;
	json transform;
	json body;
	json shape;
	json collider;
	transform["type"]			= sfge::ComponentType::TRANSFORM2D;
	body["type"]				= sfge::ComponentType::BODY2D;
	shape["type"]				= sfge::ComponentType::SHAPE2D;
	collider["type"]			= sfge::ComponentType::COLLIDER2D;
	shape["shape_type"]			= sfge::ShapeType::CIRCLE;
	collider["collider_type"]	= sfge::ColliderType::CIRCLE;
	shape["radius"] =			50;
	collider["radius"] =		50;
	body["mass"] =				1;

	for (size_t i = 0; i < 3; i++)
	{
		entity["name"]					= "Circle_" + std::to_string(i);
		transform["position"]			= { positions[i].x * 100, positions[i].y * 100 };
		body["body_type"]				= bodyTypes[i];
		if (i == 1) body["velocity"]	= {0,-1};
		entity["components"]			= { transform, body, shape, collider };
		entities[i]						= entity;
	}
	sceneJson["entities"] = entities;

	// Add systems.
	sceneJson["systems"] = json::array(
	{
		{
			{ "systemClassName", "TestDifferentBodytypesVsForcesSystem" }
		}
	});

	// Start the engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, AABBs)
{
	// Set up config and scene base.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();

	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 5;

	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
		{ "name", "AABBs" }
	};

	// Create entities.
	json entities[2];

	p2Vec2 positions[2]
	{
		p2Vec2{ screenSize.x * 0.5f - 200, screenSize.y * 0.5f },
		p2Vec2{ screenSize.x * 0.5f + 200, screenSize.y * 0.5f }
	};
	for (size_t i = 0; i < 2; i++)
	{
		positions[i] *= 0.01f;
	}

	json entity;
	json transform;
	json body;
	json shape;
	json collider;
	transform["type"]			= sfge::ComponentType::TRANSFORM2D;
	body["type"]				= sfge::ComponentType::BODY2D;
	shape["type"]				= sfge::ComponentType::SHAPE2D;
	collider["type"]			= sfge::ComponentType::COLLIDER2D;
	shape["shape_type"]			= sfge::ShapeType::CIRCLE;
	collider["collider_type"]	= sfge::ColliderType::CIRCLE;
	shape["radius"]				= 50;
	collider["radius"]			= 50;
	body["mass"]				= 1;
	body["body_type"]			= p2BodyType::KINEMATIC;
	collider["sensor"]			= true;

	for (size_t i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			entity["name"]		= "BodyToMove";
		}
		else
		{
			entity["name"]		= "Circle_" + std::to_string(i);
		}
		transform["position"]	= { positions[i].x * 100, positions[i].y * 100 };
		entity["components"]	= { transform, body, shape, collider };
		entities[i]				= entity;
	}
	sceneJson["entities"] = entities;

	// Add systems.
	sceneJson["systems"] = json::array(
	{
		{
			{ "systemClassName", "HighlightOnAabbOverlapSystem" }
		},
		{
			{ "systemClassName", "MoveBodySystem" }
		}
	});

	// Start the engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, Bodies_vs_Collisions)
{
	// Set up config and scene base.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();

	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 9.81f);
	initConfig->quadTreeBodiesPerQuad = 5;

	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
		{ "name", "Bodies vs Collisions" }
	};

	// Create entities.
	json entities[4];

	p2Vec2 positions[4]
	{
		p2Vec2{ screenSize.x / 3.0f, screenSize.y / 4.0f }, // Dynamic rect.
		p2Vec2{ screenSize.x * 2.0f / 3.0f, screenSize.y / 2.0f }, // Small static rect on the right.
		p2Vec2{ screenSize.x / 2.0f - 501, (screenSize.y * 3.0f / 4.0f) - 101 }, // Kinematic sensor rect.
		p2Vec2{ screenSize.x / 2.0f, screenSize.y * 3.0f / 4.0f } // Big static bottom rect.
	};
	for (size_t i = 0; i < 4; i++)
	{
		positions[i] *= 0.01f;
	}
	p2BodyType bodyTypes[3]
	{
		p2BodyType::DYNAMIC,
		p2BodyType::KINEMATIC,
		p2BodyType::STATIC
	};
	p2Vec2 sizes[2]
	{
		p2Vec2{ 100,100 }, // All other rect's sizes.
		p2Vec2{ 1000,100 } // Size of the bottom static rect.
	};
	p2Vec2 velocities[2]
	{
		(positions[1] - positions[0]) * 5, // Force applied to the dynamic rect.
		p2Vec2{ 4,0 } // Force applied to the kinematic rect.
	};

	json entity;
	json transform;
	json body;
	json shape;
	json collider;
	transform["type"]			= sfge::ComponentType::TRANSFORM2D;
	body["type"]				= sfge::ComponentType::BODY2D;
	shape["type"]				= sfge::ComponentType::SHAPE2D;
	collider["type"]			= sfge::ComponentType::COLLIDER2D;
	shape["shape_type"]			= sfge::ShapeType::RECTANGLE;
	collider["collider_type"]	= sfge::ColliderType::BOX;
	body["mass"] =				1;

	for (size_t i = 0; i < 4; i++)
	{
		entity["name"]					= "Rect_" + std::to_string(i);
		transform["position"]			= { positions[i].x * 100, positions[i].y * 100 };
		switch (i)
		{
			case 0:
			{
				body["body_type"]		= p2BodyType::DYNAMIC;
				shape["size"]			= { sizes[0].x, sizes[0].y };
				collider["size"]		= { sizes[0].x, sizes[0].y };
				body["velocity"]		= {velocities[0].x, velocities[0].y};
				collider["sensor"]		= false;
			}break;
			case 1:
			{
				body["body_type"]		= p2BodyType::STATIC;
				shape["size"]			= { sizes[0].x, sizes[0].y };
				collider["size"]		= { sizes[0].x, sizes[0].y };
				collider["sensor"]		= false;
			}break;
			case 2:
			{
				body["body_type"]		= p2BodyType::KINEMATIC;
				shape["size"]			= { sizes[0].x, sizes[0].y };
				collider["size"]		= { sizes[0].x, sizes[0].y };
				body["velocity"]		= { velocities[1].x, velocities[1].y };
				collider["sensor"]		= true;
			}break;
			case 3:
			{
				body["body_type"]		= p2BodyType::STATIC;
				shape["size"]			= { sizes[1].x, sizes[1].y };
				collider["size"]		= { sizes[1].x, sizes[1].y };
				collider["sensor"]		= false;
			}break;
		}
		entity["components"]			= { transform, body, shape, collider };
		entities[i]						= entity;
	}
	sceneJson["entities"] = entities;

	// Add systems.
	sceneJson["systems"] = json::array(
	{
		{
			{ "systemClassName", "ResetSceneSystem" }
		},
		{
			{ "systemClassName", "HighlightOnAabbOverlapSystem" }
		}
	});

	// Start the engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, QuadTree)
{
	// Set up config and scene base.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();

	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 2;

	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
		{ "name", "QuadTree" }
	};

	// Create entities.
	json entities[256];
	json entity;
	json body;
	json shape;
	json transform;
	json collider;
	transform["type"]			= sfge::ComponentType::TRANSFORM2D;
	body["type"]				= sfge::ComponentType::BODY2D;
	shape["type"]				= sfge::ComponentType::SHAPE2D;
	collider["type"]			= sfge::ComponentType::COLLIDER2D;
	shape["shape_type"]			= sfge::ShapeType::CIRCLE;
	collider["collider_type"]	= sfge::ColliderType::CIRCLE;
	shape["radius"]				= 10;
	collider["radius"]			= 10;
	body["mass"]				= 1;
	body["body_type"]			= p2BodyType::KINEMATIC;

	// Set up entities.
	for (size_t i = 0; i < 256; i++)
	{
		entity["name"]			= "Circle_" + std::to_string(i);
		transform["position"]	= { rand() % screenSize.x , rand() % screenSize.y }; // Random position on screen.
		// Code taken from https://stackoverflow.com/questions/686353/random-float-number-generation
		body["velocity"]		= { -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))), -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))) }; // Random velocity with X and Y components between -1 and 1;
		entity["components"]	= { transform, body, shape, collider };
		entities[i]				= entity;
	}
	sceneJson["entities"] = entities;

	// Add systems.
	sceneJson["systems"] = json::array(
	{
		{
			{ "systemClassName", "DrawQuadTreeSystem" }
		},
		{
			{ "systemClassName", "StayOnScreenCppSystem" }
		}
	});

	// Start the engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, Pendulum)
{
	// Set up config and scene base.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();

	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 5;

	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
		{ "name", "Pendulum" }
	};

	// Create entities.
	json entities[3];

	p2Vec2 positions[3]
	{
		p2Vec2{ screenSize.x * 0.5f - 200, screenSize.y * 0.5f },
		p2Vec2{ screenSize.x * 0.5f, screenSize.y * 0.5f },
		p2Vec2{ screenSize.x * 0.5f + 200, screenSize.y * 0.5f }
	};
	for (size_t i = 0; i < 3; i++)
	{
		positions[i] *= 0.01f;
	}

	json entity;
	json transform;
	json body;
	json shape;
	json collider;
	transform["type"]			= sfge::ComponentType::TRANSFORM2D;
	body["type"]				= sfge::ComponentType::BODY2D;
	shape["type"]				= sfge::ComponentType::SHAPE2D;
	collider["type"]			= sfge::ComponentType::COLLIDER2D;
	shape["shape_type"]			= sfge::ShapeType::CIRCLE;
	collider["collider_type"]	= sfge::ColliderType::CIRCLE;
	shape["radius"] =			50;
	collider["radius"] =		50;
	body["mass"] =				1;
	body["body_type"]			= p2BodyType::DYNAMIC;

	for (size_t i = 0; i < 3; i++)
	{
		entity["name"]					= "Circle_" + std::to_string(i);
		transform["position"]			= { positions[i].x * 100, positions[i].y * 100 };
		if (i == 0)
		{
			body["velocity"]			= { 4,0 };
		}
		else
		{
			body["velocity"]			= { 0,0 };
		}
		entity["components"]			= { transform, body, shape, collider };
		entities[i]						= entity;
	}
	sceneJson["entities"] = entities;

	// Add systems.
	sceneJson["systems"] = json::array(
	{
		{
			{ "systemClassName", "StayOnScreenCppSystem" }
		}
	});

	// Start the engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, Restitution_and_Mass)
{
	// Set up config and scene base.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();

	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 5;

	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
		{ "name", "Restitution and Mass" }
	};

	// Create entities.
	json entities[8];

	p2Vec2 positions[8]
	{
		p2Vec2{ (screenSize.x * 0.5f) - 100, screenSize.y / 5.0f },
		p2Vec2{ (screenSize.x * 0.5f) + 100, screenSize.y / 5.0f },
		p2Vec2{ (screenSize.x * 0.5f) - 100, screenSize.y * 2.0f / 5.0f },
		p2Vec2{ (screenSize.x * 0.5f) + 100, screenSize.y * 2.0f / 5.0f },
		p2Vec2{ (screenSize.x * 0.5f) - 100, screenSize.y * 3.0f / 5.0f },
		p2Vec2{ (screenSize.x * 0.5f) + 100, screenSize.y * 3.0f / 5.0f },
		p2Vec2{ (screenSize.x * 0.5f) - 100, screenSize.y * 4.0f / 5.0f },
		p2Vec2{ (screenSize.x * 0.5f) + 100, screenSize.y * 4.0f / 5.0f },
	};
	for (size_t i = 0; i < 8; i++)
	{
		positions[i] *= 0.01f;
	}
	float restitutions[8]
	{
		1,
		1,
		0.33f,
		0.33f,
		1,
		1,
		0.33f,
		0.33f
	};
	int sizes[8]
	{
		50,
		50,
		50,
		50,
		50,
		25,
		50,
		25
	};
	float masses[8]
	{
		1,
		1,
		1,
		1,
		1,
		0.5f,
		1,
		0.5f
	};

	json entity;
	json transform;
	json body;
	json shape;
	json collider;
	transform["type"]			= sfge::ComponentType::TRANSFORM2D;
	body["type"]				= sfge::ComponentType::BODY2D;
	shape["type"]				= sfge::ComponentType::SHAPE2D;
	collider["type"]			= sfge::ComponentType::COLLIDER2D;
	shape["shape_type"]			= sfge::ShapeType::CIRCLE;
	collider["collider_type"]	= sfge::ColliderType::CIRCLE;
	body["body_type"]			= p2BodyType::DYNAMIC;

	for (size_t i = 0; i < 8; i++)
	{
		entity["name"]					= "Circle_" + std::to_string(i);
		transform["position"]			= { positions[i].x * 100, positions[i].y * 100 };
		shape["radius"]					= sizes[i];
		collider["radius"]				= sizes[i];
		if (i % 2 == 0)
		{
			body["velocity"]			= {4,0};
		}
		else
		{
			body["velocity"]			= {0,0};
		}
		body["restitution"]				= restitutions[i];
		body["mass"]					= masses[i];
		entity["components"]			= { transform, body, shape, collider };
		entities[i]						= entity;
	}
	sceneJson["entities"] = entities;

	// Add systems.
	sceneJson["systems"] = json::array(
	{
		{
			{ "systemClassName", "StayOnScreenCppSystem" }
		},
		{
			{ "systemClassName", "ResetSceneSystem" }
		}
	});

	// Start the engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, Explosion)
{
	// Set up config and scene base.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();

	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 5;

	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
		{ "name", "Explosion" }
	};

	// Create entities.
	const int BODIES_PER_SIDE = 10;
	json entities[BODIES_PER_SIDE * BODIES_PER_SIDE];

	p2Vec2 bounds[2]
	{
		p2Vec2{ screenSize.x / 3.0f, screenSize.y / 3.0f },
		p2Vec2{ screenSize.x * 2.0f / 3.0f, screenSize.y * 2.0f / 3.0f }
	};
	std::vector<p2Vec2> positions;
	p2Vec2 spacing = (bounds[1] - bounds[0]) / (float)BODIES_PER_SIDE;
	for (float x = bounds[0].x; x < bounds[1].x; x += spacing.x)
	{
		for (float y = bounds[0].y; y < bounds[1].y; y += spacing.y)
		{
			positions.push_back(p2Vec2{x,y});
		}
	}

	json entity;
	json transform;
	json body;
	json shape;
	json collider;
	transform["type"]			= sfge::ComponentType::TRANSFORM2D;
	body["type"]				= sfge::ComponentType::BODY2D;
	shape["type"]				= sfge::ComponentType::SHAPE2D;
	collider["type"]			= sfge::ComponentType::COLLIDER2D;
	shape["shape_type"]			= sfge::ShapeType::CIRCLE;
	collider["collider_type"]	= sfge::ColliderType::CIRCLE;
	shape["radius"] =			10;
	collider["radius"] =		10;
	body["mass"] =				1;
	body["body_type"]			= p2BodyType::DYNAMIC;

	for (size_t i = 0; i < BODIES_PER_SIDE * BODIES_PER_SIDE; i++)
	{
		entity["name"]					= "Circle_" + std::to_string(i);
		transform["position"]			= { positions[i].x, positions[i].y };
		entity["components"]			= { transform, body, shape, collider };
		entities[i]						= entity;
	}
	sceneJson["entities"] = entities;

	// Add systems.
	sceneJson["systems"] = json::array(
	{
		{
			{ "systemClassName", "ExplosionSystem" }
		},
		{
			{ "systemClassName", "StayOnScreenCppSystem" }
		},
		{
			{ "systemClassName", "ResetSceneSystem" }
		}
	});

	// Start the engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(OlegLoshkin, Many_Rects)
{
	// Set up config and scene base.
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();

	auto screenSize = initConfig->screenResolution;
	initConfig->gravity = p2Vec2(0, 0);
	initConfig->quadTreeBodiesPerQuad = 5;

	engine.Init(std::move(initConfig));
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
		{ "name", "Many Rects" }
	};

	// Create entities.
	json entities[256];
	json entity;
	json body;
	json shape;
	json transform;
	json collider;
	transform["type"]			= sfge::ComponentType::TRANSFORM2D;
	body["type"]				= sfge::ComponentType::BODY2D;
	shape["type"]				= sfge::ComponentType::SHAPE2D;
	collider["type"]			= sfge::ComponentType::COLLIDER2D;
	shape["shape_type"]			= sfge::ShapeType::CIRCLE;
	collider["collider_type"]	= sfge::ColliderType::CIRCLE;
	shape["radius"]				= 10;
	collider["radius"]			= 10;
	body["mass"]				= 1;
	body["body_type"]			= p2BodyType::DYNAMIC;

	// Set up entities.
	for (size_t i = 0; i < 256; i++)
	{
		entity["name"]			= "Circle_" + std::to_string(i);
		transform["position"]	= { rand() % screenSize.x , rand() % screenSize.y }; // Random position on screen.
		// Code taken from https://stackoverflow.com/questions/686353/random-float-number-generation
		body["velocity"]		= { -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))), -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f)))) }; // Random velocity with X and Y components between -1 and 1;
		entity["components"]	= { transform, body, shape, collider };
		entities[i]				= entity;
	}
	sceneJson["entities"] = entities;

	// Add systems.
	sceneJson["systems"] = json::array(
	{
		{
			{ "systemClassName", "DrawQuadTreeSystem" }
		},
		{
			{ "systemClassName", "StayOnScreenCppSystem" }
		},
		{
			{ "systemClassName", "HighlightOnAabbOverlapSystem" }
		}
	});

	// Start the engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}