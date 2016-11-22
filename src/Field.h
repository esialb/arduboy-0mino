/*
 * Field.h
 *
 *  Created on: Nov 21, 2016
 *      Author: robin
 */

#ifndef SRC_FIELD_H_
#define SRC_FIELD_H_

#include <Arduboy.h>
#include "Shape.h"

#undef WIDTH
#undef HEIGHT

class Field {
public:
	static const int WIDTH = 10;
	static const int HEIGHT = 20;

	Field();
	virtual ~Field();

	void reset();

	void draw(Arduboy &arduboy) const;

	uint8_t get_block(int x, int y) const;
	void set_block(int x, int y, uint8_t block);
	void or_block(int x, int y, uint8_t block);
	void and_block(int x, int y, uint8_t block);

	const Shape *get_shape() const;
	void set_shape(const Shape *shape);

	int get_shape_x() const;
	int get_shape_y() const;
	void set_shape_x(int shape_x);
	void set_shape_y(int shape_y);

	void blit_shape();

private:
	uint8_t blocks[WIDTH * HEIGHT];
	const Shape *shape;
	int shape_x;
	int shape_y;
};

#endif /* SRC_FIELD_H_ */
