/*
 * main.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: robin
 */


#include <Arduboy.h>

int SCREEN_WIDTH = WIDTH;
int SCREEN_HEIGHT = HEIGHT;

#include "Field.h"
#include "Shape.h"

Arduboy arduboy;
Field field;

void setup() {
	arduboy.begin();
	arduboy.fillRect(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, WHITE);
	field.set_shape(&(Shape::L_UP));
	field.set_shape_x(4);
	field.set_shape_y(16);
	field.blit_shape();
	field.set_shape_y(12);
	field.draw(arduboy);
	arduboy.display();
}

void loop() {

}
