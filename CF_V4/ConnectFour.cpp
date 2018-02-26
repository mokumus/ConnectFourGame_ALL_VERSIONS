#include "ConnectFour.h"

//
//CONSTRUCTORS AND DESTRUCTORS
//

ConnectFour::~ConnectFour(){
	//cout << "CALLED IT " << height << "  " << width << endl;
	//Delete each sub-array
	for(int i = 0; i < height; ++i) {
		delete[] gameBoard[i];
	}
	//Delete the array of pointers
	delete[] gameBoard;
}

ConnectFour::ConnectFour():height(5), width(5){
	gameBoard = new Cell*[5];//Make room for rows
	
	for(int i = 0; i < 5; ++i)
		gameBoard[i] = new Cell[5];//Make room for each cell of the row
	
	init(); //Initlize board
}

ConnectFour::ConnectFour(int i1V,int i2V):height(i1V), width(i2V){
	gameBoard = new Cell*[i1V];//Make room for rows
	
	for(int i = 0; i < i1V; ++i)
		gameBoard[i] = new Cell[i2V];//Make room for each cell of the row
	
	if(testSize(i1V,i2V) == false){
		cerr << "Invalid size.(Constructor Error)" << endl;
		exit(1);
	}
	init();//Initlize board
}

ConnectFour::ConnectFour(string filename){
	ifstream fp;
	string tempLine;
	
	int numOfLines = 0;
	int i = 0, j = 0;
	
	fp.open(filename);
	
	if(!fp){
		cerr << "File couldn't be opened.(Constructor Error)" << endl;
		exit(1);
	}
	
	while(getline(fp,tempLine)) //Loop through each line in file to find number of lines
		numOfLines++;
	
	fp.clear(); //reset file pointer
	fp.seekg(0,ios::beg); //go to begging of the file
	
	gameBoard = new Cell*[numOfLines];//Make room for rows
	height = numOfLines; //Set height;
	
	while(getline(fp,tempLine)){
		if(tempLine.length() == 0) //Just in case of empty lines in file.
			break;
		
		if(tempLine.length() != 0)
			width = static_cast<int> (tempLine.length());
		
		
		
		gameBoard[i] = new Cell[tempLine.length()];//Make room for each cell of the row
		
		for(j = 0; j < tempLine.length(); ++j){
			if(tempLine[j] == '*')
				gameBoard[i][j].setCell(0, i, j); //If '*', set cell to empty
			else
				gameBoard[i][j].setCell(-1, i , j); // White space considered No Acess cells
		}
		i++;//Increment row value for next Cell row
	}
	
	fp.close();
	
	if(testSize(height,width) == false){
		cerr << "Invalid size.(Constructor Error)" << endl;
		exit(1);
	}
	
	init();//Initlize board
}

ConnectFour::ConnectFour(const ConnectFour& object){
	gameBoard = new Cell*[object.height];
	for(int i = 0; i < object.height; ++i){
		gameBoard[i] = new Cell[object.height];
		for(int j = 0; j < object.width; ++j)
			gameBoard[i][j] = object.gameBoard[i][j];
	}
}

//
// CONNECT FOUR OPERATORS
//

ostream& operator <<(ostream& outs, const ConnectFour &board){
	int i;
	char start = 'A';
	
	//Print Column Letters
	for(i = 0; i < board.getWidth(); ++i)
		outs << static_cast<char> (start + i) << " ";
	
	outs << endl;
	
	//Print Cells
	for(i = 0; i < board.getHeigh(); ++i){
		for(int j = 0; j < board.getWidth(); ++j){
			switch (board(i,j).getType()) {
				case 0://Type empty = 0
					outs << "." << " "; break;
				case 1://user1 = 1
					outs << "O" << " "; break;
				case 2://user2 = 2
					outs << "X" << " "; break;
				case 3://computer = 3
					outs << "C" << " "; break;
				case -1://Not acessable = -1
					outs << " " << " "; break;
				case 11://winning cell user1
					outs << "o" << " "; break;
				case 22://winning cell user2
					outs << "x" << " "; break;
				case 33://winning cell comp
					outs << "c" << " "; break;
				default:
					cerr << "Unknown cell type.(Print error):" << board(i,j).getType() << endl;
					exit(1); break;
			}
		}
		outs << endl;
	}
	return outs;
}

ConnectFour& ConnectFour::operator=(const ConnectFour &rtSide){// USED IN LOAD GAME, VERY USEFUL!!!
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

bool ConnectFour::operator==(const ConnectFour & rtSide)const{
	if(height != rtSide.height || width != rtSide.width) //If heights or widths aren't the same they can't be equal
		return false;
	
	else{
		for(int i = 0; i < height; ++i){//Loop through each cell if any is diffrent return false
			for(int j = 0; j < width; ++j){
				if(gameBoard[i][j] != rtSide.gameBoard[i][j])
					return false;
			}
		}
		return true;//If we don't come across any diffrences return true
	}
}

bool ConnectFour::operator !=(const ConnectFour& rtSide) const{
	return (!(gameBoard == rtSide.gameBoard));
}

//
// TESTERS AND INIT-PRINT FUNCTIONS
//

bool ConnectFour::testSize(int heightV, int widthV){
	return(!(heightV < 4 || widthV < 4 || widthV > 26));
}

void ConnectFour::print() const{
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

void ConnectFour::testCellClass(){
	Cell cell1(0,0,0);
	Cell cell2(2,0,0);
	Cell cell3(1,1,5);
	Cell cell4(1,2,2);
	Cell cell5;
	
	cout << "CELL1:" << cell1 << endl;
	cout << "CELL2:" << cell2 << endl;
	cout << "CELL3:" << cell3 << endl;
	cout << "CELL4:" << cell4 << endl;
	cout << "CELL5:" << cell5 << endl << endl;
	
	
	
	cout << boolalpha;
	cout << "cell1 == cell2 >> " << (cell1 == cell2) << endl;
	cout << "cell3 == cell4 >> " << (cell3 == cell4) << endl << endl;
	
	cout << "cell5 = cell2++  " << endl;
	cout << "cell5 = " << (cell5 = cell2++) << endl;
	cout << "cell2 = " << cell2 << endl << endl;
	
	cout << "cell5 = ++cell3  " << endl;
	cout << "cell5 = " << (cell5 = ++cell3) << endl;
	cout << "cell3 = " << cell3 << endl << endl;
	
	cout << "cell1 = cell2--  " << endl;
	cout << "cell1 = " << (cell1 = cell2--) << endl;
	cout << "cell2 = " << cell2 << endl << endl;
	
	/* ----ISTREAM OPERATOR TEST
	 cout << "Enter Cell(tpye(int), i1,i2): "; cin >> cell5;
	 cout << cell5 << endl;
	 */
}

void ConnectFour::init(){
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			
			// Set lowest cell to bot cell.(Token drops here)
			if(i == height - 1)
				gameBoard[i][j].setCell(0,i,j,true);
			
			else if(gameBoard[i][j].getType() == -1)//Inaccesable cells
				gameBoard[i][j].setCell(-1, i, j);
			
			else if(gameBoard[i][j].getType() == 0)//Playable cells
				gameBoard[i][j].setCell(0, i, j);
			
			else
				cerr << "Initlization error.At: " << gameBoard[i][j] << endl;
			
		}
	}
}

//
// CELL CLASS SETTERS AND GETTERS
//

void ConnectFour::Cell::setCell(int typeVal, int i1Val, int i2Val, bool btVal){
	type = typeVal;
	i1 = i1Val;
	i2 = i2Val;
	botCell = btVal;
}

string ConnectFour::Cell::getTypeAsString() const{
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

//
// CELL CLASS OPERATORS
//

bool ConnectFour::Cell::operator ==(const Cell& rtVal) const{
	return(type == rtVal.type);
}

bool ConnectFour::Cell::operator !=(const Cell& rtVal) const{
	return (!(type == rtVal.type));
}

ConnectFour::Cell& ConnectFour::Cell::operator ++(){
	switch (type) {
		case 0:
			type = 1; break;
		case 1:
			type = 2; break;
		case 2:
			type = 3; break;
		case 3:
			type = 0; break;
		default:
			cerr << "Invalid type(operator++())" << type << "was entered." << endl;
	}
	return *this;
}

ConnectFour::Cell ConnectFour::Cell::operator ++(int ignoreMe){
	ConnectFour::Cell temp = *this;
	switch (type) {
		case 0:
			type = 1; break;
		case 1:
			type = 2; break;
		case 2:
			type = 3; break;
		case 3:
			type = 0; break;
		default:
			cerr << "Invalid type(operator++())" << type << "was entered." << endl;
	}
	return temp;
}

ConnectFour::Cell& ConnectFour::Cell::operator --(){
	switch (type) {
		case 0:
			type = 3; break;
		case 1:
			type = 2; break;
		case 2:
			type = 1; break;
		case 3:
			type = 0; break;
		default:
			cerr << "Invalid type(operator++())" << type << "was entered." << endl;
	}
	return *this;
}

ConnectFour::Cell ConnectFour::Cell::operator --(int ignoreMe){
	ConnectFour::Cell temp = *this;
	switch (type) {
		case 0:
			type = 3; break;
		case 1:
			type = 2; break;
		case 2:
			type = 1; break;
		case 3:
			type = 0; break;
		default:
			cerr << "Invalid type(operator++())" << type << "was entered." << endl;
	}
	return temp;
}


//
// BOARD CHECK FUNCTIONS
//

void ConnectFour::printConnected(int arr[][2]){
	int i;
	for(i = 0; i < 4; ++i){
		cout << "[" << arr[i][0] << "," << arr[i][1] << "] ";
		
		if(gameBoard[arr[i][0]][arr[i][1]].getTypeAsString() == "User 1")
			gameBoard[arr[i][0]][arr[i][1]].setCell(11, arr[i][0], arr[i][1]); //11 represents 'o'
		else if(gameBoard[arr[i][0]][arr[i][1]].getTypeAsString() == "User 2")
			gameBoard[arr[i][0]][arr[i][1]].setCell(22, arr[i][0], arr[i][1]); //22 represents 'x'
		else if(gameBoard[arr[i][0]][arr[i][1]].getTypeAsString() == "Computer")
			gameBoard[arr[i][0]][arr[i][1]].setCell(33, arr[i][0], arr[i][1]); //33 represents 'c'
		else
			cerr << "Winning cells could not be highlighted. printConnected() error." << endl;
	}
	cout << endl;
	
	print();
}

bool ConnectFour::isGameOver(int userRef){
	return (isWon(userRef) || isBoardFull());
}

bool ConnectFour::isWon(int userRef){
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

bool ConnectFour::isBoardFull() const{
	for(int i = 0; i <  height; ++i){
		for(int j = 0; j < width; ++j){
			if(gameBoard[i][j].getTypeAsString() == "Empty") //If there is an empty cell, board is not full
				return false;
		}
	}
	cout <<"The board is full. It's a tie." << endl;
	return true;
}

bool ConnectFour::horizantalWin(int userRef, int winningFour[][2]){
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

bool ConnectFour::verticalWin(int userRef, int winningFour[][2]){
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

bool ConnectFour::diagonalWin(int userRef, int (*winningFour)[2]){
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

//
// SINGLE PLAYER MANAGER FUNCTION
//

void ConnectFour::playGame(){
	string filename;
	int failCount = 0;
	bool gameOver = false;
	cout << "Enter file name: "; cin >> filename; //User input: board file
	ConnectFour board(filename); //Create a new board
	
	
	char playerOrComputer;
	cout << "Versus [P]layer or versus [C]omputer: "; cin >> playerOrComputer; //User input: pvp or pvc
	//----------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------
	while(!gameOver){
		if(playerOrComputer == 'C' || playerOrComputer == 'c'){// PvC
			cout << endl <<"PLAYER VS COMPUTER" << endl << endl;
			cout << board;
			
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
					board.save(filename, 1, playerOrComputer);
					cout << "Game saved on " << filename << "." << endl;
					
				}
				else if(optSave == "LOAD"){
					cin >> filename;
					board.load(filename, user, playerOrComputer);
					cout << "Game loaded from " << filename << ". Pv" << playerOrComputer << " game," << turn << "s turn." << endl;
					board.print();
					if(playerOrComputer != 'C' || playerOrComputer != 'c')//IF LOADED GAME TYPE IS DIFFRENT BREAK PvP LOOP
						break;
				}
				
				//Check if move is valid on this board(A to MAX_COL)
				else if(optSave[0] >= 'A' && optSave[0] <= board(0,board.width -1).getColAsChar()){
					int status = board.play(optSave[0],user);
					if(status != 0){//Print board and change user turn if a move is made, else keep asking for input
						cout << board;
						turn = "P1";
						
						if(board.isGameOver(user) == true){ //If game is over break the loop(CHECK WIN FOR USER 1)
							gameOver = true;
							break;
						}
						board.play(); // Play computer on succesful move
						
						if(board.isGameOver(3) == true){ //If game is over break the loop(CHECK WIN FOR USER 2)
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
			cout << board;
			
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
					board.save(filename, user, playerOrComputer);
					cout << "Game saved on " << filename << "." << endl;
					
				}
				else if(optSave == "LOAD"){
					cin >> filename;
					board.load(filename, user, playerOrComputer);
					cout << "Game loaded from " << filename << ". Pv" << playerOrComputer << " game," << turn << "s turn." << endl;
					board.print();
					if(playerOrComputer == 'C' || playerOrComputer == 'c')//IF LOADED GAME TYPE IS DIFFRENT BREAK PvP LOOP
						break;
				}
				//Check if move is valid on this board(A to MAX_COL)
				else if(optSave[0] >= 'A' && optSave[0] <= board(0,board.width -1).getColAsChar()){
					int status = board.play(optSave[0],user);
					if(status != 0){//Print board and change user turn if a move is made, else keep asking for input
						cout << board;
						turn = (turn == "P1" ? "P2":"P1");
						
						if(board.isGameOver(user) == true){//If game is over break the loop
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

//
//MULTIPLAYER MANAGER FUNCTION
//

void ConnectFour::playMulti(){
	char opt1, opt2, opt3, opt4, opt5;
	string filename;
	int boardNum;
	char move;
	int error = 0;
	
	
	cout << "Board file: "; cin >> filename;
	ConnectFour b1(filename);
	cout << "Versus [P] or [C] ";
	cin >> opt1;
	
	cout << "Board file: "; cin >> filename;
	ConnectFour b2(filename);
	cout << "Versus [P] or [C] ";
	cin >> opt2;
	
	cout << "Board file: "; cin >> filename;
	ConnectFour b3(filename);
	cout << "Versus [P] or [C] ";
	cin >> opt3;
	
	cout << "Board file: "; cin >> filename;
	ConnectFour b4(filename);
	cout << "Versus [P] or [C] ";
	cin >> opt4;
	
	cout << "Board file: "; cin >> filename;
	ConnectFour b5(filename);
	cout << "Versus [P] or [C] ";
	cin >> opt5;
	
	
	
	while(error < 2){
		cout << "Board num: ";
		cin >> boardNum;
		
		switch (boardNum) {
			case 1:
				if(opt1 == 'P'){
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status = b1.play(move, user);
					if(status == 0) error++;
					b1.isGameOver(user);
					b1.print();
					user = 2;
					cout <<"P2: "; cin >> move;
					status = b1.play(move, user);
					if(status == 0) error++;
					b1.isGameOver(user);
					b1.print();
				}
				
				else{
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status =b1.play(move, user);
					if(status == 0) error++;
					b1.isGameOver(user);
					b1.print();
					
					user = 3;
					b1.play();
					b1.isGameOver(user);
			
				}
				cout << "board1 == board2 >> " << boolalpha << (b1 == b2) << endl;
				cout << "board1 != board2 >> " << (b1 != b2) << endl;
				break;
				
			case 2:
				if(opt2 == 'P'){
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status =b2.play(move, user);
					if(status == 0) error++;
					b2.isGameOver(user);
					b2.print();
					
					user = 2;
					cout <<"P2: "; cin >> move;
					status = b2.play(move, user);
					if(status == 0) error++;
					b2.isGameOver(user);
					b2.print();
				}
				
				else{
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status = b2.play(move, user);
					if(status == 0) error++;
					b2.isGameOver(user);
					b2.print();
					
					user = 3;
					b2.play();
					b2.isGameOver(user);
				
				}
				cout << "board1 == board2 >> " << (b1 == b2) << endl;
				cout << "board1 != board2 >> " << (b1 != b2) << endl;
				break;
				
			case 3:
				if(opt3 == 'P'){
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status = b3.play(move, user);
					if(status == 0) error++;
					b3.isGameOver(user);
					b3.print();
					
					user = 2;
					cout <<"P2: "; cin >> move;
					status = b3.play(move, user);
					if(status == 0) error++;
					b3.isGameOver(user);
					b3.print();
				}
				
				else{
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status = b3.play(move, user);
					if(status == 0) error++;
					b3.isGameOver(user);
					b3.print();
					
					user = 3;
					b3.play();
					b3.isGameOver(user);
			
				}
				cout << "board1 == board2 >> " << (b1 == b2) << endl;
				cout << "board1 != board2 >> " << (b1 != b2) << endl;
				break;
				
			case 4:
				if(opt4 == 'P'){
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status = b4.play(move, user);
					if(status == 0) error++;
					b4.isGameOver(user);
					b4.print();
					
					user = 2;
					cout <<"P2: "; cin >> move;
					b4.play(move, user);
					b4.isGameOver(user);
					b4.print();
				}
				
				else{
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status = b4.play(move, user);
					if(status == 0) error++;
					b4.isGameOver(user);
					b4.print();
					
					
					user = 3;
					b4.play();
					b4.isGameOver(user);
				
				}
				cout << "board1 == board2 >> " << (b1 == b2) << endl;
				cout << "board1 != board2 >> " << (b1 != b2) << endl;
				break;
				
				
			default: // board5
				
				if(opt5 == 'P'){
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status = b5.play(move, user);
					if(status == 0) error++;
					b5.isGameOver(user);
					b5.print();
					
					user = 2;
					cout <<"P2: "; cin >> move;
					status = b5.play(move, user);
					if(status == 0) error++;
					b5.isGameOver(user);
					b5.print();
				}
				
				else{
					int user = 1;
					cout <<"P1: "; cin >> move;
					int status = b5.play(move, user);
					if(status == 0) error++;
					b5.isGameOver(user);
					b5.print();
					
					user = 3;
					b5.play();
					b5.isGameOver(user);
					
				}
				cout << "board1 == board2 >> " << (b1 == b2) << endl;
				cout << "board1 != board2 >> " << (b1 != b2) << endl;
				break;
		}
	}
	
}

//
// PLAY USER
//

int ConnectFour::play(char move,int &user){
	int moveCol = static_cast<int>(move) - 'A';
	int moveRow;
	
	for(int i = 0; i < height; ++i){
		if(gameBoard[i][moveCol].getTypeAsString() != "No Access"){
			if(gameBoard[i][moveCol].isBotCell() == true){//If the reached cell is playable
				moveRow = i;
				gameBoard[moveRow][moveCol].setCell(user, moveRow, moveCol); //Mark the move
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

//
// PLAY COMPUTER
//

void ConnectFour::play(){
	int i, j, k = 0;
	int randomCol = 0;
	
	for(i = 0; i < height - 3; ++i){ //VERTICAL SMART MOVE
		for(j = 0; j < width; ++j){
			if(gameBoard[i][j].getType() == 0 &&   //EMPTY
			   gameBoard[i+1][j].getType() == 1 && //U1
			   gameBoard[i+2][j].getType() == 1){  //U1
				
				if(gameBoard[i][j].isBotCell() == true){
					gameBoard[i][j].setCell(3,i,j); // MOVE MADE
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
					gameBoard[i][j+2].setCell(3,i,j+2); // MOVE MADE
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
					gameBoard[i][j+2].setCell(3,i,j+2); // MOVE MADE
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
					gameBoard[i][j].setCell(3,i,j); // MOVE MADE
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
	
	
	gameBoard[k][randomCol].setCell(3, k, randomCol);//MOVE MADE
	gameBoard[k][randomCol].setBotCell(false); //Move made here, not playable anymore
	
	if(k > 0 && gameBoard[k-1][j].getTypeAsString() != "No Access")
		gameBoard[k-1][randomCol].setBotCell(true);//Set above cell to new playable
	else if(i > 0 && gameBoard[i-1][randomCol].getTypeAsString() == "No Access")
		gameBoard[i-1][randomCol].setBotCell(false);
	
	cout << "C:" <<gameBoard[k][randomCol].getColAsChar()<< endl;
	print();
	
}

//
// SAVE AND LOAD
//

void ConnectFour::save(string filename, int userRef, char gameType) const{
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
	
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			fp << gameBoard[i][j].getType() << " " << gameBoard[i][j].isBotCell() << " " ;
		}
		fp << endl;
	}
	fp.close();
}

void ConnectFour::load(string filename, int &userRef, char &gameType){
	ifstream fp;
	int h,w;
	int tempType;
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
	
	ConnectFour tempBoard(h,w);
	
	for(int i = 0; i < h; ++i){
		for(int j = 0; j < w; ++j){
			fp >> tempType;
			fp >> isBotCell;
			tempBoard(i,j).setCell(tempType, i, j,isBotCell);
		}
	}
	
	
	
	*this = tempBoard;
	
	fp.close();
}
