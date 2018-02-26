#include "ConnectFourUndo.h"
using namespace cfa;
using std::cout;
using std::endl;
using std::cerr;
using std::cin;

ConnectFourUndo::ConnectFourUndo() : ConnectFourPlus(){}

ConnectFourUndo::ConnectFourUndo(int i1,int i2 ) : ConnectFourPlus(i1,i2){}

ConnectFourUndo::ConnectFourUndo(const ConnectFourAbstract& obj) : ConnectFourPlus(obj){}

bool ConnectFourUndo::undoMove(){
	int numberOfMoves;
	numberOfMoves = findLastPlayed();
	

	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			if(gameBoard[i][j].getMoveNo() == numberOfMoves){
				gameBoard[i][j].setCell(0, i, j, -1,true);
				if(i > 0 && gameBoard[i-1][j].isBotCell())
					gameBoard[i-1][j].setBotCell(false);
				
				cout << "Move on " << gameBoard[i][j].getColAsChar() << " has been taken back." << endl;
				movesMade--;
				return true;
			}
		}
	}
	
	cout << "Can't take back anymore moves." << endl;
	return false;
}

void ConnectFourUndo::playGame(){
	string filename;
	int inputHeight;
	int inputWidth;
	int failCount = 0;
	bool gameOver = false;
	
	cout << "Enter height: "; cin >> inputHeight; //User input: board size
	cout << "Enter width: "; cin >> inputWidth;
	
	*this = ConnectFourUndo(inputHeight,inputWidth);
	
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
				else if(optSave == "UNDO"){//UNDO Computer's and player's move
					undoMove();
					undoMove();
					print();
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
				else if(optSave == "UNDO"){
					if(undoMove()){
						turn = (turn == "P1" ? "P2":"P1");
						user = (user == 1 ? 2:1);
						print();
					}
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
