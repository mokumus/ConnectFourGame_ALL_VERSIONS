#ifndef ConnectFourAbstract_h
#define ConnectFourAbstract_h
#include <stddef.h>
#include "Cell.h"
using std::ostream;
using std::string;

namespace cfa{
	class ConnectFourAbstract{
	public:
		//CONSTRUCTORS - DESTRUCTOR...
		ConnectFourAbstract();
		ConnectFourAbstract(int i1,int i2);
		ConnectFourAbstract(const ConnectFourAbstract&);
		virtual ~ConnectFourAbstract();
		
		//GETTERS...
		int getHeight() const;
		int getWidth() const;
		
		//TESTER...
		bool testSize(int heightV, int widthV); //Returns true if size is in bounds
		
		//PRINTER
		void print() const;
		
		//OPERATORS
		const Cell& operator ()(int i, int j) const;//Used to access the indexes, also checks range in case of bad acess.
		Cell& operator ()(int i, int j);
		ConnectFourAbstract& operator=(const ConnectFourAbstract&);// USED IN LOAD GAME
		
		//GAME MANAGERS
		virtual void playGame(); //Manages play(user) and play(comp) functions
		
	protected:
		Cell **gameBoard;
		int height;
		int width;
		static int movesMade; //Total number of moves made during the game
		
		//PLAY FUNCTIONS
		int play(char move,int &user);//plays user for single time step
		void play(); // plays computer
		
		//BOARD INITILIZER
		void init();//Initilizes cell indexes and top cell values.
		
		//GAME OVER CONDITION FUNCTIONS
		virtual bool isWon(int userRef);
		bool horizantalWin(int userRef, int winningFour[][2]);
		bool verticalWin(int userRef, int winningFour[][2]);
		bool diagonalWin(int userRef, int winningFour[][2]);
		bool isBoardFull() const;
		bool isGameOver(int userRef);
		void printConnected(int arr[][2]);
		
		//SAVE AND LOAD FUNCTIONS
		void save(string filename, int userRef, char gameType) const;
		void load(string filename, int &userRef, char &gameType);

		//MISC
		int findLastPlayed();	//returns the how many moves made
	};
}
#endif /* ConnectFourAbstract_h */
