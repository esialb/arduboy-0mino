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

#include "Graphics.h"

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
		arduboy.drawChar(62, 1, '0', WHITE, BLACK, 2);
		arduboy.drawChar(74, 1, 'm', WHITE, BLACK, 2);
		arduboy.drawChar(86, 1, 'i', WHITE, BLACK, 2);
		arduboy.drawChar(98, 1, 'n', WHITE, BLACK, 2);
		arduboy.drawChar(110, 1, 'o', WHITE, BLACK, 2);

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

		arduboy.fillRect(33, 30, 64, 6, BLACK);
		Graphics::draw_int(&arduboy, 33, 30, engine.get_lines(), WHITE);
		arduboy.fillRect(62, 16, 64, 6, BLACK);
		Graphics::draw_int(&arduboy, 62, 16, engine.get_score(), WHITE);


		field.draw(arduboy);
		arduboy.display();
	}
}
