#include <string>
#include <iostream>
#include <signal.h>
#include <thread>

#include <DCDemoMain.hpp>
#include <EcType.h>
#include <EcOs.h>
//-f eni_1MAXON.xml -i8254x 1 1 -perf


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
	std::thread t1(mainEtherCAT, argc, argv, callbackFctPtr);
	
// 	sleep(5);
	while ( DCDemoIsRunning() ) {
		
		
		if (pbyPDIn) encoder = EC_GET_FRM_DWORD( pbyPDIn + 0 );	//test for NULL-pointer
		else std::cout << "nullpointer" << std::endl;
		std::cout << "Encoder: " << encoder << std::endl;
// 		std::cout << "Encoder: " << std::endl;
		sleep(1);
		
	}
	t1.join();
	std::cout << "hallo" << std::endl;
	
    return 0;
}
