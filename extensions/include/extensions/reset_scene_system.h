#ifndef RESET_SCENE_SYSTEM_H
#define RESET_SCENE_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <vector>
#include <physics/physics2d.h>
#include <graphics/graphics2d.h>
#include <input/input.h>

namespace sfge::ext
{
	class ResetSceneSystem : public System
	{
	public:
		ResetSceneSystem(Engine& engine) : System(engine) {};

		void OnEngineInit() override;
		void OnUpdate(float dt) override;

	private:
		InputManager* inputManager;
		std::vector<p2Vec2> initialVelocities;
		std::vector<p2Vec2> initialPositions;
		std::vector<sf::Color> initialColors;
		std::vector<Body2d*> bodies;
		std::vector<Shape*> shapes;
	};
}

#endif