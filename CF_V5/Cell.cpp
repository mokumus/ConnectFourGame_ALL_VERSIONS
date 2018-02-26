//There are no new functions in this source file.

#include "Cell.h"

using namespace cfa;
using std::cerr;
using std::endl;
using std::ostream;


Cell::Cell(int tV, int i1V, int i2V,int moveNoV, bool bTV):type(tV),i1(i1V),i2(i2V),moveNo(moveNoV),botCell(bTV){}

//SETTERS
void Cell::setBotCell(bool btVal){botCell = btVal;}

void Cell::setMoveNo(int moveNoVal){moveNo = moveNoVal;}

void Cell::setType(int typeVal){type = typeVal;}

void Cell::setCell(int typeVal, int i1Val, int i2Val,int moveNoV, bool btVal){
	type = typeVal;
	i1 = i1Val;
	i2 = i2Val;
	moveNo = moveNoV;
	botCell = btVal;
}

//GETTERS...
int Cell::getType() const{return type;}

int Cell::getRow() const{return i1;}

int Cell::getCol() const{return i2;}

int Cell::getMoveNo() const{return moveNo;}

char Cell::getColAsChar() const{return ('A' + i2);}

bool Cell::isBotCell() const{return botCell;}

string Cell::getTypeAsString() const{
	switch (type) {
		case -1:
			return "No Access";
		case 0:
			return "Empty";
		case 1:
			return "User 1";
		case 2:
			return "User 2";
		case 3:
			return "Computer";
		default:
			cerr << "Invalid type(getTypeAsString): " << type << "was entered." << endl;
			exit(1);
	}
}

