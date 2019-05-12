from SFGE import *
from typing import List

class TestQuadtreeSystem(System):
    def on_draw(self):
        quads = physics2d_manager.world.get_quadtree_aabbs()
        for quad in quads:
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(quad.bottom_left.x, quad.top_right.y)), Physics2dManager.meter2pixel(quad.top_right), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(quad.top_right), Physics2dManager.meter2pixel(p2Vec2(quad.top_right.x, quad.bottom_left.y)), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(quad.bottom_left), Physics2dManager.meter2pixel(p2Vec2(quad.top_right.x, quad.bottom_left.y)), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(quad.bottom_left.x, quad.top_right.y)), Physics2dManager.meter2pixel(quad.bottom_left), Color.Red)