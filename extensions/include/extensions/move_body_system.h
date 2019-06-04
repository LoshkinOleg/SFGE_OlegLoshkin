#ifndef MOVE_BODY_SYSTEM_H
#define MOVE_BODY_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <physics/physics2d.h>
#include <input/input.h>

namespace sfge::ext
{
	class MoveBodySystem : public System
	{
	public:
		MoveBodySystem(Engine& engine) : System(engine) {};

		void OnEngineInit() override;
		void OnUpdate(float dt) override;
		void OnFixedUpdate() override;

	private:
		__int8 input = 0; // Last bit = down, last bit - 1 = up, last bit - 2 = right, last bit - 3 = left.
		InputManager* inputManager;
		Body2d* bodyToMove;
		const float DELTA_TIME = 1.00f;
	};
}

#endif