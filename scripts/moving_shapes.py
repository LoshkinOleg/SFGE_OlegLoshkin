from SFGE import *
from typing import List

 # 1m = 1000px
 # window: 1280px x 720px

class MovingShapesSystem(System):
    time = 0
    entities: List[int]
    contact_count: List[int]

    def init(self):
        self.time = 0

    def update(self, dt):
        self.time += dt
