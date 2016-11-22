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
	for(int y = 0; y < HEIGHT; y++) {
		this->set_block(0, y, Block::LEFT);
		this->set_block(WIDTH - 1, y, Block::RIGHT);
	}
	for(int x = 0; x < WIDTH; x++) {
		this->or_block(x, HEIGHT - 1, Block::DOWN);
	}
}

uint8_t Field::get_block(int x, int y) const {
	uint8_t block = this->blocks[y * WIDTH + x];
	if(this->shape && x >= this->shape_x && x < this->shape_x + 4 && y >= this->shape_y && y < this->shape_y + 4)
		block = this->shape->get_block(x - this->shape_x, y - this->shape_y, block);
	return block;
}
void Field::set_block(int x, int y, uint8_t block) {
	this->blocks[y * WIDTH + x] = block;
}
void Field::or_block(int x, int y, uint8_t block) {
	this->blocks[y * WIDTH + x] |= block;
}
void Field::and_block(int x, int y, uint8_t block) {
	this->blocks[y * WIDTH + x] &= block;
}

void Field::draw(Arduboy &arduboy) const {
	arduboy.fillRect(1, 1, 1 + WIDTH * 3, 1 + HEIGHT * 3, WHITE);
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			uint8_t block = get_block(x, y);
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
	return this->shape;
}
void Field::set_shape(const Shape *shape) {
	this->shape = shape;
}

int Field::get_shape_x() const {
	return this->shape_x;
}
int Field::get_shape_y() const {
	return this->shape_y;
}
void Field::set_shape_x(int shape_x) {
	this->shape_x = shape_x;
}
void Field::set_shape_y(int shape_y) {
	this->shape_y = shape_y;
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
