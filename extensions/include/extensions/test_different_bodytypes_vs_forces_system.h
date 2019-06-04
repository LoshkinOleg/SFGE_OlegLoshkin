#ifndef TEST_DIFFERENT_BODYTYPES_VS_FORCES_SYSTEM_H
#define TEST_DIFFERENT_BODYTYPES_VS_FORCES_SYSTEM_H

#include <engine/system.h>
#include <engine/engine.h>
#include <physics/physics2d.h>
#include <graphics/graphics2d.h>
#include <p2vector.h>

namespace sfge::ext
{
	class TestDifferentBodytypesVsForcesSystem : public System
	{
	public:
		TestDifferentBodytypesVsForcesSystem(Engine& engine) : System(engine) {};

		void OnEngineInit() override;
		void OnFixedUpdate() override;
		void OnDraw() override;

	private:
		float yPosTrigger[2]{ 7.2f / 3.0f, 7.2f * 2.0f / 3.0f };
		float drawTimer[3];
		float forceMagnitude = 3;
		Graphics2dManager* graphicsManager;
		Body2d* dynamic;
		Body2d* kinematic;
		Body2d* stat;
	};
}

#endif