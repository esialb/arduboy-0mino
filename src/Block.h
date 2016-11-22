/*
 * Block.h
 *
 *  Created on: Nov 21, 2016
 *      Author: robin
 */

#ifndef SRC_BLOCK_H_
#define SRC_BLOCK_H_

#include <Arduboy.h>

class Block {
public:
	static const uint8_t LEFT = 0x80;
	static const uint8_t UP = 0x40;
	static const uint8_t RIGHT = 0x20;
	static const uint8_t DOWN = 0x10;
	static const uint8_t FILLED = 0x08;
	static const uint8_t SHAPE = 0x07;
};

#endif /* SRC_BLOCK_H_ */
