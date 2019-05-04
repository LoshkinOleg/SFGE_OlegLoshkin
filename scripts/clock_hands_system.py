from SFGE import *


 # 1m = 1000px
 # window: 1280px x 720px

class ClockHandsSystem(System):
    # Clock hands.
    seconds = Vec2f()
    minutes = Vec2f()
    hours = Vec2f()
    # Clock hands speeds.
    secondsSpeed = 6.0
    minutesSpeed = 0.1
    hoursSpeed = 0.001666
    # Time variable and time multiplier.
    timeMultiplier = 60.0
    t = 0.0

    def init(self):
        self.t = 0.0
        self.secondsSpeed *= self.timeMultiplier
        self.minutesSpeed *= self.timeMultiplier
        self.hoursSpeed *= self.timeMultiplier

    def update(self, dt):
        self.t += dt

        self.seconds = Vec2f(0,-18)
        self.seconds = self.seconds.rotate(self.secondsSpeed * self.t)
        self.minutes = Vec2f(0,-9)
        self.minutes = self.minutes.rotate(self.minutesSpeed * self.t)
        self.hours = Vec2f(0,-5)
        self.hours = self.hours.rotate(self.hoursSpeed * self.t)

    def on_draw(self):
        graphics2d_manager.draw_vector(self.seconds, Vec2f(640,360), Color.Red)
        graphics2d_manager.draw_vector(self.minutes, Vec2f(640,360), Color.Green)
        graphics2d_manager.draw_vector(self.hours, Vec2f(640,360), Color.Green)