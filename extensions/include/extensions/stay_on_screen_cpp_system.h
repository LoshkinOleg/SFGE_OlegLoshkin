#ifndef STAY_ON_SCREEN_CPP_SYSTEM_H
#define STAY_ON_SCREEN_CPP_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <vector>
#include <physics/physics2d.h>

namespace sfge::ext
{
	class StayOnScreenCppSystem : public System
	{
	public:
		StayOnScreenCppSystem(Engine& engine) : System(engine) {};

		void OnEngineInit() override;
		void OnFixedUpdate() override;

	private:
		std::vector<Body2d*> bodies = std::vector<Body2d*>();
	};
}

#endif