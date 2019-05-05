from SFGE import *
from typing import List
from math import cos

# Display resolution: 1280[px] * 720[px]

class LerpingShapesSystem(System):
    # Data used. Positions represent centers of topLeft, topRight, bottomLeft and bottomRight quadrants of the display.
    pos_0 = Vec2f()
    pos_1 = Vec2f()
    pos_2 = Vec2f()
    pos_3 = Vec2f()
    t = 0.0
    SPEED_MULTIPLIER_0 = 0.0
    SPEED_MULTIPLIER_1 = 0.0
    SPEED_MULTIPLIER_2 = 0.0
    SPEED_MULTIPLIER_3 = 0.0
    # References to transforms of entities. 0: Rect_0, 1: Rect_1, 2: Circle_0, 3: Circle_1
    transforms: List[Transform2d]

    def init(self):
        # Initialize positions and time.
        self.pos_0 = Vec2f(426,240)
        self.pos_1 = Vec2f(853,240)
        self.pos_2 = Vec2f(426,480)
        self.pos_3 = Vec2f(853,480)
        self.t = 0.0
        self.SPEED_MULTIPLIER_0 = 1.0
        self.SPEED_MULTIPLIER_1 = 1.5
        self.SPEED_MULTIPLIER_2 = 0.5
        self.SPEED_MULTIPLIER_3 = 0.75
        # Get references to entities then to their transforms.
        entities = [entity_manager.get_entity("Rect_0"), entity_manager.get_entity("Rect_1"), entity_manager.get_entity("Circle_0"), entity_manager.get_entity("Circle_1")]
        self.transforms = [transform2d_manager.get_component(entities[0]), transform2d_manager.get_component(entities[1]), transform2d_manager.get_component(entities[2]), transform2d_manager.get_component(entities[3])]

    def fixed_update(self):
        # Lerp entities at different speeds.
        self.transforms[0].position = Vec2f.lerp(self.pos_0, self.pos_1, (cos(self.SPEED_MULTIPLIER_0 * self.t) / 2) + 0.5)
        self.transforms[1].position = Vec2f.lerp(self.pos_1, self.pos_0, (cos(self.SPEED_MULTIPLIER_1 * self.t) / 2) + 0.5)
        self.transforms[2].position = Vec2f.lerp(self.pos_2, self.pos_3, (cos(self.SPEED_MULTIPLIER_2 * self.t) / 2) + 0.5)
        self.transforms[3].position = Vec2f.lerp(self.pos_3, self.pos_2, (cos(self.SPEED_MULTIPLIER_3 * self.t) / 2) + 0.5)
        # Update timer.
        self.t += engine.config.fixed_dt