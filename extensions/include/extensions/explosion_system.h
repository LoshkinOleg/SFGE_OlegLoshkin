#ifndef EXPLOSION_SYSTEM_H
#define EXPLOSION_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <physics/physics2d.h>
#include <input/input.h>
#include <vector>

namespace sfge::ext
{
	class ExplosionSystem : public System
	{
	public:
		ExplosionSystem(Engine& engine) : System(engine) {};

		void OnEngineInit() override;
		void OnUpdate(float dt) override;

	private:
		InputManager* inputManager = nullptr;
		std::vector<Body2d*> bodies = std::vector<Body2d*>();
		const float EXPLOSION_MULTIPLIER = 10;
	};
}

#endif