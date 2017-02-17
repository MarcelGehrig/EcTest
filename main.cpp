#include <string>
#include <iostream>
#include <signal.h>
#include <thread>

#include <EtherCATMain.hpp>
//-f eni_1MAXON.xml -i8254x 1 1 -perf

using namespace ethercat;

int32_t encoder;
EC_T_BYTE* pbyPDIn;


void callbackFct(EC_T_BYTE* pbyPDInPtr)
{
	pbyPDIn = pbyPDInPtr;
// 	encoder = EC_GET_FRM_DWORD( pbyPDIn + 0 );
	
	// lese position von pointer und schreibe in globale variable von main
}



int main(int argc, char **argv) {
	void (*callbackFctPtr)(EC_T_BYTE*);
	callbackFctPtr = &callbackFct;
	EtherCATMain etherCATStack(argc, argv, callbackFctPtr);
	
	
	while ( etherCATStack.isRunning() ) {
		
		if (pbyPDIn) encoder = EC_GET_FRM_DWORD( pbyPDIn + 0 );	//test for NULL-pointer
		
		std::cout << "Encoder: " << encoder << std::endl;
		
		sleep(1);
	}
	
	etherCATStack.join();
	
    return 0;
}
