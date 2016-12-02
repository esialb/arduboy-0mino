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
	static const uint8_t LEFT = 0x8;
	static const uint8_t UP = 0x4;
	static const uint8_t RIGHT = 0x2;
	static const uint8_t DOWN = 0x1;
};

#endif /* SRC_BLOCK_H_ */
