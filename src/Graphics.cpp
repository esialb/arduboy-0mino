/*
 * Graphics.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: robin
 */

#include <Graphics.h>

#include <string.h>

void Graphics::draw_digit(Arduboy *arduboy, int x, int y, int v, int color) {
	switch(v) {
	case 0:
		arduboy->drawPixel(x+1, y, color);
		arduboy->drawPixel(x, y+1, color);
		arduboy->drawPixel(x, y+2, color);
		arduboy->drawPixel(x, y+3, color);
		arduboy->drawPixel(x+2, y+1, color);
		arduboy->drawPixel(x+2, y+2, color);
		arduboy->drawPixel(x+2, y+3, color);
		arduboy->drawPixel(x+1, y+4, color);
		break;
	case 1:
		arduboy->drawPixel(x+1, y+0, color);
		arduboy->drawPixel(x+1, y+1, color);
		arduboy->drawPixel(x+1, y+2, color);
		arduboy->drawPixel(x+1, y+3, color);
		arduboy->drawPixel(x+1, y+4, color);
		arduboy->drawPixel(x+0, y+1, color);
		arduboy->drawPixel(x+0, y+4, color);
		arduboy->drawPixel(x+2, y+4, color);
		break;
	case 2:
		arduboy->drawPixel(x+0, y+0, color);
		arduboy->drawPixel(x+1, y+0, color);
		arduboy->drawPixel(x+2, y+1, color);
		arduboy->drawPixel(x+1, y+2, color);
		arduboy->drawPixel(x+0, y+3, color);
		arduboy->drawPixel(x+0, y+4, color);
		arduboy->drawPixel(x+1, y+4, color);
		arduboy->drawPixel(x+2, y+4, color);
		break;
	case 3:
		arduboy->drawPixel(x+0, y+0, color);
		arduboy->drawPixel(x+1, y+0, color);
		arduboy->drawPixel(x+2, y+0, color);
		arduboy->drawPixel(x+2, y+1, color);
		arduboy->drawPixel(x+1, y+2, color);
		arduboy->drawPixel(x+2, y+3, color);
		arduboy->drawPixel(x+1, y+4, color);
		arduboy->drawPixel(x+0, y+4, color);
		break;
	case 4:
		arduboy->drawPixel(x+0, y+0, color);
		arduboy->drawPixel(x+2, y+0, color);
		arduboy->drawPixel(x+0, y+1, color);
		arduboy->drawPixel(x+2, y+1, color);
		arduboy->drawPixel(x+0, y+2, color);
		arduboy->drawPixel(x+1, y+2, color);
		arduboy->drawPixel(x+2, y+2, color);
		arduboy->drawPixel(x+2, y+3, color);
		arduboy->drawPixel(x+2, y+4, color);
		break;
	case 5:
		arduboy->drawPixel(x+0, y+0, color);
		arduboy->drawPixel(x+2, y+0, color);
		arduboy->drawPixel(x+1, y+0, color);
		arduboy->drawPixel(x+0, y+1, color);
		arduboy->drawPixel(x+0, y+2, color);
		arduboy->drawPixel(x+1, y+2, color);
		arduboy->drawPixel(x+2, y+3, color);
		arduboy->drawPixel(x+1, y+4, color);
		arduboy->drawPixel(x+0, y+4, color);
		break;
	case 6:
		arduboy->drawPixel(x+1, y+0, color);
		arduboy->drawPixel(x+2, y+0, color);
		arduboy->drawPixel(x+0, y+1, color);
		arduboy->drawPixel(x+0, y+2, color);
		arduboy->drawPixel(x+1, y+2, color);
		arduboy->drawPixel(x+0, y+3, color);
		arduboy->drawPixel(x+2, y+3, color);
		arduboy->drawPixel(x+0, y+4, color);
		arduboy->drawPixel(x+1, y+4, color);
		arduboy->drawPixel(x+2, y+4, color);
		break;
	case 7:
		arduboy->drawPixel(x+0, y+0, color);
		arduboy->drawPixel(x+1, y+0, color);
		arduboy->drawPixel(x+2, y+0, color);
		arduboy->drawPixel(x+2, y+1, color);
		arduboy->drawPixel(x+1, y+2, color);
		arduboy->drawPixel(x+1, y+3, color);
		arduboy->drawPixel(x+0, y+4, color);
		break;
	case 8:
		arduboy->drawPixel(x+0, y+0, color);
		arduboy->drawPixel(x+1, y+0, color);
		arduboy->drawPixel(x+2, y+0, color);
		arduboy->drawPixel(x+0, y+1, color);
		arduboy->drawPixel(x+2, y+1, color);
		arduboy->drawPixel(x+0, y+2, color);
		arduboy->drawPixel(x+1, y+2, color);
		arduboy->drawPixel(x+2, y+2, color);
		arduboy->drawPixel(x+0, y+3, color);
		arduboy->drawPixel(x+2, y+3, color);
		arduboy->drawPixel(x+0, y+4, color);
		arduboy->drawPixel(x+1, y+4, color);
		arduboy->drawPixel(x+2, y+4, color);
		break;
	case 9:
		arduboy->drawPixel(x+0, y+0, color);
		arduboy->drawPixel(x+1, y+0, color);
		arduboy->drawPixel(x+2, y+0, color);
		arduboy->drawPixel(x+0, y+1, color);
		arduboy->drawPixel(x+2, y+1, color);
		arduboy->drawPixel(x+0, y+2, color);
		arduboy->drawPixel(x+1, y+2, color);
		arduboy->drawPixel(x+2, y+2, color);
		arduboy->drawPixel(x+2, y+3, color);
		arduboy->drawPixel(x+1, y+4, color);
		arduboy->drawPixel(x+0, y+4, color);
		break;
	}
}

void Graphics::draw_int(Arduboy *arduboy, int x, int y, int v, int color) {
	char buf[12];
	itoa(v, buf, 10);
	for(int i = 0; i < sizeof(buf) && buf[i]; i++)
		draw_digit(arduboy, x + 4*i, y, buf[i] - '0', color);

}
