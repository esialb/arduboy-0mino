/*
 * KickTable.h
 *
 *  Created on: Nov 22, 2016
 *      Author: robin
 */

#ifndef SRC_KICKTABLE_H_
#define SRC_KICKTABLE_H_

#include "Shape.h"

class KickTable {
public:
	static const int TESTS = 5;

	static const KickTable JLSTZO_UR;
	static const KickTable JLSTZO_RD;
	static const KickTable JLSTZO_DL;
	static const KickTable JLSTZO_LU;
	static const KickTable JLSTZO_UL;
	static const KickTable JLSTZO_LD;
	static const KickTable JLSTZO_DR;
	static const KickTable JLSTZO_RU;


	static const KickTable I_UR;
	static const KickTable I_RD;
	static const KickTable I_DL;
	static const KickTable I_LU;
	static const KickTable I_UL;
	static const KickTable I_LD;
	static const KickTable I_DR;
	static const KickTable I_RU;

	static int kick_x_right(const Shape *shape, int test);
	static int kick_x_left(const Shape *shape, int test);
	static int kick_y_right(const Shape *shape, int test);
	static int kick_y_left(const Shape *shape, int test);

	KickTable(
			int x1, int y1,
			int x2, int y2,
			int x3, int y3,
			int x4, int y4
			);
	virtual ~KickTable();

	int get_kick_x(int test) const;
	int get_kick_y(int test) const;
private:
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
};

#endif /* SRC_KICKTABLE_H_ */
