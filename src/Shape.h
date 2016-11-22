/*
 * Shape.h
 *
 *  Created on: Nov 21, 2016
 *      Author: robin
 */

#ifndef SRC_SHAPE_H_
#define SRC_SHAPE_H_

#include <Arduboy.h>

#undef WIDTH
#undef HEIGHT

class Shape {
public:
	static const int WIDTH = 4;
	static const int HEIGHT = 4;

	static const Shape L_LEFT;
	static const Shape L_UP;
	static const Shape L_RIGHT;
	static const Shape L_DOWN;
	static const Shape J_LEFT;
	static const Shape J_UP;
	static const Shape J_RIGHT;
	static const Shape J_DOWN;
	static const Shape S_LEFT;
	static const Shape S_UP;
	static const Shape S_RIGHT;
	static const Shape S_DOWN;
	static const Shape Z_LEFT;
	static const Shape Z_UP;
	static const Shape Z_RIGHT;
	static const Shape Z_DOWN;
	static const Shape T_LEFT;
	static const Shape T_UP;
	static const Shape T_RIGHT;
	static const Shape T_DOWN;
	static const Shape O_LEFT;
	static const Shape O_UP;
	static const Shape O_RIGHT;
	static const Shape O_DOWN;
	static const Shape I_LEFT;
	static const Shape I_UP;
	static const Shape I_RIGHT;
	static const Shape I_DOWN;

	Shape(
			uint8_t id,
			uint8_t x1, uint8_t y1,
			uint8_t x2, uint8_t y2,
			uint8_t x3, uint8_t y3,
			uint8_t x4, uint8_t y4);
	virtual ~Shape();

	uint8_t get_id() const;

	uint8_t get_block(uint8_t x, uint8_t y, uint8_t block) const;

	const Shape *rotate_right() const;
	const Shape *rotate_left() const;

private:
	uint8_t id;
	uint8_t x1, x2, x3, x4;
	uint8_t y1, y2, y3, y4;
	uint8_t b1, b2, b3, b4;
};

#endif /* SRC_SHAPE_H_ */
