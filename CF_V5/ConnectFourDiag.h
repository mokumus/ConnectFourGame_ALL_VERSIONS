#ifndef ConnectFourDiag_h
#define ConnectFourDiag_h
#include "ConnectFourAbstract.h"

namespace cfa{
	class ConnectFourDiag : public ConnectFourAbstract{
	public:
		//CONSTRUCTORS - DESTRUCTOR...
		ConnectFourDiag();
		ConnectFourDiag(int i1,int i2);
		ConnectFourDiag(const ConnectFourAbstract&);
		virtual ~ConnectFourDiag(){};
	private:
		virtual bool isWon(int userRef);
	};
}

#endif /* ConnectFourDiag_h */
