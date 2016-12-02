/*
 * Field.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: robin
 */

#include <Field.h>

#include <Arduboy.h>
#include <string.h>
#include "Block.h"

#include "KickTable.h"

Field::Field() {
	reset();
}

Field::~Field() {
	// TODO Auto-generated destructor stub
}

void Field::reset() {
	memset(this->blocks, 0, sizeof(this->blocks));
/*
	for(int y = -HIDDEN_HEIGHT; y < HEIGHT; y++) {
		set_block(0, y, Block::LEFT);
		set_block(WIDTH - 1, y, Block::RIGHT);
	}
	for(int x = 0; x < WIDTH; x++) {
		or_block(x, HEIGHT - 1, Block::DOWN);
	}
*/
}

uint8_t Field::get_block(int x, int y) const {
	uint8_t bb = blocks[(y + HIDDEN_HEIGHT) * WIDTH / 2 + x / 2];
	if(x & 1)
		bb = (bb >> 4);
	return bb & 0xf;
}

uint8_t Field::get_block_with_shape(int x, int y) const {
	uint8_t block = get_block(x, y);
	if(shape) {
		uint8_t sb = 0;
		if(x >= shape_x && x < shape_x + 4 && y >= shape_y && y < shape_y + 4) {
			sb = shape->get_block(x - shape_x, y - shape_y, 0);
			if(sb)
				sb |= Block::LEFT | Block::RIGHT | Block::UP | Block::DOWN;
		}
		if(!sb && x >= shape_x && x < shape_x + 4 && y >= ghost_y && y < ghost_y + 4) {
			sb = shape->get_block(x - shape_x, y - ghost_y, 0);
		}
		if(sb)
			block = sb;
	}
	return block;
}
uint8_t Field::get_shape_block(int x, int y) const {
	uint8_t block = 0;
	if(shape) {
		uint8_t sb = 0;
		if(x >= shape_x && x < shape_x + 4 && y >= shape_y && y < shape_y + 4) {
			sb = shape->get_block(x - shape_x, y - shape_y, 0);
			if(sb)
				sb |= Block::LEFT | Block::RIGHT | Block::UP | Block::DOWN;
		}
		if(!sb && x >= shape_x && x < shape_x + 4 && y >= ghost_y && y < ghost_y + 4) {
			sb = shape->get_block(x - shape_x, y - ghost_y, 0);
		}
		if(sb)
			block = sb;
	}
	return block;
}
void Field::set_block(int x, int y, uint8_t block) {
	uint8_t bb = blocks[(y + HIDDEN_HEIGHT) * WIDTH / 2 + x / 2];
	if(x & 1) {
		bb = bb & 0xf;
		bb = bb | (block << 4);
	} else {
		bb = bb & 0xf0;
		bb = bb | block;
	}
	blocks[(y + HIDDEN_HEIGHT) * WIDTH / 2 + x / 2] = bb;
}
void Field::or_block(int x, int y, uint8_t block) {
	uint8_t bb = get_block(x, y);
	if(x & 1) {
		bb = (bb >> 4) | block;
	} else {
		bb = (bb & 0xf) | block;
	}
	set_block(x, y, bb);
}
void Field::and_block(int x, int y, uint8_t block) {
	uint8_t bb = get_block(x, y);
	if(x & 1) {
		bb = (bb >> 4) & block;
	} else {
		bb = (bb & 0xf) & block;
	}
	set_block(x, y, bb);
}

void Field::draw(Arduboy &arduboy) const {
	arduboy.fillRect(1, 0, 3 + WIDTH * 3, 3 + HEIGHT * 3, BLACK);
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			uint8_t block = get_block(x, y);
			if(block)
				arduboy.fillRect(2 + 3*x, 1 + 3*y, 4, 4, WHITE);
		}
	}
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			uint8_t block = get_shape_block(x, y);
			if(block & Block::LEFT) {
				arduboy.drawPixel(2 + 3*x, 1 + 3*y, WHITE);
				arduboy.drawPixel(2 + 3*x, 1 + 3*y + 1, WHITE);
				arduboy.drawPixel(2 + 3*x, 1 + 3*y + 2, WHITE);
				arduboy.drawPixel(2 + 3*x, 1 + 3*y + 3, WHITE);
			}
			if(block & Block::RIGHT) {
				arduboy.drawPixel(2 + 3*x + 3, 1 + 3*y, WHITE);
				arduboy.drawPixel(2 + 3*x + 3, 1 + 3*y + 1, WHITE);
				arduboy.drawPixel(2 + 3*x + 3, 1 + 3*y + 2, WHITE);
				arduboy.drawPixel(2 + 3*x + 3, 1 + 3*y + 3, WHITE);
			}
			if(block & Block::UP) {
				arduboy.drawPixel(2 + 3*x, 1 + 3*y, WHITE);
				arduboy.drawPixel(2 + 3*x + 1, 1 + 3*y, WHITE);
				arduboy.drawPixel(2 + 3*x + 2, 1 + 3*y, WHITE);
				arduboy.drawPixel(2 + 3*x + 3, 1 + 3*y, WHITE);
			}
			if(block & Block::DOWN) {
				arduboy.drawPixel(2 + 3*x, 1 + 3*y + 3, WHITE);
				arduboy.drawPixel(2 + 3*x + 1, 1 + 3*y + 3, WHITE);
				arduboy.drawPixel(2 + 3*x + 2, 1 + 3*y + 3, WHITE);
				arduboy.drawPixel(2 + 3*x + 3, 1 + 3*y + 3, WHITE);
			}
		}
	}
}

const Shape *Field::get_shape() const {
	return shape;
}
void Field::set_shape(const Shape *shape) {
	this->shape = shape;
	update_ghost_y();
}

int Field::get_shape_x() const {
	return shape_x;
}
int Field::get_shape_y() const {
	return shape_y;
}
void Field::set_shape_x(int shape_x) {
	this->shape_x = shape_x;
	update_ghost_y();
}
void Field::set_shape_y(int shape_y) {
	this->shape_y = shape_y;
	update_ghost_y();
}

void Field::blit_shape() {
	if(!shape)
		return;
	int id = shape->get_id();
	for(int y = 0; y < Shape::HEIGHT; y++) {
		for(int x = 0; x < Shape::WIDTH; x++) {
			uint8_t block = shape->get_block(x, y, 0);
			if(block)
				set_block(shape_x + x, shape_y + y, 0xf);
		}
	}
}

bool Field::can_shift(int x, int y) const {
	if(!shape)
		return false;
	for(int sy = 0; sy < Shape::HEIGHT; sy++) {
		for(int sx = 0; sx < Shape::WIDTH; sx++) {
			int bx = x + shape_x + sx;
			int by = y + shape_y + sy;
			uint8_t block = shape->get_block(sx, sy, 0);
			if(block) {
				if(bx < LEFT_BOUNDARY || bx > RIGHT_BOUNDARY || by < UP_BOUNDARY || by > DOWN_BOUNDARY)
					return false;
				if(get_block(bx, by) & 0xf)
					return false;
			}
		}
	}
	return true;
}

bool Field::can_shape(const Shape *shape, int x, int y) const {
	if(!shape)
		return false;
	for(int sy = 0; sy < Shape::HEIGHT; sy++) {
		for(int sx = 0; sx < Shape::WIDTH; sx++) {
			int bx = x + sx;
			int by = y + sy;
			uint8_t block = shape->get_block(sx, sy, 0);
			if(block) {
				if(bx < LEFT_BOUNDARY || bx > RIGHT_BOUNDARY || by < UP_BOUNDARY || by > DOWN_BOUNDARY)
					return false;
				if(get_block(bx, by) & 0xf)
					return false;
			}
		}
	}
	return true;
}
bool Field::can_rotate_right() const {
	if(!shape)
		return false;
	const Shape *rotated = shape->rotate_right();
	for(int test = 0; test < KickTable::TESTS; test++) {
		int x = shape_x + KickTable::kick_x_right(shape, test);
		int y = shape_y - KickTable::kick_y_right(shape, test);
		if(can_shape(rotated, x, y))
			return true;
	}
	return false;
}
bool Field::can_rotate_left() const {
	if(!shape)
		return false;
	Shape *rotated = shape->rotate_left();
	for(int test = 0; test < KickTable::TESTS; test++) {
		int x = shape_x + KickTable::kick_x_left(shape, test);
		int y = shape_y - KickTable::kick_y_left(shape, test);
		if(can_shape(rotated, x, y))
			return true;
	}
	return false;
}

void Field::shift(int x, int y) {
	shape_x += x;
	shape_y += y;
	update_ghost_y();
}

void Field::rotate_left() {
	if(!shape)
		return;
	const Shape *rotated = shape->rotate_left();
	for(int test = 0; test < KickTable::TESTS; test++) {
		int x = shape_x + KickTable::kick_x_left(shape, test);
		int y = shape_y - KickTable::kick_y_left(shape, test);
		if(can_shape(rotated, x, y)) {
			shape = rotated;
			shape_x = x;
			shape_y = y;
			break;
		}
	}
	update_ghost_y();
}

void Field::rotate_right() {
	if(!shape)
		return;
	const Shape *rotated = shape->rotate_right();
	for(int test = 0; test < KickTable::TESTS; test++) {
		int x = shape_x + KickTable::kick_x_right(shape, test);
		int y = shape_y - KickTable::kick_y_right(shape, test);
		if(can_shape(rotated, x, y)) {
			shape = rotated;
			shape_x = x;
			shape_y = y;
			break;
		}
	}
	update_ghost_y();
}

void Field::update_ghost_y() {
	ghost_y = 0;
	if(!shape)
		return;
	ghost_y = shape_y;
	int gy = 1;
	while(can_shift(0, gy)) {
		ghost_y++;
		gy++;
	}
}

int Field::clear_lines() {
	int cleared = 0;
	for(int y = DOWN_BOUNDARY; y >= UP_BOUNDARY;) {
		bool filled = true;
		for(int x = LEFT_BOUNDARY; x <= RIGHT_BOUNDARY; x++) {
			if(!(get_block(x, y) & 0xf)) {
				filled = false;
				break;
			}
		}
		if(filled) {
			cleared++;
			memmove(blocks + WIDTH / 2, blocks, WIDTH * (y + HIDDEN_HEIGHT) / 2);
			memset(blocks, 0, WIDTH / 2);
			for(int x = 0; x < WIDTH; x++) {
				if(y < DOWN_BOUNDARY && (get_block(x, y) & 0xf) && !(get_block(x, y+1) & 0xf))
					or_block(x, y, Block::DOWN);
				else if(y < DOWN_BOUNDARY && !(get_block(x, y) & 0xf) && (get_block(x, y+1) & 0xf))
					or_block(x, y+1, Block::UP);
			}
		} else
			y--;
	}
	return cleared;
}
