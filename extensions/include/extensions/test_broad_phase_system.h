#ifndef SFGE_EXT_BROAD_PHASE_SYSTEM_H
#define SFGE_EXT_BROAD_PHASE_SYSTEM_H

#include <vector>
#include <engine/system.h>
#include <graphics/shape2d.h>

namespace sfge::ext
{
	class TestBroadPhaseSystem : public System
	{
	public:
		TestBroadPhaseSystem(Engine& engine);

		void OnEngineInit() override;
		void OnAfterSceneLoad() override;
		void OnFixedUpdate() override;
		void OnContact(ColliderData* c1, ColliderData* c2, bool enter) override;

	private:
		std::vector<Shape*> m_Shapes;
		std::vector<unsigned int> m_ContactCount;
	};
}
#endif