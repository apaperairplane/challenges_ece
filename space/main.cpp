#include <iostream>
#include <chrono>
#include <thread>

extern "C"  {
#include "gfx.h"
}

void drawAlien(int x, int y){
        gfx_color(93, 42, 232);
        gfx_line(x, y, x+5, y);
	gfx_line(x+5, y, x+5, y+15);
	gfx_line(x+5, y+15, x+10, y+15);
	gfx_line(x+10, y+15, x+10, y+10);
	gfx_line(x+10, y+10, x, y+10);
	gfx_line(x, y+10, x, y+20);
	gfx_line(x, y+20, x+5, y+20);
	gfx_line(x+5, y+20, x+5, y+25);
	gfx_line(x+5, y+25, x+20, y+25);
	gfx_line(x+20, y+25, x+20, y+20);
	gfx_line(x+20, y+20, x+25, y+20);
	gfx_line(x+25, y+20, x+25, y+10);
	gfx_line(x+25, y+10, x+15, y+10);
	gfx_line(x+15, y+10, x+15, y+15);
	gfx_line(x+15, y+15, x+20, y+15);
	gfx_line(x+20, y+15, x+20, y);
	gfx_line(x+20, y, x+25, y);
	gfx_line(x+25, y, x+25, y+5);
	gfx_line(x+25, y+5, x, y+5);
	gfx_line(x, y+5, x, y);
}

void drawPlayer(int x, int y){
	gfx_color(255, 46, 191);
	gfx_line(x+5, y+15, x+5, y+25);
	gfx_line(x+5, y+25, x+20, y+25);
	gfx_line(x+20, y+25, x+20, y+15);
	gfx_line(x+20, y+15, x+15, y+15);
	gfx_line(x+15, y+15, x+15, y+5);
	gfx_line(x+15, y+5, x+10, y+5);
	gfx_line(x+10, y+5, x+10, y+15);
	gfx_line(x+10, y+15, x+5, y+15);
}

void drawShield(int x, int y, int damage){
	if(damage < 3){
		gfx_line(x, y, x, y+25);
		gfx_line(x, y+25, x+25, y+25);
		gfx_line(x+25, y+25, x+25, y);
		gfx_line(x+25, y, x, y);
		if(damage > 1){
			gfx_line(x, y, x+25, y+25);
		}if(damage > 2){
			gfx_line(x+25, y, x, y+25);
		}
	}
}

void drawBullet(int x, int y){
	gfx_line(x+10, y+5, x+10, y+20);
	gfx_line(x+10, y+20, x+15, y+20);
	gfx_line(x+15, y+20, x+15, y+5);
	gfx_line(x+15, y+5, x+10 , y+5);
}

// Grid is 175x300 each graphic is 25x25 and that is one space within the grid
// add 5 as space between grid squares

using namespace std::chrono;
using namespace std::this_thread;
int main(){

	gfx_open(210,360,"Space_Invaders_Bootleg");
	gfx_clear_color(8, 9, 48);
	gfx_clear();
	int px = 90;
	int py = 330;

	int x = 5;
	int y = 5;
	int s1d = 0; //shield 'x' damage 'x' = any int
        int s2d = 0;
        int s3d = 0;
	bool movehalfbeat = true;
	bool reverse = false;
	bool bulletTime = false;
	int bullety = 0;
	int bulletx = 0;
	bool alienDed = false;

	while(true){
		if(gfx_event_waiting()){
			char c = gfx_wait();
			if(c == 'd'){
				if(px+30 < 210){
					px += 30;
				}
			}else if(c == 'a'){
				if(px-30 >= 0){
					px -= 30;
				}
			}
			else if(c == 'p'){
				break;
			}else if(c == 's'){
				drawBullet(px,py);
				bulletTime = true;
				bullety = py;
				bulletx = px;
			}
			gfx_clear();
			drawAlien(x,y);
			drawShield(30, 300, s1d);
			drawShield(90, 300, s2d);
			drawShield(150, 300, s3d);
			drawPlayer(px,py);
		}
		
		sleep_for(milliseconds(65));
		sleep_until(steady_clock::now() + milliseconds(65));
		if(movehalfbeat){
			gfx_clear();
			if(alienDed){
				break;
			}
	                drawAlien(x,y);
	                drawShield(30, 300, s1d);
	                drawShield(90, 300, s2d);
		        drawShield(150, 300, s3d);
			movehalfbeat = false;
			drawPlayer(px,py);
			if(bulletTime){
				drawBullet(bulletx, bullety);
			}
			if(reverse){
                                if(x - 30 >= 0){
                                        x -= 30;
                                }else if(x + 30 < 210){
					y += 30;
					reverse = false;
                                }
                        }else{
                                if(x + 30 < 210){
                                        x += 30;
                                }else if(x - 30 >= 0){
					y += 30;
					reverse = true;
                                }
                        }
		}else{
			movehalfbeat = true;
		}
		if(bulletTime){
                                if(bulletx > x && bulletx < x + 40  && bullety > y && bullety < y + 40){
                                        bulletTime = false;
					alienDed = true;
                                }else if(bullety > 5){
                                        drawBullet(bulletx, bullety);
                                        bullety -= 30;
                                }else{
                                        bulletTime = false;
                                }

                        }
	}

	return 0;
}
