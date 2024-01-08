from spot import *

class Bird:

    def __init__(self,img):
        self.x = 200
        self.y = 400
        
        self.v = 0
        self.g = 1.5
        
        self.size = 30
        self.img = img
        
    def jump(self):
        self.v = -10

    def move(self):
        self.y = self.y + self.v
        self.v = self.v + self.g

        self.y = py5.constrain(self.y,0,430)

    def show(self):
        py5.image(self.img, self.x-self.size/2, self.y-self.size/2, self.size, self.size)
