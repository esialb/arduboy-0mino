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

	static const int HIDDEN_HEIGHT = 4;

	static const int LEFT_BOUNDARY = 0;
	static const int RIGHT_BOUNDARY = WIDTH - 1;
	static const int UP_BOUNDARY = -HIDDEN_HEIGHT;
	static const int DOWN_BOUNDARY = HEIGHT - 1;

	Field();
	virtual ~Field();

	void reset();

	void draw(Arduboy &arduboy) const;

	uint8_t get_block(int x, int y) const;
	uint8_t get_block_with_shape(int x, int y) const;
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

	bool can_shift(int x, int y) const;
	void shift(int x, int y);
	bool can_shape(const Shape *shape) const;
	bool can_rotate_right() const;
	void rotate_left();
	bool can_rotate_left() const;
	void rotate_right();

private:
	uint8_t blocks[WIDTH * (HEIGHT + HIDDEN_HEIGHT)];
	const Shape *shape;
	int shape_x;
	int shape_y;
	int ghost_y;

	void update_ghost_y();
};

#endif /* SRC_FIELD_H_ */
