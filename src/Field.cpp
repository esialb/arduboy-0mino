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
	for(int y = -HIDDEN_HEIGHT; y < HEIGHT; y++) {
		set_block(0, y, Block::LEFT);
		set_block(WIDTH - 1, y, Block::RIGHT);
	}
	for(int x = 0; x < WIDTH; x++) {
		or_block(x, HEIGHT - 1, Block::DOWN);
	}
}

uint8_t Field::get_block(int x, int y) const {
	return blocks[(y + HIDDEN_HEIGHT) * WIDTH + x];
}

uint8_t Field::get_block_with_shape(int x, int y) const {
	uint8_t block = get_block(x, y);
	if(shape) {
		uint8_t sb = 0;
		if(x >= shape_x && x < shape_x + 4 && y >= shape_y && y < shape_y + 4) {
			sb = shape->get_block(x - shape_x, y - shape_y, 0);
			if(sb)
				sb |= Block::LEFT | Block::RIGHT | Block::UP | Block::DOWN | Block::FILLED;
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
	blocks[(y + HIDDEN_HEIGHT) * WIDTH + x] = block;
}
void Field::or_block(int x, int y, uint8_t block) {
	blocks[(y + HIDDEN_HEIGHT) * WIDTH + x] |= block;
}
void Field::and_block(int x, int y, uint8_t block) {
	blocks[(y + HIDDEN_HEIGHT) * WIDTH + x] &= block;
}

void Field::draw(Arduboy &arduboy) const {
	arduboy.fillRect(1, 1, 1 + WIDTH * 3, 1 + HEIGHT * 3, BLACK);
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			uint8_t block = get_block_with_shape(x, y);
			if(block & Block::LEFT) {
				arduboy.drawPixel(1 + 3*x, 1 + 3*y, WHITE);
				arduboy.drawPixel(1 + 3*x, 1 + 3*y + 1, WHITE);
				arduboy.drawPixel(1 + 3*x, 1 + 3*y + 2, WHITE);
				arduboy.drawPixel(1 + 3*x, 1 + 3*y + 3, WHITE);
			}
			if(block & Block::RIGHT) {
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y, WHITE);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y + 1, WHITE);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y + 2, WHITE);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y + 3, WHITE);
			}
			if(block & Block::UP) {
				arduboy.drawPixel(1 + 3*x, 1 + 3*y, WHITE);
				arduboy.drawPixel(1 + 3*x + 1, 1 + 3*y, WHITE);
				arduboy.drawPixel(1 + 3*x + 2, 1 + 3*y, WHITE);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y, WHITE);
			}
			if(block & Block::DOWN) {
				arduboy.drawPixel(1 + 3*x, 1 + 3*y + 3, WHITE);
				arduboy.drawPixel(1 + 3*x + 1, 1 + 3*y + 3, WHITE);
				arduboy.drawPixel(1 + 3*x + 2, 1 + 3*y + 3, WHITE);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y + 3, WHITE);
			}
			if(block & Block::FILLED) {
				arduboy.drawPixel(1 + 3*x + 1, 1 + 3*y + 1, WHITE);
				arduboy.drawPixel(1 + 3*x + 2, 1 + 3*y + 2, WHITE);
				if(!(block & Block::SHAPE)) {
					arduboy.drawPixel(1 + 3*x + 1, 1 + 3*y + 2, WHITE);
					arduboy.drawPixel(1 + 3*x + 2, 1 + 3*y + 1, WHITE);
				}
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
				set_block(shape_x + x, shape_y + y, block | id | Block::FILLED);
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
				if(get_block(bx, by) & Block::FILLED)
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
				if(get_block(bx, by) & Block::FILLED)
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
			if(!(get_block(x, y) & Block::FILLED)) {
				filled = false;
				break;
			}
		}
		if(filled) {
			cleared++;
			memmove(blocks + WIDTH, blocks, WIDTH * (y + HIDDEN_HEIGHT));
			memset(blocks, 0, WIDTH);
			set_block(0, 0, Block::LEFT);
			set_block(WIDTH - 1, 0, Block::RIGHT);
			for(int x = 0; x < WIDTH; x++) {
				if(y == DOWN_BOUNDARY)
					or_block(x, y, Block::DOWN);
				else if((get_block(x, y) & Block::FILLED) && !(get_block(x, y+1) & Block::FILLED))
					or_block(x, y, Block::DOWN);
				else if(!(get_block(x, y) & Block::FILLED) && (get_block(x, y+1) & Block::FILLED))
					or_block(x, y+1, Block::UP);
			}
		} else
			y--;
	}
	return cleared;
}
