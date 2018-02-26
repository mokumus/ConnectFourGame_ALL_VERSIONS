#ifndef ConnectFour_h
#define ConnectFour_h
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;



class ConnectFour{
	class Cell;
public:
	
	//CONSTRUCTORS - DESTRUCTOR...
	ConnectFour();
	ConnectFour(int i1,int i2);
	ConnectFour(const string filename);
	ConnectFour(const ConnectFour&);
	~ConnectFour();
	
	//GETTERS...
	int getHeigh() const{return height;};
	int getWidth() const{return width;};
	
	//TESTER...
	bool testSize(int heightV, int widthV); //Returns true if size is in bounds
	static void testCellClass(); //Tests cell class operators to see if they are working properly
	
	//PRINTERS - OSTREAM OPT...
	void print() const;
	friend ostream& operator <<(ostream&,const ConnectFour&); //This was not needed but it's another option
	
	//OPERATORS
	const Cell& operator ()(int i, int j) const;//Used to access the indexes, also checks range in case of bad acess.
	Cell& operator ()(int i, int j);
	ConnectFour& operator=(const ConnectFour&);// USED IN LOAD GAME, VERY USEFUL!!!
	bool operator ==(const ConnectFour&) const;
	bool operator !=(const ConnectFour&) const;
	
	//GAME MANAGERS
	static void playGame(); //Manages play(user) and play(comp) functions
	static void playMulti(); //Manages multiple object games.

	
private:

	
	Cell **gameBoard;
	int height;
	int width;
	
	//BOARD INITILIZER
	void init();//Initilizes cell indexes and top cell values.
	
	//GAME OVER CONDITION FUNCTIONS
	bool horizantalWin(int userRef, int winningFour[][2]);
	bool verticalWin(int userRef, int winningFour[][2]);
	bool diagonalWin(int userRef, int winningFour[][2]);
	bool isWon(int userRef);
	bool isBoardFull() const;
	bool isGameOver(int userRef);
	void printConnected(int arr[][2]);
	
	//PLAY FUNCTIONS
	int play(char move,int &user);//plays user for single time step
	void play(); // plays computer
	
	//SAVE AND LOAD FUNCTIONS
	void save(string filename, int userRef, char gameType) const;
	void load(string filename, int &userRef, char &gameType);
	
	class Cell{
	public:
		//CONSTRUCTOR...
		Cell(int tV = 0, int i1V = -1, int i2V = -1, bool bTV = false):type(tV),i1(i1V),i2(i2V),botCell(bTV){};
		
		//SETTERS...
		void setCell(int typeVal, int i1Val, int i2Val, bool btVal = false);
		void setBotCell(bool btVal){botCell = btVal;};
		
		//GETTERS...
		int getType() const{return type;};
		int getRow() const{return i1;};
		int getCol() const{return i2;};
		char getColAsChar() const{return ('A' + i2);};
		
		bool isBotCell() const{return botCell;};
		string getTypeAsString() const;
		
		//OPERARTORS...
		bool operator ==(const Cell&) const;	//Return true if Cell.type's are the same.
		bool operator !=(const Cell&) const;
		Cell& operator ++();					// empty>>user1>>user2>>computer>>empty
		Cell operator ++(int);
		Cell& operator --();					// empty>>computer>>user2>>user1>>empty
		Cell operator --(int);
		friend ostream& operator <<(ostream& outs, const Cell& cell){
			outs << "Type: " << cell.getTypeAsString() << ", [" << cell.getRow() << "," << cell.getCol();
			outs << "], Column:"  << cell.getColAsChar() << " ,isPlayable: " << boolalpha <<cell.isBotCell();
			return outs;
		}
		friend istream& operator >>(istream& inps, Cell& cell){
			inps >> cell.type;
			inps >> cell.i1;
			inps >> cell.i2;
			inps >> cell.botCell;
			return inps;
		};
		
	private:
		int type; //empty = 0, user1 = 1, user2 = 2, computer = 3
		int i1;//index 1, row
		int i2;//index 2, col
		bool botCell; //true if the first playable cell from the bottom.
	};
};


inline const ConnectFour::Cell& ConnectFour::operator ()(int i, int j) const{
	if(i < 0 || j < 0 || i >= height || j >= width){
		cerr << endl <<"Bad Acess. operator() , i: " << i << ", j: " << j << endl;
		cerr << "height: " << height << "width: " << width << endl;
		exit(1);
	}
	
	return gameBoard[i][j];
}

inline ConnectFour::Cell& ConnectFour::operator ()(int i, int j){
	if(i < 0 || j < 0 || i >= height || j >= width){
		cerr << endl <<"Bad Acess. operator() , i: " << i << ", j: " << j << endl;
		cerr << "height: " << height << "width: " << width << endl;
		exit(1);
	}
	
	return gameBoard[i][j];
}

#endif /* ConnectFour_h */
