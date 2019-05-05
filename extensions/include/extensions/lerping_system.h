#ifndef SFGE_LERPING_SYSTEM_H
#define SFGE_LERPING_SYSTEM_H

#include <p2vector.h>
#include <engine/system.h>
#include <engine/transform2d.h>
#include <graphics/graphics2d.h>
#include <physics/physics2d.h>
using namespace sfge;

namespace sfge::ext
{
	class LerpingSystem : public System
	{
	public:
		// Constructor and overrides.
		LerpingSystem(Engine& engine);
		void OnEngineInit() override;
		void OnFixedUpdate() override;
		void OnDraw() override;

	private:
		// Vectors between which to lerp.
		p2Vec2 m_v;
		p2Vec2 m_u;
		// Vector that lerps between v and u.
		p2Vec2 m_result;
		// Resulting vector's x and y componenents.
		p2Vec2 m_result_y;
		p2Vec2 m_result_x;
		// Other variables and references.
		float m_t;
		float m_fixed_dt;
		Graphics2dManager* m_graphics_manager;
		const float M_SPEED_MULTIPLIER = 1;
	};
}
#endif