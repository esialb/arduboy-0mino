/*
 * KickTable.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: robin
 */

#include <KickTable.h>

#include "Direction.h"
#include "ShapeType.h"

KickTable::KickTable(
		int x1, int y1,
		int x2, int y2,
		int x3, int y3,
		int x4, int y4
) {
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->x4 = x4;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->y4 = y4;
}

KickTable::~KickTable() {
	// TODO Auto-generated destructor stub
}

int KickTable::kick_x_right(const Shape *shape, int test) {
	int dir = shape->get_dir();
	if(dir == Direction::UP)
		return (shape->get_id() == ShapeType::I_ID) ? I_UR.get_kick_x(test) : JLSTZO_UR.get_kick_x(test);
	if(dir == Direction::RIGHT)
		return (shape->get_id() == ShapeType::I_ID) ? I_RD.get_kick_x(test) : JLSTZO_RD.get_kick_x(test);
	if(dir == Direction::DOWN)
		return (shape->get_id() == ShapeType::I_ID) ? I_DL.get_kick_x(test) : JLSTZO_DL.get_kick_x(test);
	if(dir == Direction::LEFT)
		return (shape->get_id() == ShapeType::I_ID) ? I_LU.get_kick_x(test) : JLSTZO_LU.get_kick_x(test);
	return 0;
}
int KickTable::kick_x_left(const Shape *shape, int test) {
	int dir = shape->get_dir();
	if(dir == Direction::UP)
		return (shape->get_id() == ShapeType::I_ID) ? I_UL.get_kick_x(test) : JLSTZO_UL.get_kick_x(test);
	if(dir == Direction::RIGHT)
		return (shape->get_id() == ShapeType::I_ID) ? I_RU.get_kick_x(test) : JLSTZO_RU.get_kick_x(test);
	if(dir == Direction::DOWN)
		return (shape->get_id() == ShapeType::I_ID) ? I_DR.get_kick_x(test) : JLSTZO_DR.get_kick_x(test);
	if(dir == Direction::LEFT)
		return (shape->get_id() == ShapeType::I_ID) ? I_LD.get_kick_x(test) : JLSTZO_LD.get_kick_x(test);
	return 0;
}
int KickTable::kick_y_right(const Shape *shape, int test) {
	int dir = shape->get_dir();
	if(dir == Direction::UP)
		return (shape->get_id() == ShapeType::I_ID) ? I_UR.get_kick_y(test) : JLSTZO_UR.get_kick_y(test);
	if(dir == Direction::RIGHT)
		return (shape->get_id() == ShapeType::I_ID) ? I_RD.get_kick_y(test) : JLSTZO_RD.get_kick_y(test);
	if(dir == Direction::DOWN)
		return (shape->get_id() == ShapeType::I_ID) ? I_DL.get_kick_y(test) : JLSTZO_DL.get_kick_y(test);
	if(dir == Direction::LEFT)
		return (shape->get_id() == ShapeType::I_ID) ? I_LU.get_kick_y(test) : JLSTZO_LU.get_kick_y(test);
	return 0;
}
int KickTable::kick_y_left(const Shape *shape, int test) {
	int dir = shape->get_dir();
	if(dir == Direction::UP)
		return (shape->get_id() == ShapeType::I_ID) ? I_UL.get_kick_y(test) : JLSTZO_UL.get_kick_y(test);
	if(dir == Direction::RIGHT)
		return (shape->get_id() == ShapeType::I_ID) ? I_RU.get_kick_y(test) : JLSTZO_RU.get_kick_y(test);
	if(dir == Direction::DOWN)
		return (shape->get_id() == ShapeType::I_ID) ? I_DR.get_kick_y(test) : JLSTZO_DR.get_kick_y(test);
	if(dir == Direction::LEFT)
		return (shape->get_id() == ShapeType::I_ID) ? I_LD.get_kick_y(test) : JLSTZO_LD.get_kick_y(test);
	return 0;
}


int KickTable::get_kick_x(int test) const {
	if(test == 0)
		return 0;
	if(test == 1)
		return x1;
	if(test == 2)
		return x2;
	if(test == 3)
		return x3;
	if(test == 4)
		return x4;
	return 0;
}
int KickTable::get_kick_y(int test) const {
	if(test == 0)
		return 0;
	if(test == 1)
		return y1;
	if(test == 2)
		return y2;
	if(test == 3)
		return y3;
	if(test == 4)
		return y4;
	return 0;
}

const KickTable KickTable::JLSTZO_UR(-1,0, -1,1, 0,-2, -1,-2);
const KickTable KickTable::JLSTZO_RU(1,0, 1,-1, 0,2, 1,2);
const KickTable KickTable::JLSTZO_RD(1,0, 1,-1, 0,2, 1,2);
const KickTable KickTable::JLSTZO_DR(-1,0, -1,1, 0,-2, -1,-2);
const KickTable KickTable::JLSTZO_DL(1,0, 1,1, 0,-2, 1,-2);
const KickTable KickTable::JLSTZO_LD(-1,0, -1,-1, 0,2, -1,2);
const KickTable KickTable::JLSTZO_LU(-1,0, -1,-1, 0,2, -1,2);
const KickTable KickTable::JLSTZO_UL(1,0, 1,1, 0,-2, 1,-2);


const KickTable KickTable::I_UR(-2,0, 1,0, -2,-1, 1,2);
const KickTable KickTable::I_RU(2,0, -1,0, 2,1, -1,-2);
const KickTable KickTable::I_RD(-1,0, 2,0, -1,2, 2,-1);
const KickTable KickTable::I_DR(1,0, -2,0, 1,-2, -2,1);
const KickTable KickTable::I_DL(2,0, -1,0, 2,1, -1,-2);
const KickTable KickTable::I_LD(-2,0, 1,0, -2,-1, 1,2);
const KickTable KickTable::I_LU(1,0, -2,0, 1,-2, -2,1);
const KickTable KickTable::I_UL(-1,0, 2,0, -1,2, 2,-1);
