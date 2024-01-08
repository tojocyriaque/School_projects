from food import *

class Snake:
    def __init__(self):
        self.size = 20
        self.head = (1, 3)
        self.direction = "down"
        self.length = 3
        self.body = [(1,3), (1, 2), (1, 1)]

    def update(self):
        for i in range(self.length-1,0,-1):
            self.body[i] = self.body[i-1]
        self.body[0] = self.head
    
    def move(self):
        if self.direction == "down":
            self.head = (self.head[0],self.head[1]+1)
        if self.direction == "up":
            self.head = (self.head[0],self.head[1]-1)
        if self.direction == "right":
            self.head = (self.head[0]+1,self.head[1])
        if self.direction == "left":
            self.head = (self.head[0]-1,self.head[1])

        self.update()

    def move_left(self):
        if self.direction != "right":
            self.direction = "left"
    
    def move_right(self):
        if self.direction != "left":
            self.direction = "right"

    def move_up(self):
        if self.direction != "down":
            self.direction = "up"

    def move_down(self):
        if self.direction != "up":
            self.direction = "down"

    def eat(self, food):
        self.head = (food.x, food.y)
        for i in range(self.length-1):
            self.body[i] = self.body[i+1]
        self.body.insert(0,(food.x,food.y))
        self.length += 1

    def collapse(self):
        if self.length>=3:
            for i in range(3,self.length):
                if self.body[i]==self.head:
                    return True
        return False

    def show(self):
        py5.fill(0,0,255);
        for p in self.body:
            py5.rect(p[0]*self.size, p[1]*self.size, self.size, self.size)


