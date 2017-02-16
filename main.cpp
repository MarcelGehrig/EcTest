#include <string>
#include <iostream>
#include <thread>

#include <DCDemoMain.hpp>
#include <EcType.h>
#include <EcOs.h>
//-f eni_1MAXON.xml -i8254x 1 1 -perf


EC_T_DWORD encoderIn;
EC_T_BYTE* pbyPDIn2;
int32_t myValue;

void callbackFct(EC_T_BYTE* pbyPDIn)
{
	std::cout << pbyPDIn << std::endl;
	
// 		myValue = *( pbyPDIn+2 );
// 		myValue |= *( pbyPDIn+3 ) << 8;
// 		myValue |= *( pbyPDIn+4 ) << 16;
// 		myValue |= *( pbyPDIn+5 ) << 24;
	
// 	pbyPDIn2 = pbyPDIn;
// 	*encoderIn = EC_GET_FRM_DWORD( pbyPDIn + 0 );
//  	EC_GET_FRM_DWORD( pbyPDIn + 0 );
	// lese position von pointer und schreibe in globale variable von main
}

int main(int argc, char **argv) {
// 	std::cout << argv[0] << std::endl;
// 	std::cout << argv[1] << std::endl;
// 	std::cout << argv[2] << std::endl;
// 	std::cout << argv[3] << std::endl;
// 	std::cout << sayHello("Bob") << std::endl;
	void (*callbackFctPtr)(EC_T_BYTE*);
	callbackFctPtr = &callbackFct;
	std::thread t1(mainEtherCAT, argc, argv, callbackFctPtr);
	
	while ( 1 ) {
		std::cout << "Encoder: " << std::endl;
		std::cout << "Encoder: " << myValue << std::endl;
		
		sleep(1);
	}
	t1.join();
	std::cout << "hallo" << std::endl;
	
    return 0;
}
