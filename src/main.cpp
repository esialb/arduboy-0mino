/*
 * main.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: robin
 */


#include <Arduboy.h>

int SCREEN_WIDTH = WIDTH;
int SCREEN_HEIGHT = HEIGHT;

#include "Field.h"
#include "Shape.h"
#include "ShapeType.h"
#include "Engine.h"

Arduboy arduboy;
Field field;
Engine engine;

void setup() {
	arduboy.beginNoLogo();
	field.set_shape(0);
	arduboy.clear();
	arduboy.display();
	int seed = EEPROM.read(0);
	randomSeed(seed);
	seed = random() ^ random();
	EEPROM.write(0, seed);
}

void loop() {
	if(!arduboy.nextFrame())
		return;

	bool draw = engine.tick(field, arduboy);

	if(draw) {
		arduboy.clear();
		arduboy.drawRect(33, 1, 28, 28, WHITE);
		arduboy.fillRect(34, 2, 26, 26, BLACK);

		const Shape *nextShape = ShapeType::for_id(engine.get_next_id())->get_up();
		int nid = nextShape->get_id();
		int ox = (nid == ShapeType::I_ID || nid == ShapeType::O_ID) ? 0 : 3;
		int oy = (nid == ShapeType::I_ID) ? 3 : 6;
		for(int x = 0; x < Shape::WIDTH; x++) {
			for(int y = 0; y < Shape::HEIGHT; y++) {
				uint8_t block = nextShape->get_block(x, y, 0);
				if(block)
					arduboy.fillRect(ox + 35 + x * 6, oy + 3 + y * 6, 6, 6, WHITE);
			}
		}

		char buf[10];
		itoa(engine.get_lines(), buf, 10);
		for(int i = 0; i < sizeof(buf) && buf[i]; i++)
			arduboy.drawChar(33 + i * 6, 30, buf[i], WHITE, BLACK, 1);

		arduboy.drawChar(62, 1, '0', WHITE, BLACK, 2);
		arduboy.drawChar(74, 1, 'm', WHITE, BLACK, 2);
		arduboy.drawChar(86, 1, 'i', WHITE, BLACK, 2);
		arduboy.drawChar(98, 1, 'n', WHITE, BLACK, 2);
		arduboy.drawChar(110, 1, 'o', WHITE, BLACK, 2);

		field.draw(arduboy);
		arduboy.display();
	}
}
