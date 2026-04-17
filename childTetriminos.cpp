#include "childTetriminos.h"

	LShape::LShape(int n) {
		setNum(n);  // sets the colour
		cell[0] = { orientation(0,2), orientation(1,0), orientation(1,1), orientation(1,2)};
		cell[1] = { orientation(0,1), orientation(1,1), orientation(2,1), orientation(2,2) };
		cell[2] = { orientation(1,0), orientation(1,1), orientation(1,2), orientation(2,0) };
		cell[3] = { orientation(0,0), orientation(0,1), orientation(1,1), orientation(2,1) };
		move(0, 3);  //centralizes the block
	}

	JShape::JShape(int n ) {
		setNum(n);
		cell[0] = { orientation(0,0), orientation(1,0), orientation(1,1), orientation(1,2) };
		cell[1] = { orientation(0,1), orientation(0,2), orientation(1,1), orientation(2,1) };
		cell[2] = { orientation(1,0), orientation(1,1), orientation(1,2), orientation(2,2) };
		cell[3] = { orientation(0,1), orientation(1,1), orientation(2,0), orientation(2,1) };
		move(0, 3);
	}

	IShape::IShape(int n ) {
		setNum(n);
		cell[0] = { orientation(1,0), orientation(1,1), orientation(1,2), orientation(1,3) };
		cell[1] = { orientation(0,2), orientation(1,2), orientation(2,2), orientation(3,2) };
		cell[2] = { orientation(2,0), orientation(2,1), orientation(2,2), orientation(2,3) };
		cell[3] = { orientation(0,1), orientation(1,1), orientation(2,1), orientation(3,1) };
		move(-1, 3);
	}

	OShape::OShape(int n ) {
		setNum(n);
		cell[0] = { orientation(0,0), orientation(0,1), orientation(1,0), orientation(1,1) };
		/*cell[1] = { orientation(0,0), orientation(0,1), orientation(1,0), orientation(1,1) };
		cell[2] = { orientation(0,0), orientation(0,1), orientation(1,0), orientation(1,1) };
		cell[3] = { orientation(0,0), orientation(0,1), orientation(1,0), orientation(1,1) };*/
		move(0, 4);
	}
	void OShape::rotate() {
		rotation = 0;
	}

	SShape::SShape(int n ) {
		setNum(n);
		cell[0] = { orientation(0,1), orientation(0,2), orientation(1,0), orientation(1,1) };
		cell[1] = { orientation(0,1), orientation(1,1), orientation(1,2), orientation(2,2) };
		cell[2] = { orientation(1,1), orientation(1,2), orientation(2,0), orientation(2,1) };
		cell[3] = { orientation(0,0), orientation(1,0), orientation(1,1), orientation(2,1) };
		move(0, 3);

	}

	TShape::TShape(int n ) {
		setNum(n);
		cell[0] = { orientation(0,1), orientation(1,0), orientation(1,1), orientation(1,2) };
		cell[1] = { orientation(0,1), orientation(1,1), orientation(1,2), orientation(2,1) };
		cell[2] = { orientation(1,0), orientation(1,1), orientation(1,2), orientation(2,1) };
		cell[3] = { orientation(0,1), orientation(1,0), orientation(1,1), orientation(2,1) };
		move(0, 3);

	}

	ZShape::ZShape(int n ) {
		setNum(n);
		cell[0] = { orientation(0,0), orientation(0,1), orientation(1,1), orientation(1,2) };
		cell[1] = { orientation(0,2), orientation(1,1), orientation(1,2), orientation(2,1) };
		cell[2] = { orientation(1,0), orientation(1,1), orientation(2,1), orientation(2,2) };
		cell[3] = { orientation(0,1), orientation(1,0), orientation(1,1), orientation(2,0) };
		move(0, 3);
	}

