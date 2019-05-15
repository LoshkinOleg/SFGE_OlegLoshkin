from SFGE import *
from typing import List
from random import randint

class TestQuadtreeSystem(System):
    bodies = []

    def init(self):
        entities = entity_manager.get_entities_with_type(System.Body)
        self.bodies = []

        for entity in entities:
            self.bodies.append(physics2d_manager.body2d_manager.get_component(entity))

        # Apply random force.
        for body in self.bodies:
            body.apply_force(p2Vec2(randint(-1,1) * 0.05, randint(-1,1) * 0.05))

    def on_draw(self):
        quads = physics2d_manager.world.get_quadtree_aabbs()
        for quad in quads:
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(quad.bottom_left.x, quad.top_right.y)), Physics2dManager.meter2pixel(quad.top_right), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(quad.top_right), Physics2dManager.meter2pixel(p2Vec2(quad.top_right.x, quad.bottom_left.y)), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(quad.bottom_left), Physics2dManager.meter2pixel(p2Vec2(quad.top_right.x, quad.bottom_left.y)), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(quad.bottom_left.x, quad.top_right.y)), Physics2dManager.meter2pixel(quad.bottom_left), Color.Red)

    def update(self, dt):
        # physics2d_manager.world.log_quadtree_bodycount()

        for body in self.bodies:
            if (body.position.x >= 12.8):
                body.set_position(p2Vec2(0.2, body.position.y))
            if (body.position.y >= 7.2):
                body.set_position(p2Vec2(body.position.x, 0.2))
            if (body.position.x <= 0):
                body.set_position(p2Vec2(1260, body.position.y))
            if (body.position.y <= 0):
                body.set_position(p2Vec2(body.position.x, 7))