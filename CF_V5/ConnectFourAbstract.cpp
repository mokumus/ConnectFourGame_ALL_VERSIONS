#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "ConnectFourAbstract.h"

using namespace cfa;
using std::cerr;
using std::cout;
using std::endl;
using std::cin;
using std::ofstream;
using std::ifstream;

int ConnectFourAbstract::movesMade = 0; //Incremented each time a move is made, decremented when UNDO command is succesful

int ConnectFourAbstract::findLastPlayed(){//Returns the number of moves made
	int i, j;
	int max = 0;
	for(i = 0; i < height; ++i){
		for(j = 0; j < width; ++j){
			if(max < gameBoard[i][j].getMoveNo())
				max = gameBoard[i][j].getMoveNo();
		}
	}
	return max;
}

//VIRTUAL FUNCTIONS(NEW-WILL BE OVERRIDDEN)
bool ConnectFourAbstract::isWon(int userRef){
	int winningFour[4][2];
	
	if(horizantalWin(userRef, winningFour) ||
	   verticalWin(userRef, winningFour)  ||
	   diagonalWin(userRef, winningFour) ){
		if(userRef == 1)
			cout << "Player 1 win!" << endl;
		else if(userRef == 2)
			cout << "Player 2 win!" << endl;
		else if(userRef == 3)
			cout << "Computer win!" << endl;
		else{
			cerr << " Win check error. isWin()" << endl;
		}
		
		return true;
	}
	return false;
}


//UNCHANGED FUCNTIONS FROM HW4
ConnectFourAbstract::~ConnectFourAbstract(){
	//cout << "CALLED IT " << height << "  " << width << endl;
	//Delete each sub-arr
	for(int i = 0; i < height; ++i) {
		delete[] gameBoard[i];
	}
	//Delete the array of pointers
	delete[] gameBoard;
}

ConnectFourAbstract::ConnectFourAbstract():height(5), width(5){
	gameBoard = new Cell*[5];//Make room for rows
	
	for(int i = 0; i < 5; ++i)
		gameBoard[i] = new Cell[5];//Make room for each cell of the row
	
	init(); //Initlize board
}

ConnectFourAbstract::ConnectFourAbstract(int i1V,int i2V):height(i1V), width(i2V){
	gameBoard = new Cell*[i1V];//Make room for rows
	
	for(int i = 0; i < i1V; ++i)
		gameBoard[i] = new Cell[i2V];//Make room for each cell of the row
	
	if(testSize(i1V,i2V) == false){
		cerr << "Invalid size.(Constructor Error)" << endl;
		exit(1);
	}
	init();//Initlize board
}

ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& object){
	gameBoard = new Cell*[object.height];
	for(int i = 0; i < object.height; ++i){
		gameBoard[i] = new Cell[object.height];
		for(int j = 0; j < object.width; ++j)
			gameBoard[i][j] = object.gameBoard[i][j];
	}
}

int ConnectFourAbstract::getHeight() const{return height;}

int ConnectFourAbstract::getWidth() const{return width;}

bool ConnectFourAbstract::testSize(int heightV, int widthV){
	return(!(heightV < 4 || widthV < 4 || widthV > 26));
}

void ConnectFourAbstract::print() const{
	int i;
	char start = 'A';
	
	//Print Column Letters
	for(i = 0; i < width; ++i)
		cout << static_cast<char> (start + i) << " ";
	
	cout << endl;
	
	//Print Cells
	for(i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			switch (gameBoard[i][j].getType()) {
				case 0://Type empty = 0
					cout << "." << " "; break;
				case 1://user1 = 1
					cout << "O" << " "; break;
				case 2://user2 = 2
					cout << "X" << " "; break;
				case 3://computer = 3
					cout << "C" << " "; break;
				case -1://Not acessable = -1
					cout << " " << " "; break;
				case 11://winning cell user1
					cout << "o" << " "; break;
				case 22://winning cell user2
					cout << "x" << " "; break;
				case 33://winning cell comp
					cout << "c" << " "; break;
					
				default:
					cerr << "Unknown cell type.(Print error)" << endl;
					exit(1); break;
			}
		}
		cout << endl;
	}
}


ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract &rtSide){// USED IN LOAD GAME, VERY USEFUL!!!
	int i,j;
	if(this == &rtSide)
		return *this;
	else{
		int tempHeight = height;
		
		height = rtSide.height;
		width = rtSide.width;
		
		for(i = 0; i < tempHeight; ++i) {
			delete[] gameBoard[i];
		}
		delete [] gameBoard;
		
		gameBoard = new Cell*[height];
		for(i = 0; i < height; ++i){
			gameBoard[i] = new Cell[width];
			for(j = 0; j < width; ++j)
				gameBoard[i][j] = rtSide.gameBoard[i][j];
		}
		return *this;
	}
}

const Cell& ConnectFourAbstract::operator ()(int i, int j) const{
	if(i < 0 || j < 0 || i >= height || j >= width){
		cerr << endl <<"Bad Acess. operator() , i: " << i << ", j: " << j << endl;
		cerr << "height: " << height << "width: " << width << endl;
		exit(1);
	}
	
	return gameBoard[i][j];
}

Cell& ConnectFourAbstract::operator ()(int i, int j){
	if(i < 0 || j < 0 || i >= height || j >= width){
		cerr << endl <<"Bad Acess. operator() , i: " << i << ", j: " << j << endl;
		cerr << "height: " << height << "width: " << width << endl;
		exit(1);
	}
	
	return gameBoard[i][j];
}

void ConnectFourAbstract::init(){
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			
			// Set lowest cell to bot cell.(Token drops here)
			if(i == height - 1)
				gameBoard[i][j].setCell(0,i,j,-1,true);
			
			else if(gameBoard[i][j].getType() == -1)//Inaccesable cells
				gameBoard[i][j].setCell(-1, i, j, -1);
			
			else if(gameBoard[i][j].getType() == 0)//Playable cells
				gameBoard[i][j].setCell(0, i, j, -1);
			
			else
				cerr << "Initlization error.At: " << gameBoard[i][j] << endl;
			
		}
	}
}

void ConnectFourAbstract::printConnected(int arr[][2]){
	int i;
	for(i = 0; i < 4; ++i){
		cout << "[" << arr[i][0] << "," << arr[i][1] << "] ";
		
		if(gameBoard[arr[i][0]][arr[i][1]].getTypeAsString() == "User 1")
			gameBoard[arr[i][0]][arr[i][1]].setCell(11, arr[i][0], arr[i][1], -2); //11 represents 'o'
		else if(gameBoard[arr[i][0]][arr[i][1]].getTypeAsString() == "User 2")
			gameBoard[arr[i][0]][arr[i][1]].setCell(22, arr[i][0], arr[i][1], -2); //22 represents 'x'
		else if(gameBoard[arr[i][0]][arr[i][1]].getTypeAsString() == "Computer")
			gameBoard[arr[i][0]][arr[i][1]].setCell(33, arr[i][0], arr[i][1], -2); //33 represents 'c'
		else
			cerr << "Winning cells could not be highlighted. printConnected() error." << endl;
	}
	cout << endl;
	
	print();
}

bool ConnectFourAbstract::isGameOver(int userRef){
	return (isWon(userRef) || isBoardFull());
}

bool ConnectFourAbstract::isBoardFull() const{
	for(int i = 0; i <  height; ++i){
		for(int j = 0; j < width; ++j){
			if(gameBoard[i][j].getTypeAsString() == "Empty") //If there is an empty cell, board is not full
				return false;
		}
	}
	cout <<"The board is full. It's a tie." << endl;
	return true;
}

bool ConnectFourAbstract::horizantalWin(int userRef, int winningFour[][2]){
	int i,j,m;//j = row, i = col
	int connected;
	
	for(j = height - 1; j >= 0; --j){
		connected = 0;
		
		for(i = width - 1, m = 0;
			i >= 0;
			--i, ++m){
			
			if(gameBoard[j][i].getType() == userRef){
				if(i + 1 < width && gameBoard[j][i+1].getType() != userRef) //Set connect to 0 if there is disconnection
					connected = 0;
				
				if(m >= 4)
					m = 0;//If we didn't find a connection reset connection array to find new connections
				
				winningFour[m][0] = j; //Save connected cells
				winningFour[m][1] = i;
				
				connected++;
				
				if(connected >= 4){
					cout << "Horizontal win." << endl;
					printConnected(winningFour);
					return true;
				}
			}
		}
	}
	return false;
}


bool ConnectFourAbstract::verticalWin(int userRef, int winningFour[][2]){
	int i,j,m;//j = col, i = row
	int connected;
	
	
	for(j = width - 1; j >= 0; --j){
		connected = 0;
		
		for(i = height - 1, m = 0;
			i >= 0;
			--i, ++m){
			if(gameBoard[i][j].getType() == userRef){
				if(i + 1 < height && gameBoard[i+1][j].getType() != userRef) //Set connect to 0 if there is disconnection
					connected = 0;
				
				if(m >= 4)
					m = 0;//If we didn't find a connection reset connection array to find new connections
				
				winningFour[m][0] = i;//Save connected cells
				winningFour[m][1] = j;
				
				connected++;
				
				if(connected >= 4){
					cout << "Vertical win." << endl;
					printConnected(winningFour);
					return true;
				}
			}
		}
	}
	return false;
}

bool ConnectFourAbstract::diagonalWin(int userRef, int (*winningFour)[2]){
	int i,j,m;
	
	
	
	//TO TOP LEFT
	for(i = 3; i < height; ++i){//We start from 3 because we ignore 3 by 3 triangle area on bottom.
		for(j = 0; j < width-3; ++j){//also ignore triangle on top
			if(gameBoard[i][j].getType() == userRef &&
			   gameBoard[i-1][j+1].getType() == userRef &&
			   gameBoard[i-2][j+2].getType() == userRef &&
			   gameBoard[i-3][j+3].getType() == userRef){
				
				for(m = 0; m < 4; ++m){//save connected cells
					winningFour[m][0] = i - m;
					winningFour[m][1] = j + m;
				}
				cout << "Diagonal win." << endl;
				printConnected(winningFour);
				return true;
			}
		}
	}
	//TO BOTTOM RIGHT
	for(i = 3; i < height; ++i){
		for(j = 3; j < width; ++j){
			if(gameBoard[i][j].getType() == userRef &&
			   gameBoard[i-1][j-1].getType() == userRef &&
			   gameBoard[i-2][j-2].getType() == userRef &&
			   gameBoard[i-3][j-3].getType() == userRef){
				
				for(m = 0; m < 4; ++m){
					winningFour[m][0] = i - m;
					winningFour[m][1] = j - m;
				}
				cout << "Diagonal win." << endl;
				printConnected(winningFour);
				return true;
			}
		}
	}
	return false;
}

void ConnectFourAbstract::save(string filename, int userRef, char gameType) const{
	ofstream fp;
	
	fp.open(filename);
	
	if(!fp){
		cout << "Cannot save to given file.\nExiting..." << endl;
		cerr << "Invalid file name(Save Error)." << endl;
		exit(1);
	}
	
	fp << userRef << endl;
	fp << gameType << endl;
	fp << height << endl;
	fp << width << endl;
	fp << movesMade << endl;
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			fp << gameBoard[i][j].getType() << " " << gameBoard[i][j].isBotCell() << " ";
			fp << gameBoard[i][j].getMoveNo() << " ";
		}
		fp << endl;
	}
	fp.close();
}

void ConnectFourAbstract::load(string filename, int &userRef, char &gameType){
	ifstream fp;
	int h,w;
	int tempType;
	int tempMoveNo;
	bool isBotCell;

	fp.open(filename);
	
	if(!fp){
		cout << "Cannot load from given file.\nExiting..." << endl;
		cerr << "Invalid file name(Load Error)." << endl;
		exit(1);
	}
	
	fp >> userRef;
	fp >> gameType;
	fp >> h;
	fp >> w;
	fp >> movesMade;
	ConnectFourAbstract tempBoard(h,w);
	
	for(int i = 0; i < h; ++i){
		for(int j = 0; j < w; ++j){
			fp >> tempType;
			fp >> isBotCell;
			fp >> tempMoveNo;
			tempBoard(i,j).setCell(tempType, i, j, tempMoveNo, isBotCell);
		}
	}
	
	*this = tempBoard;
	
	fp.close();
}

int ConnectFourAbstract::play(char move,int &user){
	int moveCol = static_cast<int>(move) - 'A';
	int moveRow;
	
	for(int i = 0; i < height; ++i){
		if(gameBoard[i][moveCol].getTypeAsString() != "No Access"){
			if(gameBoard[i][moveCol].isBotCell() == true){//If the reached cell is playable
				moveRow = i;
				gameBoard[moveRow][moveCol].setCell(user, moveRow, moveCol, movesMade++); //Mark the move
				gameBoard[moveRow][moveCol].setBotCell(false); //Move made here, not playable anymore
				
				if(i > 0 && gameBoard[i-1][moveCol].getTypeAsString() != "No Access")
					gameBoard[i-1][moveCol].setBotCell(true);//Set above cell to new playable
				
				return 1; //Move made succesfully
			}
		}
	}
	cout << "Column is full, try again." << endl;
	
	return 0; //Column is full
}

void ConnectFourAbstract::play(){
	int i, j, k = 0;
	int randomCol = 0;
	
	for(i = 0; i < height - 3; ++i){ //VERTICAL SMART MOVE
		for(j = 0; j < width; ++j){
			if(gameBoard[i][j].getType() == 0 &&   //EMPTY
			   gameBoard[i+1][j].getType() == 1 && //U1
			   gameBoard[i+2][j].getType() == 1){  //U1
				
				if(gameBoard[i][j].isBotCell() == true){
					gameBoard[i][j].setCell(3,i,j,movesMade++); // MOVE MADE
					gameBoard[i][j].setBotCell(false); //Move made here, not playable anymore
					
					if(i > 0 && gameBoard[i-1][j].getTypeAsString() != "No Access")
						gameBoard[i-1][j].setBotCell(true);//Set above cell to new playable
					else if(i > 0 && gameBoard[i-1][j].getTypeAsString() == "No Access")
						gameBoard[i-1][j].setBotCell(false);
				}
				cout << "C:" <<gameBoard[i][j].getColAsChar() << endl;
				print();
				return;
			}
		}
	}
	
	for(j = 0; j < width - 3; ++j){//HORIZANTAL SMART MOVE
		for(i = 0; i <  height; ++i){
			if(gameBoard[i][j].getType() == 1 &&  //U1
			   gameBoard[i][j+1].getType() == 1 &&//U1
			   gameBoard[i][j+2].getType() == 0){ //EMPTY
				
				if(gameBoard[i][j+2].isBotCell() == true){
					gameBoard[i][j+2].setCell(3,i,j+2,movesMade++); // MOVE MADE
					gameBoard[i][j+2].setBotCell(false); //Move made here, not playable anymore
					
					if(i > 0 && gameBoard[i-1][j+2].getTypeAsString() != "No Access")
						gameBoard[i-1][j+2].setBotCell(true);//Set above cell to new playable
					else if(i > 0 && gameBoard[i-1][j+2].getTypeAsString() == "No Access")
						gameBoard[i-1][j+2].setBotCell(false);
				}
				cout << "C:" <<gameBoard[i][j+2].getColAsChar() << endl;
				print();
				return;
			}
		}
	}
	
	for(j = 0; j < width - 3; ++j){//HORIZANTAL SMART MOVE, COMPUTER CLOSE TO CONNECTFOUR
		for(i = 0; i <  height; ++i){
			if(gameBoard[i][j].getType() == 3 &&  //COMP
			   gameBoard[i][j+1].getType() == 3 &&//COMP
			   gameBoard[i][j+2].getType() == 0){ //EMPTY
				
				if(gameBoard[i][j+2].isBotCell() == true){
					gameBoard[i][j+2].setCell(3,i,j+2,movesMade++); // MOVE MADE
					gameBoard[i][j+2].setBotCell(false); //Move made here, not playable anymore
					
					if(i > 0 && gameBoard[i-1][j+2].getTypeAsString() != "No Access")
						gameBoard[i-1][j+2].setBotCell(true);//Set above cell to new playable
					else if(i > 0 && gameBoard[i-1][j+2].getTypeAsString() == "No Access")
						gameBoard[i-1][j+2].setBotCell(false);
				}
				cout << "C:" <<gameBoard[i][j+2].getColAsChar() << endl;
				print();
				return;
			}
		}
	}
	
	for(i = 0; i < height - 3; ++i){ //VERTICAL SMART MOVE, COMPUTER CLOSE TO CONNECTFOUR
		for(j = 0; j < width; ++j){
			if(gameBoard[i][j].getType() == 0 && //empty
			   gameBoard[i+1][j].getType() == 3 && //cmp
			   gameBoard[i+2][j].getType() == 3){ // cmp
				
				if(gameBoard[i][j].isBotCell() == true){
					gameBoard[i][j].setCell(3,i,j,movesMade++); // MOVE MADE
					gameBoard[i][j].setBotCell(false); //Move made here, not playable anymore
					
					if(i > 0 && gameBoard[i-1][j].getTypeAsString() != "No Access")
						gameBoard[i-1][j].setBotCell(true);//Set above cell to new playable
					else if(i > 0 && gameBoard[i-1][j].getTypeAsString() == "No Access")
						gameBoard[i-1][j].setBotCell(false);
				}
				cout << "C:" <<gameBoard[i][j].getColAsChar() << endl;
				print();
				return;
			}
		}
	}
	
	randomCol = rand()%(width);
	
	while(k < height){
		if(gameBoard[k][randomCol].isBotCell()  == false)
			k++;
		else
			break;
	}
	
	gameBoard[k][randomCol].setCell(3, k, randomCol,movesMade++);//MOVE MADE
	gameBoard[k][randomCol].setBotCell(false); //Move made here, not playable anymore
	
	if(k > 0 && gameBoard[k-1][randomCol].getTypeAsString() != "No Access")
		gameBoard[k-1][randomCol].setBotCell(true);//Set above cell to new playable
	else if(i > 0 && gameBoard[i-1][randomCol].getTypeAsString() == "No Access")
		gameBoard[i-1][randomCol].setBotCell(false);
	
	cout << "C:" <<gameBoard[k][randomCol].getColAsChar()<< endl;
	print();
	
}

void ConnectFourAbstract::playGame(){
	
	string filename;
	int inputHeight;
	int inputWidth;
	int failCount = 0;
	bool gameOver = false;
	
	cout << "Enter height: "; cin >> inputHeight; //User input: board size
	cout << "Enter width: "; cin >> inputWidth;
	
	*this = ConnectFourAbstract(inputHeight,inputWidth);
	
	char playerOrComputer;
	cout << "Versus [P]layer or versus [C]omputer: "; cin >> playerOrComputer; //User input: pvp or pvc
	//----------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------
	while(!gameOver){
		if(playerOrComputer == 'C' || playerOrComputer == 'c'){// PvC
			cout << endl <<"PLAYER VS COMPUTER" << endl << endl;
			this->print();;
			
			string optSave;
			string turn = "P1";
			int user = 1;
			while(playerOrComputer == 'C' || playerOrComputer == 'c'){
				cout << turn << ": "; cin >> optSave;
				optSave[0] = toupper(optSave[0]); //Changing input to upper so we can accept lowercase inputs too.
				
				if(failCount > 3)
					exit(1);
				
				else if(optSave == "SAVE"){
					string filename;
					cin >> filename;
					save(filename, 1, playerOrComputer);
					cout << "Game saved on " << filename << "." << endl;
					
				}
				else if(optSave == "LOAD"){
					cin >> filename;
					this->load(filename, user, playerOrComputer);
					cout << "Game loaded from " << filename << ". Pv" << playerOrComputer << " game," << turn << "s turn." << endl;
					print();
					if(playerOrComputer != 'C' || playerOrComputer != 'c')//IF LOADED GAME TYPE IS DIFFRENT BREAK PvP LOOP
						break;
				}
				
				//Check if move is valid on this board(A to MAX_COL)
				else if(optSave[0] >= 'A' && optSave[0] <= this->operator()(0, width -1).getColAsChar()){
					int status = play(optSave[0],user);
					if(status != 0){//Print board and change user turn if a move is made, else keep asking for input
						print();;
						turn = "P1";
						
						if(isGameOver(user) == true){ //If game is over break the loop(CHECK WIN FOR USER 1)
							gameOver = true;
							break;
						}
						play(); // Play computer on succesful move
						
						if(isGameOver(3) == true){ //If game is over break the loop(CHECK WIN FOR USER 2)
							gameOver = true;
							break;
						}
					}
					else
						failCount++;//Increase fail count on invalid input.
				}
				
				else{
					cout << "Not in range, try again." << endl;
					failCount++;
				}
			}
		}
		//----------------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------------
		else if(playerOrComputer != 'C' || playerOrComputer != 'c'){ //PvP
			cout << endl << "PLAYER-1 VS PLAYER-2" << endl << endl;
			print();;
			
			string optSave;
			string turn = "P1";
			int user = 1;
			
			while(playerOrComputer != 'C' || playerOrComputer != 'c'){ // PLAYER VS PLAYER LOOP
				cout << turn << ": "; cin >> optSave;
				optSave[0] = toupper(optSave[0]); //Changing input to upper so we can accept lowercase inputs too.
				
				if(failCount > 3)
					exit(1);
				
				else if(optSave == "SAVE"){
					string filename;
					cin >> filename;
					save(filename, user, playerOrComputer);
					cout << "Game saved on " << filename << "." << endl;
					
				}
				else if(optSave == "LOAD"){
					cin >> filename;
					this->load(filename, user, playerOrComputer);
					cout << "Game loaded from " << filename << ". Pv" << playerOrComputer << " game," << turn << "s turn." << endl;
					print();
					if(playerOrComputer == 'C' || playerOrComputer == 'c')//IF LOADED GAME TYPE IS DIFFRENT BREAK PvP LOOP
						break;
				}
				//Check if move is valid on this board(A to MAX_COL)
				else if(optSave[0] >= 'A' && optSave[0] <= this->operator()(0,width -1).getColAsChar()){
					int status = play(optSave[0],user);
					if(status != 0){//Print board and change user turn if a move is made, else keep asking for input
						print();;
						turn = (turn == "P1" ? "P2":"P1");
						
						if(isGameOver(user) == true){//If game is over break the loop
							gameOver = true;
							break;
						}
						
						
						user = (user == 1 ? 2:1); // Change user on succesful move
					}
					else
						failCount++;//Increase fail count on invalid input.
				}
				
				else{
					cout << "Not in range, try again." << endl;
					failCount++;
				}
			}
		}
	}
}



