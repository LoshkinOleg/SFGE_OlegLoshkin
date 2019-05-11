from SFGE import *
from typing import List

class TestForcesSystem(System):
    def init(self):
        forceMultiplier = 1

        entities = entity_manager.get_entities_with_type(System.Body)
        bodies = []
        for entity in entities:
            bodies.append(physics2d_manager.body2d_manager.get_component(entity))

        for body in bodies:
            body.apply_force(p2Vec2(1,-1) * forceMultiplier * engine.config.fixed_dt);