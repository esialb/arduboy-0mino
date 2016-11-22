/*
 * Engine.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: robin
 */

#include <Engine.h>
#include <Arduboy.h>
#include "Shape.h"
#include "ShapeType.h"

Engine::Engine() {
	// TODO Auto-generated constructor stub
	if(bag == 0x7f)
		bag = 0;
	int id;
	do {
		id = (rand() & 0x7) % 7;
	} while(bag & (1 << id));
	bag |= (1 << id);
	next_id = id + 1;
}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

bool Engine::tick(Field &field, Arduboy &arduboy) {
	bool ret = false;

	uint8_t left = arduboy.pressed(LEFT_BUTTON) ? 1 : 0;
	uint8_t up = arduboy.pressed(UP_BUTTON) ? 1 : 0;
	uint8_t right = arduboy.pressed(RIGHT_BUTTON) ? 1 : 0;
	uint8_t down = arduboy.pressed(DOWN_BUTTON) ? 1 : 0;
	uint8_t a = arduboy.pressed(A_BUTTON) ? 1 : 0;
	uint8_t b = arduboy.pressed(B_BUTTON) ? 1 : 0;

	while(!field.get_shape()) {
		if(bag == 0x7f)
			bag = 0;
		int id = next_id;

		if(bag == 0x7f)
			bag = 0;
		int nid;
		do {
			nid = (random() & 0x7) % 7;
		} while(bag & (1 << nid));
		bag |= (1 << nid);
		next_id = nid + 1;

		const Shape *shape = ShapeType::for_id(id)->get_up();
		field.set_shape(shape);
		field.set_shape_x(4);
		field.set_shape_y(0);
		ret = true;
	}

	if(left + up + right + down != 1) {
		autoshifting = false;
		shift_held_frames = 0;
	} else {
		if(shift_held_frames == AUTOSHIFT_FRAMES)
			autoshifting = true;
		bool lock = down && !shift_held_frames;
		if(up && shift_held_frames == 0) {
			lock = autoshifting = true;
		} else
			up = 0;
		while(shift_held_frames == 0 || autoshifting) {
			if(left && field.can_shift(-1, 0))
				field.shift(-1, 0);
			else if(up && field.can_shift(0, 1))
				field.shift(0, 1);
			else if(right && field.can_shift(1, 0))
				field.shift(1, 0);
			else if(down && field.can_shift(0, 1)) {
				field.shift(0, 1);
				lock = false;
			} else
				break;
			if(shift_held_frames == 0 && !up)
				break;
		}
		ret = true;
		if(shift_held_frames < AUTOSHIFT_FRAMES)
			shift_held_frames++;
		if(lock) {
			field.blit_shape();
			field.set_shape(0);
			lines += field.clear_lines();
			rotating = false;
			return ret;
		}
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
			ret = true;
		}
	}
	return ret;
}

int Engine::get_lines() const {
	return lines;
}
int Engine::get_next_id() const {
	return next_id;
}
