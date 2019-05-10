#include <engine/engine.h>
#include <engine/config.h>
#include <engine/scene.h>
#include <gtest/gtest.h>

TEST(OlegLoshkin, p2Vec2_Testing)
{
	sfge::Engine engine;
	std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>();
	engine.Init(std::move(initConfig));

	// Set up scene.
	auto* sceneManager = engine.GetSceneManager();
	json sceneJson = {
			{ "name", "p2Vec2 Testing" }
	};

	// Set up systems.
	json systemJson = {
			{"script_path", "scripts/test_vectors_system.py"}
	};
	sceneJson["systems"] = json::array({systemJson});

	// Start engine.
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}