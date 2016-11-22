/*
 * ShapeType.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: robin
 */

#include <ShapeType.h>

#include "Shape.h"

ShapeType::ShapeType(uint8_t id, const Shape *left, const Shape *up, const Shape *right, const Shape *down) {
	this->id = id;
	this->left = left;
	this->up = up;
	this->right = right;
	this->down = down;
}

ShapeType::~ShapeType() {
	// TODO Auto-generated destructor stub
}

const ShapeType *ShapeType::for_id(uint8_t id) {
	if(id == L_ID)
		return &L;
	if(id == J_ID)
		return &J;
	if(id == S_ID)
		return &S;
	if(id == Z_ID)
		return &Z;
	if(id == T_ID)
		return &T;
	if(id == O_ID)
		return &O;
	if(id == Z_ID)
		return &Z;
	return 0;
}

const ShapeType ShapeType::L = ShapeType(L_ID, &Shape::L_LEFT, &Shape::L_UP, &Shape::L_RIGHT, &Shape::L_DOWN);
const ShapeType ShapeType::J = ShapeType(J_ID, &Shape::J_LEFT, &Shape::J_UP, &Shape::J_RIGHT, &Shape::J_DOWN);
const ShapeType ShapeType::S = ShapeType(L_ID, &Shape::S_LEFT, &Shape::S_UP, &Shape::S_RIGHT, &Shape::S_DOWN);
const ShapeType ShapeType::Z = ShapeType(L_ID, &Shape::Z_LEFT, &Shape::Z_UP, &Shape::Z_RIGHT, &Shape::Z_DOWN);
const ShapeType ShapeType::T = ShapeType(L_ID, &Shape::T_LEFT, &Shape::T_UP, &Shape::T_RIGHT, &Shape::T_DOWN);
const ShapeType ShapeType::O = ShapeType(L_ID, &Shape::O_LEFT, &Shape::O_UP, &Shape::O_RIGHT, &Shape::O_DOWN);
const ShapeType ShapeType::I = ShapeType(L_ID, &Shape::I_LEFT, &Shape::I_UP, &Shape::I_RIGHT, &Shape::I_DOWN);

const Shape *ShapeType::get_left() const {
	return left;
}
const Shape *ShapeType::get_up() const {
	return up;
}
const Shape *ShapeType::get_right() const {
	return right;
}
const Shape *ShapeType::get_down() const {
	return down;
}

const Shape *ShapeType::rotate_left(const Shape *shape) const {
	if(shape == left)
		return down;
	if(shape == down)
		return right;
	if(shape == right)
		return up;
	if(shape == up)
		return left;
	return 0;
}
const Shape *ShapeType::rotate_right(const Shape *shape) const {
	if(shape == left)
		return up;
	if(shape == up)
		return right;
	if(shape == right)
		return down;
	if(shape == down)
		return left;
	return 0;
}
