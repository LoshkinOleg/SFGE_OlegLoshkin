from SFGE import *
from typing import List
from random import uniform

class TestQuadtreeSystem(System):
    bodies = []
    quads = []
    buffer = 0

    def init(self):
        entities = entity_manager.get_entities_with_type(System.Body2d)
        self.bodies = []
        self.quads = []
        self.buffer = 0.2

        for entity in entities:
            self.bodies.append(physics2d_manager.body2d_manager.get_component(entity))

        # Apply random force.
        for body in self.bodies:
            body.apply_force(p2Vec2(uniform(-1.0,1.0) * 0.05, uniform(-1.0,1.0) * 0.05))

    def on_draw(self):
        self.quads = physics2d_manager.world.get_quadtree_aabbs()
        for quad in self.quads:
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(quad.bottom_left.x, quad.top_right.y)), Physics2dManager.meter2pixel(quad.top_right), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(quad.top_right), Physics2dManager.meter2pixel(p2Vec2(quad.top_right.x, quad.bottom_left.y)), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(quad.bottom_left), Physics2dManager.meter2pixel(p2Vec2(quad.top_right.x, quad.bottom_left.y)), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(quad.bottom_left.x, quad.top_right.y)), Physics2dManager.meter2pixel(quad.bottom_left), Color.Red)

        #for body in self.bodies:
        #    graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(body.aabb.bottom_left.x, body.aabb.top_right.y)), Physics2dManager.meter2pixel(body.aabb.top_right), Color.Green)
        #    graphics2d_manager.draw_line(Physics2dManager.meter2pixel(body.aabb.top_right), Physics2dManager.meter2pixel(p2Vec2(body.aabb.top_right.x, body.aabb.bottom_left.y)), Color.Green)
        #    graphics2d_manager.draw_line(Physics2dManager.meter2pixel(body.aabb.bottom_left), Physics2dManager.meter2pixel(p2Vec2(body.aabb.top_right.x, body.aabb.bottom_left.y)), Color.Green)
        #    graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(body.aabb.bottom_left.x, body.aabb.top_right.y)), Physics2dManager.meter2pixel(body.aabb.bottom_left), Color.Green)

    def fixed_update(self):
        # physics2d_manager.world.log_quadtree_bodycount()

        for body in self.bodies:
            if (body.position.x > 12.8 - self.buffer):
                body.set_position(p2Vec2(self.buffer, body.position.y))
                # body.set_position(p2Vec2(2.0, 2.0))
            if (body.position.y > 7.2 - self.buffer):
                body.set_position(p2Vec2(body.position.x, self.buffer))
                # body.set_position(p2Vec2(2.0, 2.0))
            if (body.position.x < self.buffer):
                body.set_position(p2Vec2(12.8 - self.buffer, body.position.y))
                # body.set_position(p2Vec2(2.0, 2.0))
            if (body.position.y < self.buffer):
                body.set_position(p2Vec2(body.position.x, 7.20 - self.buffer))
                # body.set_position(p2Vec2(2.0, 2.0))