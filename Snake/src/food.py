import py5
import random

class Food:
    def __init__(self):
        self.size = 20
        self.x = random.randint(0, 24)
        self.y = random.randint(0, 24)

        self.px = self.x*self.size+self.size//2
        self.py = self.y*self.size+self.size//2

    def show(self):
        py5.fill(255,120,80)
        py5.ellipse(self.px, self.py, self.size, self.size)
