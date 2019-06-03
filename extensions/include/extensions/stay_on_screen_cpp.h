#ifndef STAY_ON_SCREEN_CPP_H
#define STAY_ON_SCREEN_CPP_H

#include <engine/system.h>
#include <engine/engine.h>
#include <physics/physics2d.h>

namespace sfge::ext
{
	class StayOnScreenCpp : public System
	{
	public:
		StayOnScreenCpp(Engine& engine);
		void OnEngineInit() override;
		void OnFixedUpdate() override;

	private:
		std::vector<Body2d*> bodies;
	};
}

#endif