import py5
import random

class Tube:
    def __init__(self, img, rimg):
        self.w = 50
        self.v = -10
        
        self.down_h = random.randint(80, 250)
        self.up_h = 485 - self.down_h - 140

        self.x = 820

        self.down_y = 485 - self.down_h
        self.up_y = 0

        self.img = img
        self.rimg = rimg

    def show(self):
        py5.image(self.img, self.x, self.down_y, self.w, self.down_h)
        py5.image(self.rimg, self.x, self.up_y, self.w,  self.up_h)

    def move(self):
        self.x = self.x + self.v

