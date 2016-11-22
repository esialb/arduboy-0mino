/*
 * Engine.h
 *
 *  Created on: Nov 22, 2016
 *      Author: robin
 */

#ifndef SRC_ENGINE_H_
#define SRC_ENGINE_H_

#include <Arduboy.h>
#include "Field.h"

class Engine {
public:
	static const int AUTOSHIFT_FRAMES = 20;

	Engine();
	virtual ~Engine();

	void tick(Field &field, Arduboy &arduboy);

	int get_lines() const;
	int get_next_id() const;

private:
	uint8_t bag = 0;
	bool autoshifting = false;
	int shift_held_frames = 0;
	bool rotating = false;
	int drop_held_frames = 0;
	int lines = 0;
	int next_id = 0;
};

#endif /* SRC_ENGINE_H_ */
