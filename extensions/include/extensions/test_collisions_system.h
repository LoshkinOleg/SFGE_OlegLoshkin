#ifndef SFGE_EXT_COLLISIONS_SYSTEM_H
#define SFGE_EXT_COLLISIONS_SYSTEM_H

#include <vector>
#include <engine/system.h>
#include <physics/body2d.h>

namespace sfge::ext
{
	class TestCollisionsSystem : public System
	{
	public:
		TestCollisionsSystem(Engine& engine);

		void OnEngineInit() override;
		void OnFixedUpdate() override;

	private:
		std::vector<Body2d*> m_Bodies;
	};
}
#endif