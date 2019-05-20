from SFGE import *
from typing import List
from random import uniform

class TestBroadPhaseSystem(System):
    bodies = []
    buffer = 0

    def init(self):
        entities = entity_manager.get_entities_with_type(System.Body2d)
        self.bodies = []
        self.buffer = 0.2

        for entity in entities:
            self.bodies.append(physics2d_manager.body2d_manager.get_component(entity))

        for body in self.bodies:
            body.apply_force(p2Vec2(uniform(-1.0,1.0) * 0.02, uniform(-1.0,1.0) * 0.02))

    def on_draw(self):
        for body in self.bodies:
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(body.aabb.bottom_left.x, body.aabb.top_right.y)), Physics2dManager.meter2pixel(body.aabb.top_right), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(body.aabb.top_right), Physics2dManager.meter2pixel(p2Vec2(body.aabb.top_right.x, body.aabb.bottom_left.y)), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(body.aabb.bottom_left), Physics2dManager.meter2pixel(p2Vec2(body.aabb.top_right.x, body.aabb.bottom_left.y)), Color.Red)
            graphics2d_manager.draw_line(Physics2dManager.meter2pixel(p2Vec2(body.aabb.bottom_left.x, body.aabb.top_right.y)), Physics2dManager.meter2pixel(body.aabb.bottom_left), Color.Red)

    def fixed_update(self):
        for body in self.bodies:
            if (body.position.x > 12.8 - self.buffer):
                body.set_position(p2Vec2(self.buffer, body.position.y))
            if (body.position.y > 7.2 - self.buffer):
                body.set_position(p2Vec2(body.position.x, self.buffer))
            if (body.position.x < self.buffer):
                body.set_position(p2Vec2(12.8 - self.buffer, body.position.y))
            if (body.position.y < self.buffer):
                body.set_position(p2Vec2(body.position.x, 7.20 - self.buffer))

    def on_contact(self, c1, c2, enter):
        print(c1.entity)