from SFGE import *
from math import cos


class TestVectorsSystem(System):
    # test positions
    pos_0 = Vec2f()
    pos_1 = Vec2f()
    pos_2 = Vec2f()
    pos_3 = Vec2f()
    pos_4 = Vec2f()
    pos_5 = Vec2f()
    pos_6 = Vec2f()
    pos_7 = Vec2f()
    pos_8 = Vec2f()
    pos_9 = Vec2f()
    # Scale factor
    scale = 0.0
    # Displayed numerical values boolean
    displayedResults = False
    # p2Vec2 + p2Vec2
    addition_0 = p2Vec2()
    addition_1 = p2Vec2()
    addition_result = p2Vec2()
    # p2Vec2 - p2Vec2
    substraction_0 = p2Vec2()
    substraction_1 = p2Vec2()
    substraction_result = p2Vec2()
    # p2Vec2 * float
    multiplication_0 = p2Vec2()
    multiplication_factor = 0.0
    multiplication_result = p2Vec2()
    # p2Vec2 / float
    division_0 = p2Vec2()
    division_factor = 0.0
    division_result = p2Vec2()
    # Lerp
    lerp_0 = p2Vec2()
    lerp_1 = p2Vec2()
    lerp_result = p2Vec2()
    # Angle between
    angleBetween_0 = p2Vec2()
    angleBetween_1 = p2Vec2()
    angleBetween_result = 0.0
    # Rotation
    rotation_v = p2Vec2()
    rotation_angle = 0.0
    # Dot
    dot_0 = p2Vec2()
    dot_1 = p2Vec2()
    dot_result = 0.0
    # Cross
    cross_0 = p2Vec2()
    cross_1 = p2Vec2()
    cross_result = p2Vec3()
    # Normalized
    normalized_v = p2Vec2()
    normalized_result = 0.0
    # Time variables
    t = 0.0

    def init(self):
        screenSize = Vec2f(1280,720)
        # test positions
        self.pos_0 = Vec2f(1 * (screenSize.x / 5) - (screenSize.x / 10), 1 * (screenSize.y / 2) - (screenSize.y / 4) )
        self.pos_1 = Vec2f(2 * (screenSize.x / 5) - (screenSize.x / 10), 1 * (screenSize.y / 2) - (screenSize.y / 4) )
        self.pos_2 = Vec2f(3 * (screenSize.x / 5) - (screenSize.x / 10), 1 * (screenSize.y / 2) - (screenSize.y / 4) )
        self.pos_3 = Vec2f(4 * (screenSize.x / 5) - (screenSize.x / 10), 1 * (screenSize.y / 2) - (screenSize.y / 4) )
        self.pos_4 = Vec2f(5 * (screenSize.x / 5) - (screenSize.x / 10), 1 * (screenSize.y / 2) - (screenSize.y / 4) )
        self.pos_5 = Vec2f(1 * (screenSize.x / 5) - (screenSize.x / 10), 2 * (screenSize.y / 2) - (screenSize.y / 4) )
        self.pos_6 = Vec2f(2 * (screenSize.x / 5) - (screenSize.x / 10), 2 * (screenSize.y / 2) - (screenSize.y / 4) )
        self.pos_7 = Vec2f(3 * (screenSize.x / 5) - (screenSize.x / 10), 2 * (screenSize.y / 2) - (screenSize.y / 4) )
        self.pos_8 = Vec2f(4 * (screenSize.x / 5) - (screenSize.x / 10), 2 * (screenSize.y / 2) - (screenSize.y / 4) )
        self.pos_9 = Vec2f(5 * (screenSize.x / 5) - (screenSize.x / 10), 2 * (screenSize.y / 2) - (screenSize.y / 4) )
        # Scale factor
        self.scale = 0.025
        # Displayed numerical values boolean
        self.displayedResults = False
        # p2Vec2 + p2Vec2
        self.addition_0 = p2Vec2(1,0)
        self.addition_1 = p2Vec2(0,1)
        self.addition_result = p2Vec2()
        # p2Vec2 - p2Vec2
        self.substraction_0 = p2Vec2(1,0)
        self.substraction_1 = p2Vec2(0,1)
        self.substraction_result = p2Vec2()
        # p2Vec2 * float
        self.multiplication_0 = p2Vec2(1,0)
        self.multiplication_factor = 2.0
        self.multiplication_result = p2Vec2()
        # p2Vec2 / float
        self.division_0 = p2Vec2(1,0)
        self.division_factor = 2.0
        self.division_result = p2Vec2()
        # Lerp
        self.lerp_0 = p2Vec2(1,0)
        self.lerp_1 = p2Vec2(0,1)
        self.lerp_result = p2Vec2()
        # Angle between
        self.angleBetween_0 = p2Vec2(1,0)
        self.angleBetween_1 = p2Vec2(1,1)
        self.angleBetween_result = 0.0 # Result is supposed to be 45° Euler.
        # Rotation
        self.rotation_v = p2Vec2(1,0)
        self.rotation_angle = 90.0
        # Dot
        self.dot_0 = p2Vec2(1,0)
        self.dot_1 = p2Vec2(1,1)
        self.dot_result = 0.0 # Result is supposed to be 2.
        # Cross
        self.cross_0 = p2Vec2(2,0)
        self.cross_1 = p2Vec2(0,2)
        self.cross_result = p2Vec3() # Result is supposed to be (0,0,4).
        # Normalized
        self.normalized_v = p2Vec2(2,0)
        self.normalized_result = 0.0
        # Time variables
        self.t = 0.0

    def update(self, dt):
        # p2Vec2 + p2Vec2
        self.addition_result = self.addition_0 + self.addition_1
        # p2Vec2 - p2Vec2
        self.substraction_result = self.substraction_0 - self.substraction_1
        # p2Vec2 * float
        self.multiplication_result = self.multiplication_0 * self.multiplication_factor
        # p2Vec2 / float
        self.division_result = self.division_0 / self.division_factor
        # Lerp
        self.lerp_result = p2Vec2.lerp(self.lerp_0, self.lerp_1, ((cos(self.t))/2) + 0.5)
        # Angle between
        self.angleBetween_result = p2Vec2.angle_between(self.angleBetween_0, self.angleBetween_1)
        # Rotation
        self.rotation_v = self.rotation_v.rotate(self.rotation_angle * dt)
        # Dot
        self.dot_result = p2Vec2.dot(self.dot_0, self.dot_1)
        # Cross
        self.cross_result = p2Vec2.cross(self.cross_0, self.cross_1)
        # Normalized
        self.normalized_result = self.normalized_v.normalized()
        # Time variables
        self.t += dt;

    def on_draw(self):
        # p2Vec2 + p2Vec2
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.addition_0) * self.scale, self.pos_0, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.addition_1) * self.scale, self.pos_0, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.addition_result) * self.scale, self.pos_0, Color.Red)
        # p2Vec2 - p2Vec2
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.substraction_0) * self.scale, self.pos_1, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.substraction_1) * self.scale, self.pos_1, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.substraction_result) * self.scale, self.pos_1, Color.Red)
        # p2Vec2 * float
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.multiplication_0) * self.scale, self.pos_2, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.multiplication_result) * self.scale, self.pos_2, Color.Red)
        # p2Vec2 / float
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.division_0) * self.scale, self.pos_3, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.division_result) * self.scale, self.pos_3, Color.Red)
        # Lerp
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.lerp_0) * self.scale, self.pos_4, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.lerp_1) * self.scale, self.pos_4, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.lerp_result) * self.scale, self.pos_4, Color.Red)
        # Angle between
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.angleBetween_0) * self.scale, self.pos_5, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.angleBetween_1) * self.scale, self.pos_5, Color.Green)
        if (self.displayedResults == False):
            print("Angle between angleBetween_0 and angleBetween_1 is: ", self.angleBetween_result)
        # Rotation
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.rotation_v) * self.scale, self.pos_6, Color.Green)
        # Dot
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.dot_0) * self.scale, self.pos_7, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.dot_1) * self.scale, self.pos_7, Color.Green)
        if (self.displayedResults == False):
            print("Dot product of dot_0 and dot_1 is: ", self.dot_result)
        # Cross
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.cross_0) * self.scale, self.pos_8, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.cross_1) * self.scale, self.pos_8, Color.Green)
        if (self.displayedResults == False):
            print("Cross_result is: (", self.cross_result.x, ";", self.cross_result.y, ";", self.cross_result.z, ")")
        # Normalized
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.normalized_v) * self.scale, self.pos_9, Color.Green)
        graphics2d_manager.draw_vector(Physics2dManager.meter2pixel(self.normalized_result) * self.scale, self.pos_9, Color.Red)
        # Displayed numerical values boolean
        self.displayedResults = True