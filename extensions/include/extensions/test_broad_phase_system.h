#ifndef SFGE_EXT_BROAD_PHASE_SYSTEM_H
#define SFGE_EXT_BROAD_PHASE_SYSTEM_H

#include <vector>
#include <engine/system.h>
#include <graphics/shape2d.h>
#include <physics/body2d.h>

namespace sfge::ext
{
	class TestBroadPhaseSystem : public System
	{
	public:
		TestBroadPhaseSystem(Engine& engine);

		void OnEngineInit() override;
		void OnFixedUpdate() override;
		void OnContact(ColliderData* c1, ColliderData* c2, bool enter) override;
		void OnDraw() override;

	private:
		std::vector<Shape*> m_Shapes;
		std::vector<Body2d*> m_Bodies;
		std::map<Entity, int> m_Dictionary; // Associates a particular entity with it's index in m_ContactCount.
		std::vector<int> m_ContactCount;
		Body2dManager* m_BodyManager;
		ShapeManager* m_ShapeManager;
		EntityManager* m_EntityManager;
		Graphics2dManager* m_GraphicsManager;
		Physics2dManager* m_PhysicsManager;
		p2World* m_World;
	};
}
#endif