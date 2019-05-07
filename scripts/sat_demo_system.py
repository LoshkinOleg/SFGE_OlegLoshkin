from SFGE import *
from typing import List
from math import cos

# Display size: 1280[px] x 720[px]

class SatDemoSystem(System):
    # Lerping variables for Rect_1.
    pos_0 = Vec2f()
    pos_1 = Vec2f()
    t = 0
    fixed_dt = 0
    # Vector declarations of aabb components, displayed on sides of display.
    rect_0_aabb_x = Vec2f()
    rect_0_aabb_y = Vec2f()
    rect_1_aabb_x = Vec2f()
    rect_1_aabb_y = Vec2f()
    # References to bodies and transforms. 0: Rect_0, 1: Rect_1
    transforms: List[Transform2d]
    bodies: List[Body2d]
    aabbs: List[Aabb2d]

    def init(self):
        # Get config data.
        resolution = engine.config.screen_size
        self.fixed_dt = engine.config.fixed_dt
        # Set lerping variables.
        self.pos_0 = Vec2f(resolution.x / 3.0, resolution.y / 3.0)
        self.pos_1 = Vec2f(self.pos_0.x * 2.0, self.pos_0.y * 2.0)
        self.t = 0
        # Set references.
        entities = [entity_manager.get_entity("Rect_0"), entity_manager.get_entity("Rect_1")]
        self.transforms = [transform2d_manager.get_component(entities[0]), transform2d_manager.get_component(entities[1])]
        self.bodies = [physics2d_manager.body2d_manager.get_component(entities[0]), physics2d_manager.body2d_manager.get_component(entities[1])]
        self.aabbs = [self.bodies[0].get_aabb(), self.bodies[1].get_aabb()]
        # Set aabb visualizations.
        self.rect_0_aabb_x = Vec2f(self.aabbs[0].top_right.x - self.aabbs[0].bottom_left.x, 0)
        self.rect_0_aabb_y = Vec2f(0, self.aabbs[0].bottom_left.y - self.aabbs[0].top_right.y)
        self.rect_1_aabb_x = Vec2f(self.aabbs[1].top_right.x - self.aabbs[1].bottom_left.x, 0)
        self.rect_1_aabb_y = Vec2f(0, self.aabbs[1].bottom_left.y - self.aabbs[1].top_right.y)

    def fixed_update(self):
        # Lerp Rect_1.
        self.transforms[1].position = Vec2f.lerp(self.pos_0, self.pos_1, (cos(self.t)/2) + 0.5)

        # Update delta time.
        self.t += self.fixed_dt

    def on_draw(self):
        # Draw projections of Rects on display edges.

        graphics2d_manager.draw_line(Vec2f((self.transforms[0].position - (self.rect_0_aabb_x /2.0)).x,5), Vec2f((self.transforms[0].position + (self.rect_0_aabb_x /2.0)).x, 5), Color.Red)
        graphics2d_manager.draw_line(Vec2f(5, (self.transforms[0].position - (self.rect_0_aabb_y /2.0)).y), Vec2f(5, (self.transforms[0].position + (self.rect_0_aabb_y /2.0)).y), Color.Red)
        graphics2d_manager.draw_line(Vec2f((self.transforms[1].position - (self.rect_1_aabb_x /2.0)).x,5), Vec2f((self.transforms[1].position + (self.rect_1_aabb_x /2.0)).x, 5), Color.Green)
        graphics2d_manager.draw_line(Vec2f(5, (self.transforms[1].position - (self.rect_1_aabb_y /2.0)).y), Vec2f(5, (self.transforms[1].position + (self.rect_1_aabb_y /2.0)).y), Color.Green)