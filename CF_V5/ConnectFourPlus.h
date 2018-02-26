#ifndef ConnectFourPlus_h
#define ConnectFourPlus_h
#include "ConnectFourAbstract.h"

namespace cfa{
	class ConnectFourPlus : public ConnectFourAbstract{
	public:
		//CONSTRUCTORS - DESTRUCTOR...
		ConnectFourPlus();
		ConnectFourPlus(int i1,int i2);
		ConnectFourPlus(const ConnectFourAbstract&);
		virtual ~ConnectFourPlus(){};
	protected:
		virtual bool isWon(int userRef);
	};
}



#endif /* ConnectFourPlus_h */
