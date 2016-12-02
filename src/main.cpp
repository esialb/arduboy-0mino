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
		arduboy.fillRect(0, 0, 128, 64, WHITE);

		arduboy.drawChar(62, 1, '0', BLACK, WHITE, 2);
		arduboy.drawChar(74, 1, 'm', BLACK, WHITE, 2);
		arduboy.drawChar(86, 1, 'i', BLACK, WHITE, 2);
		arduboy.drawChar(98, 1, 'n', BLACK, WHITE, 2);
		arduboy.drawChar(110, 1, 'o', BLACK, WHITE, 2);

		const Shape *nextShape = ShapeType::for_id(engine.get_next_id())->get_up();
		int nid = nextShape->get_id();
		int swidth = nextShape->get_maxx() - nextShape->get_minx() + 1;
		int sheight = nextShape->get_maxy() - nextShape->get_miny() + 1;
		int ox = 3 * (4 - swidth) - 6 * nextShape->get_minx();
		int oy = 3 * (4 - sheight) - 6 * nextShape->get_miny();
		arduboy.fillRect(35, 1, 26, 26, BLACK);
		for(int x = nextShape->get_minx(); x <= nextShape->get_maxx(); x++) {
			for(int y = nextShape->get_miny(); y <= nextShape->get_maxy(); y++) {
				uint8_t block = nextShape->get_block(x, y, 0);
				uint8_t color = (block ? WHITE : BLACK);
				arduboy.fillRect(ox + 36 + x * 6, oy + 2 + y * 6, 6, 6, color);
			}
		}

		Graphics::draw_int(&arduboy, 35, 28, engine.get_lines(), BLACK);
		Graphics::draw_int(&arduboy, 62, 16, engine.get_score(), BLACK);


		field.draw(arduboy);
		arduboy.display();
	}
}
