from bird import *

tubes = []
b = None
bg = None
bird_img = None
tube_img = None
tube_reverse = None
score = 0
velocity = 20
s_velocity = -10
game_over = False

def setup():
    global bg, b, bird_img, tube_img, tube_reverse
    py5.size(800,600)
    py5.text_size(2)

    bg = py5.load_image("../images/city_bg.jpeg")
    bird_img = py5.load_image("../images/bird4.png")
    tube_img = py5.load_image("../images/tube.png")
    tube_reverse = py5.load_image("../images/tube_reverse.png")

    b = Bird(bird_img)

def key_pressed():
    global b, tubes, game_over, score

    if py5.key_code==32:
        b.jump()

    elif py5.key=='€r' or py5.key=='R' and game_over:
        game_over = False
        score = 0
        restart()

def x_die(b, tube):
    for x in [b.x-b.size/2, b.x+b.size/2]:
        if tube.x<=x<=tube.x+tube.w:
            return True
    return False

def y_die(b, tube):
    for y in [b.y-b.size/2, b.y+b.size/2]:
        if tube.down_y<=y<=tube.down_y+tube.down_h or tube.up_y<=y<=tube.up_y+tube.up_h :
            return True
    return False

def restart():
    global b, bird_img, tubes
    b = Bird(bird_img)
    tubes = []

def draw():
    global b, bg, tubes, bird_img, tube_img, tube_reverse,score,velocity,s_velocity,game_over
    py5.image(bg, 0, 0, py5.width, py5.height)
   
    if not game_over:
        if py5.frame_count%velocity == 0:
            tubes.append(Tube(tube_img, tube_reverse))
            tubes[-1].v = s_velocity

            if score>0 and score%5 == 0:
                py5.frame_rate(py5.get_frame_rate()+1)

        for tube in tubes:
            if x_die(b,tube) and y_die(b,tube):
                game_over = True

            elif b.x == tube.x:
                score = score + 1    

    
    for tube in tubes:
        if not game_over:
            tube.move()
        tube.show()

    if not game_over:
        b.move()

    b.show()
    py5.text("score:"+str(score),10,20)

py5.run_sketch()

