
#include <iostream>
#include <cmath>
#include <unistd.h>

extern "C" {
#include "gfx.h"
}

void draw_polygon(int *x, int *y, int n, bool closed = false)
{
	for (int i = 0; i < n - 1; i ++)
		gfx_line(x[i],y[i],x[i+1],y[i+1]);
	if (closed)
		gfx_line(x[0],y[0],x[n-1],y[n-1]);
}

void draw_circle(int xc, int yc, int radius)
{
	int x[18];
	int y[18];
	for (int i = 0; i < 18; i++)
	{
		double angle = i*20.0*3.14159/180.0;
		x[i] = xc + cos(angle)*radius;
		y[i] = yc + sin(angle)*radius;
	}

	draw_polygon(x, y, 18, true);
}

void draw_state(int x, int y)
{
	gfx_clear();

	gfx_color(255, 255, 0);
	draw_circle(x, y, 50);

	gfx_color(0, 255, 0);
	draw_circle(x, y, 40);

	gfx_color(0, 255, 255);
	draw_circle(x, y, 30);

	gfx_color(255, 0, 255);
	draw_circle(x, y, 20);
}

int main()
{
	gfx_open(500, 500, "My first window");

	// start in middle of the screen
	int x = gfx_xsize() / 2;
	int y = gfx_ysize() / 2;
	int dx = 1;
	int dy = 1;

	while(true)
	{
		
		if (gfx_event_waiting())
		{
			int button = gfx_wait();

			// print information about the event
			std::cout << "got event: " << button;
			// print character keys
			if (button > 31 && button < 128) std::cout << " " << char(button);
			// mouse events
			if (button < 10) std::cout << " at pos (" << gfx_xpos() << "," << gfx_ypos() << ")";
			std::cout << std::endl;

			// when do we quit?
			if (button == 'x' || button == 'q')
				break;

			// up arrow
			if (button == 65431 || button == 65362) dy--;
			// down arrow
			if (button == 65433 || button == 65364) dy++;
			// left arroow
			if (button == 65430 || button == 65361) dx--;
			// right arroow
			if (button == 65432 || button == 65363) dx++;
		}
		else
		{
			// move the centroids
			x = x + dx;
			y = y + dy;

			// did we go past edge of window?
			if (x > gfx_xsize()) x = 0;
			if (y > gfx_ysize()) y = 0;
			if (x < 0) x = gfx_xsize();
			if (y < 0) y = gfx_ysize();

			// sleep 10,000 usec or 10 msec.
			usleep(10000);

			// update the drawing
			draw_state(x, y);
		}
	}

	return 0;
}

