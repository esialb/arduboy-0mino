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

#define AUTOSHIFT_FRAMES 30

bool autoshifting = false;
int shift_held_frames = 0;
bool rotating = false;

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
	if(!arduboy.nextFrame())
		return;
	int left = arduboy.pressed(LEFT_BUTTON) ? 1 : 0;
	int up = arduboy.pressed(UP_BUTTON) ? 1 : 0;
	int right = arduboy.pressed(RIGHT_BUTTON) ? 1 : 0;
	int down = arduboy.pressed(DOWN_BUTTON) ? 1 : 0;
	int a = arduboy.pressed(A_BUTTON) ? 1 : 0;
	int b = arduboy.pressed(B_BUTTON) ? 1 : 0;

	if(left + up + right + down != 1) {
		autoshifting = false;
		shift_held_frames = 0;
	} else {
		if(shift_held_frames == AUTOSHIFT_FRAMES)
			autoshifting = true;
		while(shift_held_frames == 0 || autoshifting) {
			if(left && field.can_shift(-1, 0))
				field.shift(-1, 0);
			else if(up && field.can_shift(0, -1))
				field.shift(0, -1);
			else if(right && field.can_shift(1, 0))
				field.shift(1, 0);
			else if(down && field.can_shift(0, 1))
				field.shift(0, 1);
			else
				break;
			if(shift_held_frames == 0)
				break;
		}
		if(shift_held_frames < AUTOSHIFT_FRAMES)
			shift_held_frames++;
	}

	if(a + b != 1)
		rotating = false;
	else {
		if(!rotating) {
			if(a && field.can_rotate_left())
				field.rotate_left();
			if(b && field.can_rotate_right())
				field.rotate_right();
			rotating = true;
		}
	}

	field.draw(arduboy);
	arduboy.display();
}
