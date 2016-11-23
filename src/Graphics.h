/*
 * Graphics.h
 *
 *  Created on: Nov 22, 2016
 *      Author: robin
 */

#ifndef SRC_GRAPHICS_H_
#define SRC_GRAPHICS_H_

#include <Arduboy.h>

class Graphics {
public:
	static void draw_digit(Arduboy *arduboy, int x, int y, int v, int color);
	static void draw_int(Arduboy *arduboy, int x, int y, int v, int color);
};

#endif /* SRC_GRAPHICS_H_ */
