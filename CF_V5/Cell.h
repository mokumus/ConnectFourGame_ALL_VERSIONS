#ifndef Cell_h
#define Cell_h
#include<iostream>
using std::ostream;
using std::string;

namespace cfa{
	class Cell{
	public:
		//CONSTRUCTOR...
		Cell(int tV = 0, int i1V = -1, int i2V = -1,int moveNoV = -1, bool bTV = false);
		
		//SETTER...
		void setCell(int typeVal, int i1Val, int i2Val,int moveNoV, bool btVal = false);
		void setBotCell(bool btVal);
		void setMoveNo(int moveNoVal);
		void setType(int typeVal);
		
		//GETTERS...
		int getType() const;
		int getRow() const;
		int getCol() const;
		int getMoveNo() const;
		char getColAsChar() const;
	
		bool isBotCell() const;
		string getTypeAsString() const;
		
		//OSTREAM(For debugging)...
		friend ostream& operator <<(ostream& outs, const Cell& cell){
			outs << "Type: " << cell.getTypeAsString() << ", [" << cell.getRow() << "," << cell.getCol();
			outs << "], Column:"  << cell.getColAsChar() << " ,isPlayable: " << std::boolalpha <<cell.isBotCell();
			return outs;
		}
		
	private:
		int type;		//empty = 0, user1 = 1, user2 = 2, computer = 3
		int i1;			//index 1, row
		int i2;			//index 2, col
		int moveNo;		//-1 if no move made in the cell, else number of moves made before this cell.
		bool botCell;	//true if the first playable cell from the bottom
	};
}

#endif /* Cell_h */
