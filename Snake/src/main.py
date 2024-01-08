from snake import *

f = Food()
s = Snake()
GAME_OVER = False
hx, hy = 0, 0

def setup():
    py5.size(500, 500, py5.P3D)

def key_pressed():
    global s
    if py5.key_code==38:
        s.move_up()
    
    elif py5.key_code==40:
        s.move_down()
    
    elif py5.key_code==37:
        s.move_left()

    elif py5.key_code==39:
        s.move_right()

def draw():
    global s, f, GAME_OVER
    hx, hy = s.head
    py5.background(100)
    
    py5.no_stroke()

    if hx<0 or hx>=py5.width or hy<0 or hy>=py5.height:
        GAME_OVER = True

    elif s.collapse():
        GAME_OVER = True
        
    if py5.frame_count%20==0:
        if not GAME_OVER:
            s.move()
    
    if s.head == (f.x, f.y):
        s.eat(f)
        f = Food()

    f.show()
    s.show()

if __name__ == "__main__":
    py5.run_sketch()


