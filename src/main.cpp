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
	arduboy.fillRect(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, BLACK);
	arduboy.drawRect(33, 1, 28, 28, WHITE);
	arduboy.display();
}

void loop() {
	if(!arduboy.nextFrame())
		return;

	engine.tick(field, arduboy);

	const Shape *nextShape = ShapeType::for_id(engine.get_next_id())->get_up();
	for(int x = 0; x < Shape::WIDTH; x++) {
		for(int y = 0; y < Shape::HEIGHT; y++) {
			uint8_t block = nextShape->get_block(x, y, 0);
			arduboy.fillRect(35 + x * 6, 3 + y * 6, 6, 6, block ? WHITE : BLACK);
		}
	}

	char buf[10];
	itoa(engine.get_lines(), buf, 10);
	for(int i = 0; i < sizeof(buf) && buf[i]; i++)
		arduboy.drawChar(33 + i * 6, 30, buf[i], WHITE, BLACK, 1);

	field.draw(arduboy);
	arduboy.display();
}
