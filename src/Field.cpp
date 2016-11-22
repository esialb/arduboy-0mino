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
		if(x >= shape_x && x < shape_x + 4 && y >= shape_y && y < shape_y + 4)
			sb = shape->get_block(x - shape_x, y - shape_y, 0);
		if(!sb && x >= shape_x && x < shape_x + 4 && y >= ghost_y && y < ghost_y + 4) {
			sb = shape->get_block(x - shape_x, y - ghost_y, 0);
			if(sb)
				sb = block | Block::FILLED;
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
	arduboy.fillRect(1, 1, 1 + WIDTH * 3, 1 + HEIGHT * 3, WHITE);
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			uint8_t block = get_block_with_shape(x, y);
			if(block & Block::LEFT) {
				arduboy.drawPixel(1 + 3*x, 1 + 3*y, BLACK);
				arduboy.drawPixel(1 + 3*x, 1 + 3*y + 1, BLACK);
				arduboy.drawPixel(1 + 3*x, 1 + 3*y + 2, BLACK);
				arduboy.drawPixel(1 + 3*x, 1 + 3*y + 3, BLACK);
			}
			if(block & Block::RIGHT) {
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y, BLACK);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y + 1, BLACK);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y + 2, BLACK);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y + 3, BLACK);
			}
			if(block & Block::UP) {
				arduboy.drawPixel(1 + 3*x, 1 + 3*y, BLACK);
				arduboy.drawPixel(1 + 3*x + 1, 1 + 3*y, BLACK);
				arduboy.drawPixel(1 + 3*x + 2, 1 + 3*y, BLACK);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y, BLACK);
			}
			if(block & Block::DOWN) {
				arduboy.drawPixel(1 + 3*x, 1 + 3*y + 3, BLACK);
				arduboy.drawPixel(1 + 3*x + 1, 1 + 3*y + 3, BLACK);
				arduboy.drawPixel(1 + 3*x + 2, 1 + 3*y + 3, BLACK);
				arduboy.drawPixel(1 + 3*x + 3, 1 + 3*y + 3, BLACK);
			}
			if(block & Block::FILLED) {
				arduboy.drawPixel(1 + 3*x + 1, 1 + 3*y + 1, BLACK);
				arduboy.drawPixel(1 + 3*x + 1, 1 + 3*y + 2, BLACK);
				arduboy.drawPixel(1 + 3*x + 2, 1 + 3*y + 1, BLACK);
				arduboy.drawPixel(1 + 3*x + 2, 1 + 3*y + 2, BLACK);
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
	for(int y = 0; y < Shape::HEIGHT; y++) {
		for(int x = 0; x < Shape::WIDTH; x++) {
			uint8_t block = shape->get_block(x, y, 0);
			if(block) {
				block |= Block::FILLED | Block::UP | Block::LEFT | Block::DOWN | Block::RIGHT;
				set_block(shape_x + x, shape_y + y, block);
			}
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

bool Field::can_shape(const Shape *shape) const {
	if(!shape)
		return false;
	for(int sy = 0; sy < Shape::HEIGHT; sy++) {
		for(int sx = 0; sx < Shape::WIDTH; sx++) {
			int bx = shape_x + sx;
			int by = shape_y + sy;
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
	return can_shape(shape->rotate_right());
}
bool Field::can_rotate_left() const {
	return can_shape(shape->rotate_left());
}

void Field::shift(int x, int y) {
	shape_x += x;
	shape_y += y;
	update_ghost_y();
}

void Field::rotate_left() {
	if(!shape)
		return;
	shape = shape->rotate_left();
	update_ghost_y();
}

void Field::rotate_right() {
	if(!shape)
		return;
	shape = shape->rotate_right();
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
