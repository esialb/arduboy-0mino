/*
 * ShapeType.h
 *
 *  Created on: Nov 21, 2016
 *      Author: robin
 */

#ifndef SRC_SHAPETYPE_H_
#define SRC_SHAPETYPE_H_

#include "Shape.h"

class ShapeType {
public:
	static const uint8_t L_ID = 1;
	static const uint8_t J_ID = 2;
	static const uint8_t S_ID = 3;
	static const uint8_t Z_ID = 4;
	static const uint8_t T_ID = 5;
	static const uint8_t O_ID = 6;
	static const uint8_t I_ID = 7;

	static const ShapeType L;
	static const ShapeType J;
	static const ShapeType S;
	static const ShapeType Z;
	static const ShapeType T;
	static const ShapeType O;
	static const ShapeType I;

	ShapeType(uint8_t id, const Shape *left, const Shape *up, const Shape *right, const Shape *down);
	virtual ~ShapeType();

	static const ShapeType *for_id(uint8_t id);

	const Shape *get_left() const;
	const Shape *get_up() const;
	const Shape *get_right() const;
	const Shape *get_down() const;

	const Shape *rotate_left(const Shape *shape) const;
	const Shape *rotate_right(const Shape *shape) const;

private:
	uint8_t id;
	const Shape *left;
	const Shape *up;
	const Shape *right;
	const Shape *down;
};

#endif /* SRC_SHAPETYPE_H_ */
