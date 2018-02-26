#ifndef ConnectFourUndo_h
#define ConnectFourUndo_h
#include "ConnectFourPlus.h"

namespace cfa{
	class ConnectFourUndo : public ConnectFourPlus{
	public:
		//CONSTRUCTORS - DESTRUCTOR...
		ConnectFourUndo();
		ConnectFourUndo(int i1,int i2);
		ConnectFourUndo(const ConnectFourAbstract&);
		virtual ~ConnectFourUndo(){};
		virtual void playGame();
		
	private:		
		bool undoMove();		//return true if succesful, false if no moves to take back
	};
}

#endif /* ConnectFourUndo_h */
