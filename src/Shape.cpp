/*
 * Shape.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: robin
 */

#include <Shape.h>
#include "Field.h"
#include "Block.h"

#include <string.h>

#include "ShapeType.h"
#include "Direction.h"

Shape::Shape(
		uint8_t id, uint8_t dir,
		uint8_t x1, uint8_t y1,
		uint8_t x2, uint8_t y2,
		uint8_t x3, uint8_t y3,
		uint8_t x4, uint8_t y4) {
	this->id = id;
	this->dir = dir;
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->x4 = x4;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->y4 = y4;
	uint8_t s[4][4];
	memset(s, 0, sizeof(s));
	s[x1][y1] = 1;
	s[x2][y2] = 1;
	s[x3][y3] = 1;
	s[x4][y4] = 1;

	b1 = b2 = b3 = b4 = Block::LEFT | Block::UP | Block::RIGHT | Block::DOWN;

	if(x1 > 0 && s[x1-1][y1])
		b1 &= ~(Block::LEFT);
	if(x1 < 3 && s[x1+1][y1])
		b1 &= ~(Block::RIGHT);
	if(y1 > 0 && s[x1][y1-1])
		b1 &= ~(Block::UP);
	if(y1 < 3 && s[x1][y1+1])
		b1 &= ~(Block::DOWN);

	if(x2 > 0 && s[x2-1][y2])
		b2 &= ~(Block::LEFT);
	if(x2 < 3 && s[x2+1][y2])
		b2 &= ~(Block::RIGHT);
	if(y2 > 0 && s[x2][y2-1])
		b2 &= ~(Block::UP);
	if(y2 < 3 && s[x2][y2+1])
		b2 &= ~(Block::DOWN);


	if(x3 > 0 && s[x3-1][y3])
		b3 &= ~(Block::LEFT);
	if(x3 < 3 && s[x3+1][y3])
		b3 &= ~(Block::RIGHT);
	if(y3 > 0 && s[x3][y3-1])
		b3 &= ~(Block::UP);
	if(y3 < 3 && s[x3][y3+1])
		b3 &= ~(Block::DOWN);

	if(x4 > 0 && s[x4-1][y4])
		b4 &= ~(Block::LEFT);
	if(x4 < 3 && s[x4+1][y4])
		b4 &= ~(Block::RIGHT);
	if(y4 > 0 && s[x4][y4-1])
		b4 &= ~(Block::UP);
	if(y4 < 3 && s[x4][y4+1])
		b4 &= ~(Block::DOWN);

}

Shape::~Shape() {
	// TODO Auto-generated destructor stub
}

uint8_t Shape::get_block(uint8_t x, uint8_t y, uint8_t block) const {
	if(x == x1 && y == y1)
		return b1;
	if(x == x2 && y == y2)
		return b2;
	if(x == x3 && y == y3)
		return b3;
	if(x == x4 && y == y4)
		return b4;
	return block;
}

const Shape *Shape::rotate_right() const {
	ShapeType *type = ShapeType::for_id(id);
	return type->rotate_right(this);
}
const Shape *Shape::rotate_left() const {
	ShapeType *type = ShapeType::for_id(id);
	return type->rotate_left(this);
}

uint8_t Shape::get_id() const {
	return id;
}

uint8_t Shape::get_dir() const {
	return dir;
}

const Shape Shape::L_UP = Shape(
		ShapeType::L_ID, Direction::UP,
		0, 1,
		1, 1,
		2, 1,
		2, 0);
const Shape Shape::L_LEFT = Shape(
		ShapeType::L_ID, Direction::LEFT,
		0, 0,
		1, 0,
		1, 1,
		1, 2);
const Shape Shape::L_RIGHT = Shape(
		ShapeType::L_ID, Direction::RIGHT,
		1, 0,
		1, 1,
		1, 2,
		2, 2);
const Shape Shape::L_DOWN = Shape(
		ShapeType::L_ID, Direction::DOWN,
		0, 1,
		1, 1,
		2, 1,
		0, 2);
const Shape Shape::J_LEFT = Shape(
		ShapeType::J_ID, Direction::LEFT,
		1, 0,
		1, 1,
		1, 2,
		0, 2);
const Shape Shape::J_UP = Shape(
		ShapeType::J_ID, Direction::UP,
		0, 0,
		0, 1,
		1, 1,
		2, 1);
const Shape Shape::J_RIGHT = Shape(
		ShapeType::J_ID, Direction::RIGHT,
		1, 0,
		2, 0,
		1, 1,
		1, 2);
const Shape Shape::J_DOWN = Shape(
		ShapeType::J_ID, Direction::DOWN,
		0, 1,
		1, 1,
		2, 1,
		2, 2);
const Shape Shape::S_LEFT = Shape(
		ShapeType::S_ID, Direction::LEFT,
		1, 0,
		1, 1,
		2, 1,
		2, 2);
const Shape Shape::S_UP = Shape(
		ShapeType::S_ID, Direction::UP,
		1, 0,
		2, 0,
		0, 1,
		1, 1);
const Shape Shape::S_RIGHT = Shape(
		ShapeType::S_ID, Direction::RIGHT,
		1, 0,
		1, 1,
		2, 1,
		2, 2);
const Shape Shape::S_DOWN = Shape(
		ShapeType::S_ID, Direction::DOWN,
		1, 1,
		2, 1,
		1, 2,
		0, 2);
const Shape Shape::Z_LEFT = Shape(
		ShapeType::Z_ID, Direction::LEFT,
		1, 0,
		1, 1,
		0, 1,
		0, 2);
const Shape Shape::Z_UP = Shape(
		ShapeType::Z_ID, Direction::UP,
		0, 0,
		1, 0,
		1, 1,
		2, 1);
const Shape Shape::Z_RIGHT = Shape(
		ShapeType::Z_ID, Direction::RIGHT,
		2, 0,
		2, 1,
		1, 1,
		1, 2);
const Shape Shape::Z_DOWN = Shape(
		ShapeType::Z_ID, Direction::DOWN,
		0, 1,
		1, 1,
		1, 2,
		2, 2);
const Shape Shape::T_LEFT = Shape(
		ShapeType::T_ID, Direction::LEFT,
		1, 0,
		0, 1,
		1, 1,
		1, 2);
const Shape Shape::T_UP = Shape(
		ShapeType::T_ID, Direction::UP,
		1, 0,
		0, 1,
		1, 1,
		2, 1);
const Shape Shape::T_RIGHT = Shape(
		ShapeType::T_ID, Direction::RIGHT,
		1, 0,
		1, 1,
		2, 1,
		1, 2);
const Shape Shape::T_DOWN = Shape(
		ShapeType::T_ID, Direction::DOWN,
		0, 1,
		1, 1,
		1, 2,
		2, 1);
const Shape Shape::O_LEFT = Shape(
		ShapeType::O_ID, Direction::LEFT,
		1, 0,
		1, 1,
		2, 0,
		2, 1);
const Shape Shape::O_UP = Shape(
		ShapeType::O_ID, Direction::UP,
		1, 0,
		1, 1,
		2, 0,
		2, 1);
const Shape Shape::O_RIGHT = Shape(
		ShapeType::O_ID, Direction::RIGHT,
		1, 0,
		1, 1,
		2, 0,
		2, 1);
const Shape Shape::O_DOWN = Shape(
		ShapeType::O_ID, Direction::DOWN,
		1, 0,
		1, 1,
		2, 0,
		2, 1);
const Shape Shape::I_LEFT = Shape(
		ShapeType::I_ID, Direction::LEFT,
		1, 0,
		1, 1,
		1, 2,
		1, 3);
const Shape Shape::I_UP = Shape(
		ShapeType::I_ID, Direction::UP,
		0, 1,
		1, 1,
		2, 1,
		3, 1);
const Shape Shape::I_RIGHT = Shape(
		ShapeType::I_ID, Direction::RIGHT,
		2, 0,
		2, 1,
		2, 2,
		2, 3);
const Shape Shape::I_DOWN = Shape(
		ShapeType::I_ID, Direction::DOWN,
		0, 2,
		1, 2,
		2, 2,
		3, 2);
